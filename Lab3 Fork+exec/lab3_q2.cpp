#include <iostream>
#include<unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *argv[])
{
	int i =fork();
	if (i==0)
	{
		int x= execlp("./hello.out","Hello",NULL);
	}
	else
	{
		wait(NULL);
		cout<<"Program completed"<<endl;
	}
	return 0;
}
