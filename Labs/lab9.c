#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <semaphore.h> 
#include <pthread.h>

int numberofTables=5;

int count=5;  
sem_t s1; 
sem_t s2;


void occupyTable()
{
    sem_wait(&s1);
	if(count==0)
	{
		sem_post(&s1);
		sem_wait(&s2);
	}
    count--;  
	printf("Thread %ld occupied table\n",pthread_self());
    sem_post(&s1);
} 

void LeaveTable()
{
    sem_wait(&s1); 
	count++; 
	printf("Thread %ld left table\n",pthread_self());
	if(count==0)
		sem_post(&s2);
    sem_post(&s1);

} 

void* runner(void*param)
{
	occupyTable(); 
	LeaveTable(); 	
	pthread_exit(NULL);
}

int main()
{
    sem_init(&s1,0,1);  
    sem_init(&s2,0,0); 
	
	int i=0,n=9; 
	
	pthread_t t[n]; 
	
	for(i=0;i<n;i++) 
	{
		pthread_create(&t[i],NULL,runner,NULL);
	} 
	
	for(i=0;i<n;i++) 
	{
		pthread_join(t[i],NULL);
	}
}