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

int arr[8]={1,2,3,4,5,6,7,8};
int size=8;

void *worker(void *arg) {
    int index = *(int*)arg;
    int seg=size/4;
    int start=index*seg;
    int end=(index+1)*seg;
    int i;
    int sum=0;
    for(i=start;i<end;i++)
    {
      sum+=arr[i];
    }
    pthread_exit((void*)sum);
}

int main(int argc, char *argv[]) {
   
    pthread_t threads[4];
    int thread_args[4]; 
    // Create Threads
    int i;
    for ( i = 0; i < 4; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_args[i]);
    }
    int totalsum=0;
void* temp;
    // Wait for the threads to complete
    for (i = 0; i < 4; i++) {
        pthread_join(threads[i], &temp);
	totalsum+=(int)temp;
    }
    printf("sum= %d\n",totalsum);
  
    
    return 0;
}
