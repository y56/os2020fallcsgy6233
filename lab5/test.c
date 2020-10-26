#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>

enum CONSTANTS {
    NUM_THREADS = 4,
    NUM_ITERS = 1
};

int global = 0;

void* main_thread(void *arg) {
    int i;
    for (i = 0; i < NUM_ITERS; ++i) {
        // __atomic_fetch_add(&global, 1, __ATOMIC_SEQ_CST);
        /* This fails consistently. */
        global++;
        // printf("%ld  %ld\n", (long)getpid(), (long)getppid());
        printf("pid: %d, thread tid=%lu, thread pid=%d\n",
               getpid(),pthread_self(),syscall(SYS_gettid));
    }
    return NULL;
}

int main(void) {
    int i;
    pthread_t threads[NUM_THREADS];

    printf("pid: %d, thread tid=%lu, thread pid=%d -- main\n",
           getpid(),pthread_self(),syscall(SYS_gettid));

    for (i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, main_thread, NULL);
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);
    // assert(global == NUM_THREADS * NUM_ITERS);
    printf("global:                  %d\n", global);
    printf("NUM_THREADS * NUM_ITERS: %d\n", NUM_THREADS * NUM_ITERS);

    return EXIT_SUCCESS;
}
