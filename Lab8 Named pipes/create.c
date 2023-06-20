//(Named Pipes) Write a C or C++ program that accepts a filename as  command line argument and send it to the child process. The child reads the data from the file which is the array of numbers and sends the array to the parent which calculates the palindromes from the arrays.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int res;
	res=mkfifo("fifo1",0777);
	printf("named pipe created\n");
}
