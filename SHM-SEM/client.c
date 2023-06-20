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

#define BUF_SIZE 1024

struct sharedseg 
{	
	char buf[BUF_SIZE];
};

int main()
{
	sem_t* s1=sem_open("s1",0666,0); 
	sem_t* s2=sem_open("s2",0666,0); 
	sem_init(s1,1,0);
	sem_init(s2,1,0);//initialization of semaphores is done in one file only
	
	struct sharedseg* shm; 
	char* buf; 
	key_t key=ftok("shm",0); 
	int shmid=shmget(key,sizeof(struct sharedseg),0666|IPC_CREAT); 
	shm=shmat(shmid,NULL,0);  
	buf=shm->buf;  
	
	char temp[BUF_SIZE]; 
	int fptr=open("file.txt",O_RDONLY,S_IRUSR); 
	ssize_t size=read(fptr,temp,BUF_SIZE); 
	temp[size]='\0'; 
	
	printf("read %s from file\n",temp); 
	
	int i=0; 
	for(i=0;i<size;i++) 
		buf[i]=temp[i]; 
	buf[i]='\0';
	
	printf("Client sent \"%s\" to server\n",buf);
	
	sem_post(s1); 
	sem_wait(s2); 
	
	printf("Client read \"%s\" from shm\n",buf); 
	
	shmdt(shm);
	shmctl(shmid,IPC_RMID,NULL);//done only in file that run at end
}
