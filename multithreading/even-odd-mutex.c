#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;  
int i = 0; 

void* print_even(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (i % 2 == 0) {
            printf("%d, ", i);
            i++;
        }
        pthread_mutex_unlock(&mutex);
        if (i >= 10) break;  
    }
    return NULL;
}

void* print_odd(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (i % 2 == 1) {
            printf("%d, ", i);
            i++;
        }
        pthread_mutex_unlock(&mutex);
        if (i >= 10) break; 
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&mutex, NULL); 

    pthread_create(&thread1, NULL, print_even, NULL);
    pthread_create(&thread2, NULL, print_odd, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex); 

    return 0;
}
