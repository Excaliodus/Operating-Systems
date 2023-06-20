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

int main()
{
	sem_t * s1=sem_open("sem1",0666,1);
	sem_t * s2=sem_open("sem2",0666,1);
	sem_init(s1,1,0); 
	sem_init(s2,1,0); 
	
	int fd1[2]; 
	int fd2[2]; 
	
	if(pipe(fd1)==-1) 
		printf("Cannot make pipe1\n"); 
	if(pipe(fd2)==-1) 
		printf("Cannot make pipe2\n"); 
	
	int pid=fork(); 
	if(pid>0) 
	{
		close(fd1[0]);//read end of pipe1 
		close(fd2[1]);//write end on pipe 2 
		
		int n=100;
		write(fd1[1],&n,sizeof(int)); 
		printf("Number sent by Parent:%d\n",n);		
		close(fd1[1]);//write end of pipe1 
		sem_post(s1); 
		sem_wait(s2);
		read(fd2[0],&n,sizeof(int)); 
		close(fd2[0]);  
		printf("Number recieved by Parent:%d\n",n);
		
	} 
	else if (pid==0)
	{
		close(fd2[0]);//read end of pipe2 
		close(fd1[1]);//write end on pipe1
		sem_wait(s1); 
		
		int n; 
		read(fd1[0],&n,sizeof(int)); 
		close(fd1[0]);  
		printf("Number recieved by Child:%d\n",n);
		n++; 
		write(fd2[1],&n,sizeof(int));  
		printf("Number sent by Child:%d\n",n);
		close(fd2[1]);//write end of pipe2  
		sem_post(s2);
		
		
	}


}