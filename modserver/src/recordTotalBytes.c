#include <pthread.h>

typedef struct {
    pthread_mutex_t mutexlock;
    int totalbytes;
} sharedVariables;

int recordTotalBytes(int bytes, sharedVariables *mempointer) {
    pthread_mutex_lock(&mempointer->mutexlock);
    mempointer->totalbytes += bytes;
    int total = mempointer->totalbytes;
    pthread_mutex_unlock(&mempointer->mutexlock);
    return total;
}
