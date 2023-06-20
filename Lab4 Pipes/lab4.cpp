#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#inlcude <errno.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
using namespace std;

int main(int argc, char *argv[])
{
	int fa[2];
	if (pipe(fa) == -1)
   	{
      return 1;
   	}
   	
   	int fb[2];
   	if (pipe(fb) == -1)
   	{
      return 1;
   	}
   	
   	int id = fork();
   	if (id == -1)
    	return 2;
    
    if (id>0)
    {
    	close(fa[0]);
    	close(fb[1]);
		char buff[9999];
		int fd = open("file.txt", O_RDONLY, S_IRUSR);
		ssize_t size = read (fd, buff, sizeof(buff));
		int temp = size;
		if (write(fa[1], &temp, sizeof(int))<0)
		{
			return 3;
		}
		if (write(fa[1], &buff, sizeof(char) *temp)<0)
			return 4;
		close (fa[1]);
		wait(NULL);
		if (read (fb[0], &buff sizeof(char) *temp)<0)
			return 6;
		close(fb[0];
		int fb = open ("output.txt", O_WRONLY, S_IWUSR);
		write (fb,buff,size);
	}
	else
	{
		int j=0;
		close(fa[1]);
    	close(fb[0]);
    	char buff[9999];
    	if (read (fa[0], &j, sizeof(int))<0)
    		return 5;
    	if (read (fa[0], &buff, sizeof(char)*j)<0)
    		return 6;
    	
    	
		for (int i=0; i<temp; i++)
	{
		if (buff[i] == '&' || buff[i] == '@' || buff[i] == '#' || buff[i] == '*' || buff[i] == '?' || buff[i] == '$' || buff[i] == '"' || buff[i] == '~' || buff[i] == '%')
			buff[i] = ' ';
	}
	if (write(fb[1], &buff, sizeof(char)*j)<0)
		return 4;
	return 0;
}
