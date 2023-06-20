#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char*argv[]) 
{
	char* tosend[argc];
	
	int i=0,j=0;  
	for(i=0;i<argc;i++) 
		tosend[i]=(char*)malloc(12);
	
	for(i=1;i<argc;i++)
	{
		tosend[i][0]=argv[i][0];  
		tosend[i][1]='\0';
	} 
	
	tosend[0][0]='.';
	tosend[0][1]='/';
	tosend[0][2]='e';
	tosend[0][3]='x';
	tosend[0][4]='e';
	tosend[0][5]='c';
	tosend[0][6]='2';
	tosend[0][7]='.';
	tosend[0][8]='o';
	tosend[0][9]='u';
	tosend[0][10]='t';
	tosend[0][11]='\0';

	int pid=fork(); 
	
	if(pid==0)
	{
		execvp("./exec2.out",tosend);
	} 
	else 
	{
		execlp("mkdir","mkdir","file",NULL);
	}
	
	
}
