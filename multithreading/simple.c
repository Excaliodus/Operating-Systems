#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>



void *worker(void *arg) {
    int num = *(int*)arg;
    num+=1;
    printf("%d\n",num);
    sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
   
    pthread_t threads[2];
    int thread_args[2]; 
    // Create Threads
    int i;
    for ( i = 0; i < 2; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_args[i]);
    }

    // Wait for the threads to complete
    for (i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("done\n");
  
    
    return 0;
}
