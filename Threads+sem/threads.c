#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <semaphore.h> 

//synchrozing it to ensure it runs it this order->runner1,runner2,runner1

sem_t s1;//DONT MAKE POINTERS-WILL GIVE SEGMENTATION FAULT 
sem_t s2; 


struct toPass
{
	int* arr; 
	int size;
};

void* runner1(void*args)
{
	sem_wait(&s1);
	
	struct toPass* p1=(struct toPass*)args; 
	printf("In runner 1\n");
	int i=0; 
	for(i=0;i<10;i++)
	{
		p1->arr[i]=p1->arr[i]+1;  
		printf("%d ",p1->arr[i]); 
	} 
	
	printf("\n"); 

	sem_post(&s2);

	pthread_exit(NULL);
}

void* runner2(void*args)
{
	sem_wait(&s2);
	
	struct toPass* p1=(struct toPass*)args; 
	printf("In runner 2\n");
	int i=0; 
	for(i=0;i<10;i++)
	{
		p1->arr[i]=p1->arr[i]+2;  
		printf("%d ",p1->arr[i]); 
	} 
	
	printf("\n");  
	
	sem_post(&s1);
	
	pthread_exit(NULL);
}

int main() 
{
	struct toPass p1;  
	
	sem_init(&s1,0,1);//no need to open-we open named semaphores only
	sem_init(&s2,0,0);
	
	p1.arr=(int*)malloc(sizeof(int)*10); 
	p1.size=10;
		
	int i=0; 
	for(i=0;i<10;i++)
		p1.arr[i]=i;
		
	pthread_t pid[3];  
	pthread_create(&pid[0],NULL,runner1,&p1);
	pthread_create(&pid[1],NULL,runner2,&p1);
	pthread_create(&pid[2],NULL,runner1,&p1); 
	pthread_join(pid[0],NULL);
	pthread_join(pid[1],NULL);
	pthread_join(pid[2],NULL);

	
	
}