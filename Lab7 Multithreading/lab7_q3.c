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
pthread_mutex_t mutex;
int i=0;

void* even(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if (i%2==0)
		{
			printf("%d, ", i);
			i++;
		}
		pthread_mutex_unlock(&mutex);
		if (i>= 100)
			break;
	}
	return NULL;
}

void* odd(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if (i%2!=0)
		{
			printf("%d, ", i);
			i++;
		}
		pthread_mutex_unlock(&mutex);
		if (i>= 100)
			break;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t my_thread[2];
    int j;
    for(j=0; j<2; j++)
    {
    	if (j==0)
    		pthread_create(&my_thread[j], NULL, even, NULL);
    	pthread_create(&my_thread[j], NULL, odd, NULL);	
    }
    for(j=0; j<2; j++)
    {
    	pthread_join(my_thread[j], NULL);
    }
    return 0;
}
