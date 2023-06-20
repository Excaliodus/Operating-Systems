#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define SHM_SIZE 1024
sem_t * s1;
sem_t * s2;
pthread_mutex_t mutex;

void *func1(void *arg) {
    pthread_mutex_lock(&mutex);
    sem_wait(&s1);
    printf("leftcross\n");
    sleep(2);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
void *func2(void *arg) {
    pthread_mutex_lock(&mutex);
    sem_wait(&s2);
    printf("rightcross\n");
    sleep(2);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
int main(int argc, char* argv[])
{
    s1 = sem_open("sem1", 0666, 4);  
    s2 = sem_open("sem2", 0666, 4);  
        pthread_t t1, t2;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create two threads
    pthread_create(&t1, NULL,func1 , NULL);
    pthread_create(&t2, NULL,func2 , NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("allcross\n");
    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
}
