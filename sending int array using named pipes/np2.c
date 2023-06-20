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
	res=open("final",O_RDONLY); 
	if(res==-1) 
		printf("Error");  
	
	int temp[5];
	read(res,temp,sizeof(int)*5);  
	int i=0; 
	for(i=0;i<5;i++)
		printf("%d ",temp[i]);
	
	close(res);
	
}