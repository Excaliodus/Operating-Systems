/*Question :   

 Write a program that take input from a file in Child process. In Child process the following thing should be done:

-	Filing to read data from a file 

-	Remove the alphabets from that data and place it in output file.

-	The data is sent to parent which sort the numbers in ascending order. 

Note: use the input file given in Quiz folder. You are not allowed to use file handling. Use Open, read, write calls instead. 

Submission Guidelines:

You have to submit following things;

-	Outfiles 

-	Cpp files 

-	Screen Short of your output*/

#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#define BUFFER_SIZE 25

using namespace std;
int main(int argc, char *argv[])
{
	int fa[2];
	if (pipe(fa) == -1)
   	{
      return 1;
   	}
   	
	int id1 = fork();
	if (id1 == -1)
    {
        cout<<"Fork 1 failed"<<endl;
        return 2;
    }
    if (id1 != 0)
    {
    	wait(NULL);
		close(fb[1];
		if (read (fa[0], &j, sizeof(int))<0)
    		return 5;
    	if (read (fa[0], &buff, sizeof(char)*j)<0)
    		return 6;
		for (int i=0; i<j; i++)
		{
			for(int x=0; x<j; x++)
			{ 
				if (buff[i]>'0' && buff[i]<'9')
				{
					if (buff[i]<buff[i+1])
					{
						int swap=buff[i+1];
						buff	
				}
			}	
		}
		int fb = open ("output.txt", O_WRONLY, S_IWUSR);
		write (fb,buff,size);
    }
    else
    {
    	char buff[9999];
		int fd = open("QuizText.txt", O_RDONLY, S_IRUSR);
		ssize_t size = read (fd, buff, sizeof(buff));
		int temp = size;
    	int temp1=temp;
		for (int i=0; i<temp; i++)
		{
			if (buff[i]>'0' && buff[i]<'9')
			{
				temp1--;
				buff[i] = ' ';
			}	
		}
		close(fa[0]);
		if (write(fa[1], &temp1, sizeof(int))<0)
		{
			return 3;
		}
		if (write(fa[1], &buff, sizeof(char) *temp)<0)
			return 4;
    }
    return 0;
}
