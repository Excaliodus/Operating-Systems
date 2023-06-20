#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_TABLES 5

int table_count = NUM_TABLES;
sem_t mutex_1;
sem_t mutex_2;

void occupy_table()
{
    sem_wait(&mutex_1);

    if (table_count == 0)
    {
        sem_post(&mutex_1);
        sem_wait(&mutex_2);
    }

    table_count--;
    printf("Thread %ld occupied table\n", pthread_self());

    sem_post(&mutex_1);
}

void leave_table()
{
    sem_wait(&mutex_1);

    table_count++;
    printf("Thread %ld left table\n", pthread_self());

    if (table_count == 1)
    {
        sem_post(&mutex_2);
    }

    sem_post(&mutex_1);
}

void *runner(void *param)
{
    occupy_table();
    leave_table();
    pthread_exit(NULL);
}

int main()
{
    sem_init(&mutex_1, 0, 1);
    sem_init(&mutex_2, 0, 0);

    int i = 0, n = 9;
    pthread_t threads[n];

    for (i = 0; i < n; i++)
    {
        pthread_create(&threads[i], NULL, runner, NULL);
    }

    for (i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex_1);
    sem_destroy(&mutex_2);

    return 0;
}