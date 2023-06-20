#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>  
#include <fcntl.h>
#include <pthread.h>
#include<semaphore.h>

sem_t * s1;
sem_t * s2;
sem_t * s3;

int main() 
{
	s1 = sem_open("sem1", O_CREAT, 0666, 1);  
	s2 = sem_open("sem2", O_CREAT, 0666, 1);  
	s3 = sem_open("sem3", O_CREAT, 0666, 1); 
}