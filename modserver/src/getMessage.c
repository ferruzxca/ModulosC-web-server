#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *getMessage(int conn_s) {
    char *message = malloc(1024);
    read(conn_s, message, 1024);
    return message;
}
