/*client.c */
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

int fill_buffer(char * bufptr, int size,char* command[]);
struct shmseg 
{
   int bytes;
   char buf[BUF_SIZE];
};

int main(int argc, char *argv[]) 
{
   
   struct shmseg *shmp; 
   char *bufptr;
   sem_t* s1 = sem_open("sem1",0666, 0); 
   sem_t* s2 = sem_open("sem2",0666, 0);
   sem_t* s3 = sem_open("sem3",0666, 0);
   
   sem_wait(s1);
   int shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644);
   
   if (shmid == -1) 
   {
	   printf("Client:Unable to open shared memory\n");
	   return 1;
   } 
   else 
		printf("Client:Opened Shared Memory 1\n");  
   
   // Attach to the segment to get a pointer to it.
   shmp = shmat(shmid, NULL, 0);
   if (shmp == (void *) -1) 
   {
		printf("Client: Unable to attach\n"); 
		return 2;
   } 
   else 
	   printf("Client:Attached to Shared Memory 1\n");  
   
   
   bufptr = shmp->buf;
   shmp->bytes = fill_buffer(bufptr,1024,argv);
   printf("Client:Wrote \"%s\" to Shared Memory 1\n", shmp->buf);
   bufptr = shmp->buf;
     
   sem_post(s2);
  	
	if(argv[1][0]=='r')
	{	
		sem_wait(s3);
		printf("Client:Read Key:\"%s\" from Shared Memory 1\n", shmp->buf); 
		
		char shmkey2[20]; 
		int i=0; 
		
		while(shmp->buf[i]!=' ' && shmp->buf[i]!='\0') 
		{
			shmkey2[i]=shmp->buf[i]; 
			i++;
		} 
		shmkey2[i]='\0'; 
		
		int SHM_KEY2=atoi(shmkey2);  
		
		//reading from second shared memory 
		struct shmseg *shmp1;
		char *bufptr1;
		int shmid2 = shmget(SHM_KEY2, sizeof(struct shmseg), 0644);
   
		if (shmid2 == -1) 
		{
			printf("Client:Unable to create shared memory\n");
			return 1;
		} 
		else 
			printf("Client:Opened Shared Memory 2\n");
   
		// Attach to the segment to get a pointer to it.
		shmp1 = shmat(shmid2, NULL, 0);
		if (shmp1 == (void *) -1) 
		{
			printf("Client: Unable to attach\n"); 
			return 2;
		} 
		else 
			printf("Client:Attached to Shared Memory 2\n");
		
			printf("Client:Read file Data from Shared Memory 2:\"%s\"\n", shmp1->buf); 

		if (shmdt(shmp1) == -1) 
		{
			printf("Client:Unable to dettach\n"); 
			return 3;
		}  
		else	
			printf("Client:Dettached Shared Memory 2\n");
		 
   
	}
	
	if (shmdt(shmp) == -1) 
	{
		printf("Client:Unable to dettach\n"); 
		return 3;
    }  
	else	
		printf("Client:Dettached Shared Memory 1\n");  
	
   printf("Client: Complete\n");
   return 0;
} 

int fill_buffer(char * bufptr, int size,char* command[]) 
{
	
	int filled_count; 
	
	int i=0;  
	int j=0;
	while(command[1][j]!='\0')
	{
		bufptr[i]=command[1][j]; 
		i++; 
		j++;
	}
	bufptr[i]=' '; 
	
	i++; 
	j=0;	
	while(command[2][j]!='\0')//reading file name
	{
		bufptr[i]=command[2][j]; 
		i++; 
		j++;
	} 
	
	if(bufptr[0]=='w')//reading data to be written
	{
		bufptr[i]=' '; 
	
		i++;  
		j=0;
		while(command[3][j]!='\0')
		{
			bufptr[i]=command[3][j]; 
			i++; 
			j++;
		}  
	} 
	
	bufptr[i]='\0';   
	bufptr[size-1] = '\0';
	
	filled_count = strlen(bufptr);
	return filled_count;
}