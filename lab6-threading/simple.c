#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 100

void *thread_func(void *arg) {
    int thread_num = *(int *)arg;
    printf("Hello from thread %d - I was created in iteration %d\n", thread_num, thread_num - 1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number of threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0 || num_threads > MAX_THREADS) {
        printf("Invalid number of threads. Must be between 1 and %d\n", MAX_THREADS);
        return 1;
    }

    pthread_t threads[MAX_THREADS];
    int thread_nums[MAX_THREADS];

    for (int i = 1; i <= num_threads; i++) {
        thread_nums[i - 1] = i;
        pthread_create(&threads[i - 1], NULL, thread_func, &thread_nums[i - 1]);

        if (i % 4 == 0 || i % 5 == 0) {
            printf("I am thread 1. Created new thread (%d) in iteration %d...\n", i, i - 1);
            sleep(1);
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
