#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// External function declaration
extern int madd_t(int, int);

// Function to be executed by threads
void *performMadd(void *threadId) {
    long tid = (long)threadId;
    long tid2 = tid * 2;
    int result = madd_t(tid, tid2); // Call madd_t with thread ID as arguments
    printf("Result from thread %ld: %d\n", tid, result);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Create threads
    for(t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, performMadd, (void *)t);

        if (rc) {
            printf("Error: Unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads have completed.\n");
    pthread_exit(NULL);
    return 0;
}
