#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
using namespace std;

void writeToFile(int min, int max, float avg, char *fileName) 
{
    ofstream file;
    file.open(fileName);
    file << "Min: " << min << endl;
    file << "Max: " << max << endl;
    file << "Avg: " << avg << endl;
    file.close();
}

int main(int argc, char *argv[])
{
	int min = 99999;
	int max= -99999;
	float avg=0;
	int numCount=0;
	for( int j=1;  j<argc-1;j++)
	{
		int temp = atoi(argv[j]);
		if (temp>max)
		{
			max=temp;	
		}
		if (temp<min)
		{
			min=temp;
		}
		avg+=temp;
		numCount++;
	}
	if (avg<50)
	{
		return 0;
	}
	int i= fork();
	if (i==0)
	{
		avg = avg/numCount;
		cout << "Child Process: " << endl;
        cout << "Min: " << min << endl;
        cout << "Max: " << max << endl;
        cout << "Avg: " << avg << endl;
        exit(0);
	}
	else 
	{
		int status;
		waitpid(i, &status, 0);
        cout << "Parent Process: " << endl;
        cout << "Results written to file: " << argv[argc - 1] << endl;
        writeToFile(min, max, avg / numCount, argv[argc - 1]);
    }
}
