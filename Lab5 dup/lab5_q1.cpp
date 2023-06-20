#include <fcntl.h>
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
    	int file_desc = open("dup.txt", O_WRONLY | O_APPEND);
    	if(file_desc < 0)
        {
        	printf("Error opening the file\n");
        	return 1;
        }
		close(fa[0]);
		if (write(fa[1],&file_desc,sizeof(file_desc))==-1)
      	{
       		cout<<"An error ocurred while writing to the file."<<endl;
			return 1;
     	}
       	close(fa[1]);
    }
    else
    {
    	int file_desc1;
    	if(read(fa[0], &file_desc1, sizeof(file_desc1))==-1)
        {
        	cout<<"An error ocurred while writing to the file."<<endl;
            return 1;
        }
        int copy_desc = dup(file_desc1);
        write(copy_desc,"This will be output to the file named dup.txt\n", 46);  
    	write(file_desc1,"This will also be output to the file named dup.txt\n", 51);
    }
    return 0;
}
