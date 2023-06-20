#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_QUEUE_SIZE 50

typedef struct
{
	int array[MAX_QUEUE_SIZE];
	int front;
	int rear;
	int count;
} Queue;

void queue_push(Queue* queue, int item);
int queue_pop(Queue* queue);

Queue* shared_queue;
//size of array stored at first index
int data1[11] = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int data2[11] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

void* push_thread1(void* arg)
{
	for(;;)
	{
		int* data = (int*)arg;
		int len=data[0]+1;
		for (int i = 1; i < len; i++)
		{
			queue_push(shared_queue, data[i]);
		}
		sem_post(&sem1);
	}
}
void* push_thread2(void* arg)
{
	for(;;)
	{
		sem_wait(&sem1);
		int* data = (int*)arg;
		int len=data[0]+1;
		for (int i = 1; i < len; i++)
		{
			queue_push(shared_queue, data[i]);
		}
		sem_post(&sem2);
}

void* pop_thread(void* arg)
{
	for(;;)
	{
		sem_wait(&sem2)
		int popped_data;
		int* data = (int*)arg;
		for (int i = 0; i < data; i++)
		{
			popped_data = queue_pop(shared_queue);
			printf("Popped data: %d\n", popped_data);
		}
	}
}

void queue_push(Queue* queue, int item)
{
	queue->array[queue->rear] = item;
	queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	queue->count++;
}

int queue_pop(Queue* queue)
{
	int popped_item;
	
	popped_item = queue->array[queue->front];
	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
	queue->count--;
	
	return popped_item;
}



int main()
{
	shared_queue = (Queue*)malloc(sizeof(Queue));
	shared_queue->front = 0;
	shared_queue->rear = 0;
	shared_queue->count = 0;
	
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	
	pthread_t write1, write2;
	if (pthread_create(&write1, NULL, push_thread1, (void*)data1))
	{
		printf("Error creating thread 1\n");
		exit(1);
	}
	if (pthread_create(&write2, NULL, push_thread2, (void*)data2)) 
	{
		printf("Error creating thread 2\n");
		exit(1);
	}
	
	pthread_t thread3;
	if (pthread_create(&thread3, NULL, pop_thread, (void*)(data1[0]+data2[0]))
	{
		printf("Error creating thread 3\n");
		exit(1);
	}
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	free(shared_queue);
	
	return 0;
}