#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

 int num =12;//enter yor number here

int factorial(int s,int e)//recursie func
{
	if (s==e)
		return s;
	else
		return e*factorial(s,e-1);
}

void *worker(void *arg) {
	int index= *(int*)arg;
	int mid=num/2;
	int total=1;
    if(index==0)
{	
	total=factorial(1,mid-1);
}
else{
	total=factorial(mid,num);
}
    pthread_exit((void*)total);
}

int main(int argc, char *argv[]) {
   
    pthread_t threads[2];
    int thread_args[2]; 
    //Create Threads
thread_args[0]=0;
thread_args[1]=1;

        pthread_create(&threads[0], NULL, worker, &thread_args[0]);
  pthread_create(&threads[1], NULL, worker, &thread_args[1]);
	int temp;
	int fac=1;
    // Wait for the threads to complete

        pthread_join(threads[0], (void*)&temp);	
	fac*=temp;
        pthread_join(threads[1], (void*)&temp);	
	fac*=temp;
    printf("factorial: %d\n",fac);

  
    
    return 0;
}
