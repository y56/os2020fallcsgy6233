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
    int scope; 
    srand(time(NULL));
    pthread_t threads[NUM_THREADS];



    printf("checking the default scope.......\n");
    pthread_attr_t attr;
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* first inquire on the current scope */
    if (pthread_attr_getscope(&attr, &scope) != 0)
        fprintf(stderr, "Unable to get scheduling scope\n");
    else {
        if (scope == PTHREAD_SCOPE_PROCESS)
            printf("\nPTHREAD_SCOPE_PROCESS\n\n");
        else if (scope == PTHREAD_SCOPE_SYSTEM)
            printf("\nPTHREAD_SCOPE_SYSTEM\n\n");
        else
            fprintf(stderr, "Illegal scope value.\n");
    }
    
    printf("setting the contention scope to PTHREAD_SCOPE_PROCESS\n");
    /* set the scheduling algorithm to PCS or SCS */
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
    
    printf("checking the scope again.......\n");
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* first inquire on the current scope */
    if (pthread_attr_getscope(&attr, &scope) != 0)
        fprintf(stderr, "Unable to get scheduling scope\n");
    else {
        if (scope == PTHREAD_SCOPE_PROCESS)
            printf("\nPTHREAD_SCOPE_PROCESS\n\n");
        else if (scope == PTHREAD_SCOPE_SYSTEM)
            printf("\nPTHREAD_SCOPE_SYSTEM\n\n");
        else
            fprintf(stderr, "Illegal scope value.\n");
    }
    




    for (i = 0; i < NUM_THREADS; ++i)
        pthread_create(&threads[i], NULL, main_thread, NULL);
    for (i = 0; i < NUM_THREADS; ++i)
        pthread_join(threads[i], NULL);

    //printf("\nglobal:                  %d\n", global);
    //printf("NUM_THREADS * NUM_ITERS: %d\n", NUM_THREADS * NUM_ITERS);
    //printf("the area: %f\n", 4.0*global/NUM_THREADS/NUM_ITERS);
    return EXIT_SUCCESS;
}
