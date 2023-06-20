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

int arr[16]={2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32};
int size=16;

void *worker(void *arg)
{
	int value = *(int*)arg;
	int seg_size=(size/4);
	int start_idx=value*seg_size;
    int end_idx=(value+1)*seg_size;
    int sum=0;
    int i=0;
    for(i=start_idx; i<end_idx; i++)
    {
    	sum+=arr[i];
    }
	pthread_exit((void*)sum);
}
	
int main(int argc, char *argv[])
{
    pthread_t my_thread[4];
    int val[4];
    int i;
    for(i=0; i<4; i++)
    {
    	val[i]=i;
    	pthread_create(&my_thread[i], NULL, worker, &val[i]);
    }
    int tsum=0;
    void* ret;
    for(i=0; i<4; i++)
    {
    	pthread_join(my_thread[i], &ret);
    	tsum+=(int)ret;
    }
    printf("The total sum is: %d \n", tsum);
    pthread_exit(NULL);
}
