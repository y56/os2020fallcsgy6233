// ref: https://stackoverflow.com/questions/2353371/how-to-do-an-atomic-increment-and-fetch-in-c

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enum CONSTANTS {
    NUM_THREADS = 4,
    NUM_ITERS = 1000000
};

int global = 0;
void* main_thread() {
    int i;
    int x,y;
    for (i = 0; i < NUM_ITERS; ++i) {
        x = rand();
        y = rand();
        if ((
          ((double)x/(double)RAND_MAX)*((double)x/(double)RAND_MAX) +
          ((double)y/(double)RAND_MAX)*((double)y/(double)RAND_MAX)
        ) <= 1) {
            __atomic_fetch_add(&global, 1, __ATOMIC_SEQ_CST);
        }
    }
    return NULL;
}

int main(void) {
    int i;
    pthread_t threads[NUM_THREADS];

    srand(time(NULL));

    for (i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, main_thread, NULL);
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);

    printf("global:                  %d\n", global);
    printf("NUM_THREADS * NUM_ITERS: %d\n", NUM_THREADS * NUM_ITERS);
    printf("the area: %f\n", 4.0*global/NUM_THREADS/NUM_ITERS);
    return EXIT_SUCCESS;
}
