#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    
    key_t key = ftok("shmfile",65);
  
   
    int shmid = shmget(key,1024,0666|IPC_CREAT);
  
   
    char *str = (char*) shmat(shmid,(void*)0,0);
  
    printf("Data read from memory: %s\n",str);
    
    
    int num_count = 0;
    int sum = 0;
int small=100;
int large=-1;
    char *num_str = strtok(str, " ");
    while (num_str != NULL) {
        int num = atoi(num_str);
        sum += num;
        num_count++;
if(num>large)
large=num;
if(num<small)
small=num;
        num_str = strtok(NULL, " ");
    }
    double avg = (double)sum / num_count;
    printf("Sum: %d\nAverage: %f\n", sum, avg);
 printf("Smallest: %d\nLargest: %d\n", small, large);

   
    shmdt(str);
    
    
    shmctl(shmid,IPC_RMID,NULL);
     
    return 0;


}