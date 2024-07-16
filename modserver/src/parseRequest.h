#ifndef PARSE_REQUEST_H
#define PARSE_REQUEST_H

typedef struct {
    char filename[256];
    int returncode;
} httpRequest;

httpRequest parseRequest(char *msg);

#endif // PARSE_REQUEST_H
