#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void *process_file(void *arg) 
{
	char *filename = (char *)arg;
	int temp;
	char data[1000];
	int fd = open (filename, O_RDONLY, S_IRUSR);
	ssize_t size = read(fd, data, sizeof (data));
	temp= size;
	temp--;
	close(fd);
	int unique[1000], count = 0;
	int i;
	for (i = 0; i < temp; i++)
	{
		int value = data[i];
		int j;
		if(value>=0)
		{
			for (j = 0; j < i; j++)
			{
                		if (data[j] == value)
				{
                    			break;
                		}
            		}
            		if (j == count)
			{
                		unique[count++] = value;
            		}
		}
	}
    	int *result = malloc(sizeof(int) * (count + 1));	//Creating new array for unique elements
    	result[0] = count;					//Length of array stored at 0th index
    	int k;
    	for (k = 0; k < count; k++)
	{
        	result[k + 1] = unique[k];
    	}
    	return result;
}

int main(int argc,int*argv[])
{
    	pthread_t thread1;
	pthread_t thread2;
    	void *result1;
	void *result2;
    	pthread_create(&thread1, NULL, process_file, "f1.txt");
	pthread_join(thread1, &result1);
	int *data1 = (int *)result1;
    	int count1 = data1[0];
	int sum = 0;
	int k;
	int temp;
	int unique[1000];
	int count = 0;
	int i;
    	for (i = 1; i <= count1; i++)
	{
        	int value = data1[i];
        	int j;
        	for (j = 0; j < count; j++)
		{
            		if (unique[j] == value)
			{
                		break;
            		}
       		}
        	if (j == count)
		{
            	unique[count++] = value;
       		}
    	}
    	pthread_create(&thread2, NULL, process_file, "f2.txt");
    	pthread_join(thread2, &result2);
	int *data2 = (int *)result2;
	int count2 = data2[0];
	int l;
   	for (l = 1; l <= count2; l++)
	{
        	int value = data2[i];
        	int j;
        	for (j = 0; j < count; j++)
		{
            		if (unique[j] == value)
			{
                		break;
            		}
        	}
        	if (j == count)
		{
            		unique[count++] = value;
        	}
    	}
    	for ( k = 0; k < count; k++)
	{
		int m;
		temp=unique[k];
      		for(m=0;m<k;m++)
		{
		  	if(temp==unique[m])
			{
 				temp=0;
			}
		}
        	sum += temp;	
    	}
    	float avg = (float)sum / count;
    	printf("Average of unique integers: %f\n", avg);
   	free(result1);
   	free(result2);
    	return 0;
}