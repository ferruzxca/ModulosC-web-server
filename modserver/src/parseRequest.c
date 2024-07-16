#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    char filename[256];
    int returncode;
} httpRequest;

httpRequest parseRequest(char *message) {
    httpRequest ret;
    char method[8];
    char filename[256];
    char http_version[16];

    sscanf(message, "%s %s %s", method, filename, http_version);

    // Inicialización por defecto
    strcpy(ret.filename, "400.html");
    ret.returncode = 400;

    if (strcmp(method, "GET") != 0) {
        return ret;
    }

    if (strcmp(http_version, "HTTP/1.1") != 0 && strcmp(http_version, "HTTP/1.0") != 0) {
        return ret;
    }

    // Si no hay nombre de archivo en la solicitud
    if (strcmp(filename, "/") == 0) {
        strcpy(ret.filename, "public_html/index.html");
        ret.returncode = 200;
        return ret;
    }

    // Remover la primera barra del nombre de archivo
    memmove(filename, filename + 1, strlen(filename));

    // Construir la ruta completa del archivo
    strcpy(ret.filename, "public_html/");
    strcat(ret.filename, filename);

    // Verificar si el archivo existe
    if (access(ret.filename, F_OK) != -1) {
        ret.returncode = 200;
    } else {
        strcpy(ret.filename, "404.html");
        ret.returncode = 404;
    }

    return ret;
}

