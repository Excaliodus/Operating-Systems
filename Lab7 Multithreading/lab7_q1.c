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

void *worker(void *arg)
{
	int value = *(int*)arg;
	printf("The value recieved is %d \n", value);
	value++;
	printf("The new value is %d \n", value);
	sleep(1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t my_thread[2];
    int val[2];
    int i;
    for(i=0; i<2; i++)
    {
    	val[i]=i;
    	pthread_create(&my_thread[i], NULL, worker, &val[i]);
    }
    for(i=0; i<2; i++)
    {
    	pthread_join(my_thread[i], NULL);
    }
    printf("Done\n");
}
