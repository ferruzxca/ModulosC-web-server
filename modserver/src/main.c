#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <pthread.h>
#include "recordTotalBytes.h"
#include "parseRequest.h"


//Funciones
char * getFileName(char* msg);
char * getMessage(int fd);
int printFile(int fd, char *filename);
int printHeader(int fd, int returncode);
int sendMessage(int fd, char *msg);
void cleanup(int signum);

// global constants
#define PORT 2001
#define LISTENQ 10

int list_s;  // listening socket

// headers to send to clients
char *header200 = "HTTP/1.0 200 OK\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n";
char *header400 = "HTTP/1.0 400 Bad Request\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n";
char *header404 = "HTTP/1.0 404 Not Found\nServer: CS241Serv v0.1\nContent-Type: text/html\n\n";



int main(int argc, char *argv[]) {
    int conn_s;
    short int port = PORT;
    struct sockaddr_in servaddr;
    
    (void) signal(SIGINT, cleanup);
    
    if ((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        fprintf(stderr, "Error creating listening socket.\n");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    
    if (bind(list_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
        fprintf(stderr, "Error calling bind()\n");
        exit(EXIT_FAILURE);
    }
    
    if (listen(list_s, 10) == -1) {
        fprintf(stderr, "Error Listening\n");
        exit(EXIT_FAILURE);
    }
    
    shm_unlink("/sharedmem");
    
    int sharedmem;
    
    if ((sharedmem = shm_open("/sharedmem", O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) == -1) {
        fprintf(stderr, "Error opening sharedmem in main() errno is: %s ", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    ftruncate(sharedmem, sizeof(sharedVariables));
    
    sharedVariables *mempointer;
    
    mempointer = mmap(NULL, sizeof(sharedVariables), PROT_READ | PROT_WRITE, MAP_SHARED, sharedmem, 0); 
    
    if (mempointer == MAP_FAILED) {
        fprintf(stderr, "Error setting shared memory for sharedVariables in recordTotalBytes() error is %d \n ", errno);
        exit(EXIT_FAILURE);
    }
    
    pthread_mutex_init(&mempointer->mutexlock, NULL);
    mempointer->totalbytes = 0;

    socklen_t addr_size = sizeof(servaddr);
    int headersize;
    int pagesize;
    int totaldata;
    int children = 0;
    pid_t pid;
    
    while (1) {
        if (children <= 10) {
            pid = fork();
            children++;
        }
        
        if (pid == -1) {
            fprintf(stderr,"can't fork, error %d\n", errno);
            exit(1);
        }
        
        if (pid == 0) {
            while (1) {
                conn_s = accept(list_s, (struct sockaddr *)&servaddr, &addr_size);
                    
                if (conn_s == -1) {
                    fprintf(stderr,"Error accepting connection \n");
                    exit(1);
                }
                
                char *header = getMessage(conn_s);
                httpRequest details = parseRequest(header);
                free(header);
                
                headersize = printHeader(conn_s, details.returncode);
                pagesize = printFile(conn_s, details.filename);
                
                totaldata = recordTotalBytes(headersize + pagesize, mempointer);
                
                printf("Process %d served a request of %d bytes. Total bytes sent %d \n", getpid(), headersize + pagesize, totaldata);
                
                close(conn_s);
            }
        }
    }
    
    return EXIT_SUCCESS;
}
