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
	//remember to open semaphore in both files
	sem_wait(s1); 
	
	struct sharedseg* shm; 
	char* buf; 
	key_t key=ftok("shm",0); 
	int shmid=shmget(key,sizeof(struct sharedseg),0666); 
	shm=shmat(shmid,NULL,0);  
	buf=shm->buf; 
	
	printf("Server read \"%s\" from shm\n",buf);  
		
	int Array[100]; 
	
	int i=0; 
	int totalnums=0; 
	while(buf[i]!='\0')
	{
		char temp[20]; 
		int j=0; 
		while(buf[i]!=' ' && buf[i]!='\0')
		{
			temp[j]=buf[i]; 
			j++; 
			i++;
		} 
		i++; 
		temp[j]='\0'; 
		Array[totalnums]=atoi(temp);//string to integers  
		totalnums++;
	}
	
	for(i=0;i<totalnums;i++)
	{
		Array[i]=Array[i]*2;
	}
	
	char towrite[totalnums][10];
	for(i=0;i<totalnums;i++)
	{ 
		sprintf(towrite[i], "%d", Array[i]);//integers to string
	} 
	
	int fptr=open("file2.txt",O_CREAT,0666);//create new file if not present
	fptr=open("file2.txt",O_WRONLY,S_IWUSR);  
	for(i=0;i<totalnums;i++)
	{
		write(fptr,towrite[i],strlen(towrite[i]));//write to new file number wise
		write(fptr," ",1);
	}
	
	sem_post(s2);
	
	printf("Server sent \"%s\" to Client\n",buf); 
	
	shmdt(shm); 
	
}
