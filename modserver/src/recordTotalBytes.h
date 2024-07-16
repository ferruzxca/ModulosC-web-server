#ifndef RECORD_TOTAL_BYTES_H
#define RECORD_TOTAL_BYTES_H

#include <pthread.h>

typedef struct {
    pthread_mutex_t mutexlock;
    int totalbytes;
} sharedVariables;

int recordTotalBytes(int bytes, sharedVariables *mempointer);

#endif // RECORD_TOTAL_BYTES_H
