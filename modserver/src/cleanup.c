#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Declaración de la función de limpieza
void cleanup(int signum);

extern int list_s;  // Declaración externa para el socket

void cleanup(int signum) {
    printf("Cleaning up...\n");

    // Cerrando el socket
    if (close(list_s) < 0) {
        perror("close");
    }

    exit(EXIT_SUCCESS);
}

