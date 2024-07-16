#include <unistd.h>
#include <string.h>

void sendMessage(int conn_s, char *message) {
    write(conn_s, message, strlen(message));
}
