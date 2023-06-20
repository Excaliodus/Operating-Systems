#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char*argv[]) 
{
	char tosend[100];
	int i=0,j=0;  

	for(i=1;i<argc;i++)
	{
		tosend[j]=argv[i][0];  
		j++; 
		tosend[j]=' '; 
		j++;
	} 
	tosend[j]='\0'; 
	
	printf("got %s from 1stfile\n",tosend);
	
}