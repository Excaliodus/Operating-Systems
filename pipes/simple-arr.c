#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>

int main(int argc, char *argv[])
{
   int fd[2];
   if (pipe(fd) == -1)
   {
      return 1;
   }

   int pid = fork();
   if (pid == -1)
      return 2;

   if (pid >0)
   {
      close(fd[0]);
      int arr[] = {1, 2, 3, 4, 1, 2, 5, 9};
      int arrSize = sizeof(arr) / sizeof (int);
      int i;
      for (i=0; i<arrSize; i++)
      {
         printf("%d ", arr[i]);
      } 
      if (write(fd[1], &arrSize, sizeof(int)) < 0)
         return 3;
 
      if (write(fd[1], &arr, sizeof(int) *arrSize) < 0)
      {
         return 4;
      }
      printf("\nSent array \n");
      close(fd[1]);
   }
   else
   {
      close(fd[1]);
      int arr[8];
      int n, i, sum = 0;

      if (read(fd[0], &n, sizeof(int)) < 0)
         return 5;

      printf("Received n = %d\n", n);

      if (read(fd[0], &arr, sizeof(int) * n) <0)
         return 6; 

      printf("Received array.\n");

      close(fd[0]);
      int min = 999999999;
      int max = -99999999;
      for (i=0; i<n; i++){
         sum += arr[i];
         if(arr[i]>max)
             max=arr[i];
         if(arr[i]<min)
             min=arr[i];
      }
      float avg=sum/n;

      printf("Average is %f\n", avg);
      printf("Min is %d\n", min);
      printf("max is %d\n", max);
   }

   return 0;
}
