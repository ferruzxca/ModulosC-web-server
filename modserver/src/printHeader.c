#include <unistd.h>
#include <string.h>

extern char *header200;
extern char *header400;
extern char *header404;

int printHeader(int conn_s, int returncode) {
    char *header;
    int headerSize = 0;

    switch (returncode) {
        case 200:
            header = header200;
            headerSize = strlen(header200);
            break;
        case 400:
            header = header400;
            headerSize = strlen(header400);
            break;
        case 404:
            header = header404;
            headerSize = strlen(header404);
            break;
    }

    write(conn_s, header, headerSize);
    return headerSize;
}
