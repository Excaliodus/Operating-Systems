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
	res=open("final",O_WRONLY); 
	if(res==-1) 
		printf("Error");  
	
	int num[5]={1,2,3,4,5};
	write(res,num,sizeof(int)*5);
	close(res);
	
}