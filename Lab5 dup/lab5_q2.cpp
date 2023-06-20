//Write a program that creates an array. The parent creates an array and sends it to the child using  pipes. The child's job is to receive the array and find min, max, average stored into the array.

#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

using namespace std;
int main(int argc, char* argv[])
{
    int fa[2];
    if (pipe(fa) == -1)
    {
        cout<<"Pipe 1 failed"<<endl;
        return 1;
    }
    int id1 = fork();
    if (id1 < 0)
    {
        cout<<"Fork 1 failed"<<endl;
        return 2;
    }
    if (id1 != 0)
    {
    	int arr[10]={1,2,3,4,5,6,7,8,9,0};
		close(fa[0]);
		if (write(fa[1],&arr,sizeof(arr))==-1)
      	{
       		cout<<"An error ocurred while writing to the file."<<endl;
			return 1;
     	}
       	close(fa[1]);
    }
    else
    {
    	int sum=0;
    	int avg=0;
    	int min=999999;
    	int max=-999999;
    	int arr1[10];
    	if(read(fa[0], &arr1, sizeof(arr1))==-1)
        {
        	cout<<"An error ocurred while writing to the file."<<endl;
            return 1;
        }
        int arrSize=sizeof(arr1)/sizeof(int);
        for (int i=0;i <arrSize; i++)
        {
        	sum=sum+arr1[i];
        	if(min>arr1[i])
        	{
        		min=arr1[i];
        	}
        	if(max<arr1[i])
        	{
        		max=arr1[i];
        	}
        }
        avg=sum/arrSize;
        cout<<"The Average is: "<<avg<<endl;
        cout<<"The Min is: "<<min<<endl;
        cout<<"The Max is: "<<max<<endl;
    }
    return 0;
}
