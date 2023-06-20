#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc,char*argv[]) 
{
	int fptr=open("file.txt",O_RDONLY,S_IRUSR); 
	int fd2=open("f.txt",O_CREAT,0666); 
	fd2=open("f.txt",O_WRONLY,S_IWUSR); 
	
	dup2(fd2,1);//redirect output
	dup2(fptr,0);//redirect input
	
	printf("Hello file \n");//a new file is created and this is printed in that file 
	
	char buf[50]; 
	fgets(buf,sizeof(buf),stdin); //use this to get string input 
	
	printf("input was: %s\n",buf);
	
}