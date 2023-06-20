/* server.c */
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

#define BUF_SIZE 1024
#define SHM_KEY 1232
#define SHM_KEY1 1235 

sem_t * s1;
sem_t * s2;
sem_t * s3;

int fill_buffer(char * bufptr, int size,char* command);
struct shmseg {
  int bytes;
   char buf[BUF_SIZE];
}; 

void ReadFromfile(char*filename)
{
	char*dataRead; 
	printf("Server:Opening \"%s\":\n",filename);
	int fptr=open(filename,O_RDONLY,S_IRUSR);  
	

	struct shmseg *shmp;
	int shmid = shmget(SHM_KEY1, sizeof(struct shmseg), 0644|IPC_CREAT);
	if (shmid == -1) 
    {
	   printf("Server:Unable to create shared memory\n"); 
	   return;
	} 
	else 
		 printf("Server:Created Shared Memory 2\n"); 
   
   // Attach to the segment to get a pointer to it.
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) 
	{
	   printf("Server:Unable to attach\n"); 
	   return;
	}   
	else 
		printf("Server:Attached to Shared Memory 2\n"); 
	
	
	dataRead= shmp->buf;
	
   shmp->bytes = read(fptr,(char*)dataRead,1000); //read file  
	dataRead[shmp->bytes]='\0';
   printf("Server:Data in file:\"%s\"\n",dataRead); 
   printf("Server:Wrote \"%s\" to Shared Memory 2\n", shmp->buf);
   dataRead = shmp->buf;

	if (shmdt(shmp) == -1) {
      printf("Server:Unable to dettach shared memory2\n"); 
		return;
   }  
   else 
		printf("Server:Dettached Shared Memory 2\n"); 
   
} 

void WriteTofile(char*filename,char*dataTobeWritten)
{
	int fptr=open(filename,O_CREAT);//if not present create it 
	fptr=open(filename,O_WRONLY,S_IWUSR); 
	printf("Server:Writing \"%s\" to file \"%s\"\n",dataTobeWritten,filename);
	write(fptr, dataTobeWritten, strlen(dataTobeWritten)); 
	
}

void * runner(void *param)
{
	char* buffer=(char*)param;
		
	char command[50]; 
	char filename[50]; 
	char dataTobeWritten[100];
	int i=0; 
    int j=0;
   
   while(buffer[i]!=' ')
   {
	   command[j]=buffer[i]; 
	   i++; 
	   j++;
   } 
   command[j]='\0';
   i++; 
   j=0;
   
    while(buffer[i]!=' ' && buffer[i]!='\0')
   {
	   filename[j]=buffer[i]; 
	   i++; 
	   j++;
   } 
   filename[j]='\0'; 
   
   if(command[0]=='w')
   {
	    i++; 
		j=0; 
		
		while(buffer[i]!='\0')
		{
			dataTobeWritten[j]=buffer[i]; 
			i++; 
			j++;
		} 
		dataTobeWritten[j]='\0'; 
   }
  
	if(command[0]=='w')//write to file 
		WriteTofile(filename,dataTobeWritten); 
	else if(command[0]=='r')
	{
		ReadFromfile(filename); 
		
		struct shmseg *shmp;
		char*bufptr;
		int shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644);
		if (shmid == -1) 
		{
			printf("Server:Unable to get shared memory\n"); 
			pthread_exit(NULL);
		} 
		else 
			printf("Server:Again Opened Shared Memory 1\n");
			
   
		// Attach to the segment to get a pointer to it.
		shmp = shmat(shmid, NULL, 0);
		if (shmp == (void *) -1) 
		{
			printf("Server:Unable to attach\n");  
			pthread_exit(NULL);
		}  
		else 
			printf("Server:Attached to Shared Memory 1\n");
		
		bufptr= shmp->buf;
		
		bufptr[0]='1';
		bufptr[1]='2';
		bufptr[2]='3';
		bufptr[3]='5'; 
		bufptr[4]='\0';
		
		shmp->bytes = 4;  
		printf("Server:Wrote Key:\"%s\" to Shared Memory 1\n", shmp->buf);
		bufptr = shmp->buf;

		if (shmdt(shmp) == -1) 
		{
			printf("Server:Unable to dettach shared memory2\n");  
			pthread_exit(NULL);
		} 	 
		else 
			printf("Server:Dettached Shared Memory 2\n");  
		
		sem_post(s3);	
	}
}


int main(int argc, char *argv[]) 
{
	struct shmseg *shmp;
	char *bufptr;
	s1 = sem_open("sem1",0666, 0); 
	s2 = sem_open("sem2",0666, 0);  
	s3 = sem_open("sem3",0666, 0); 
	sem_init(s1, 1, 0); 
	sem_init(s2, 1, 0); 
	sem_init(s3, 1, 0); 

	int shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT); //shared memory allocation

	if (shmid == -1) 
	{
		printf("Server:Unable to create shared memory\n"); 
		return 1;
	} 
	else 
		printf("Server:Created Shared Memory 1\n"); 

	// Attach to the segment to get a pointer to it.
	shmp = shmat(shmid, NULL, 0);
	if (shmp == (void *) -1) 
	{
		printf("Server:Unable to attach\n"); 
		return 2;
	}  
	else 
		printf("Server:Attached to Shared Memory 1\n"); 

	sem_post(s1); 
	sem_wait(s2);
	
	printf("Server:Command Recieved Through Shared Memory 1 \"%s\"\n", shmp->buf);
 
	char ReadFromSharedMemory[200]; 
  
	int i=0; 
	int j=0;  
  
	while(shmp->buf[i]!='\0')
	{
		ReadFromSharedMemory[j]=shmp->buf[i]; 
		i++; 
		j++;
	}
	ReadFromSharedMemory[j]='\0';
	shmp->buf[0]='\0'; 
  
	if (shmdt(shmp) == -1)
	{
		printf("Server:Unable to dettach\n"); 
		return 3;
	} 
	else
		printf("Server:Detached Shared Memory 1\n");
  
	printf("Server:Creating a new Thread\n");
	pthread_t t1;
	pthread_create(&t1,NULL,runner,(void*)ReadFromSharedMemory);  
	pthread_join(t1,NULL); 
	
	printf("Server: Complete\n");
	return 0;
} 



