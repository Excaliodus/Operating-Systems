#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <semaphore.h>  
#include <pthread.h> 
#include <string.h> 
#include <fcntl.h>  

int main() 
{
	sem_open("s1",O_CREAT,0666,1);
	sem_open("s2",O_CREAT,0666,1);
}