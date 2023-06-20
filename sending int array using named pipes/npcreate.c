#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h>

int main()
{
	int res; 
	res=mkfifo("final",0777);
	printf("fifo created\n");
	
}