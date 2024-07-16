#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int printFile(int conn_s, char *filename) {
    int file;
    char buffer[1024];
    int bytesRead;

    file = open(filename, O_RDONLY);
    if (file == -1) {
        write(conn_s, "File not found", 14);
        return 0;
    }

    while ((bytesRead = read(file, buffer, 1024)) > 0) {
        write(conn_s, buffer, bytesRead);
    }

    close(file);
    return bytesRead;
}
