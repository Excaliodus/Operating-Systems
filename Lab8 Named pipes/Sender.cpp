#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<fstream>
#include<iostream>
using namespace std;

int main()
{
	int res;
	int n;
	int length=5;
	ifstream fin("inptu.txt");
    if (fin.is_open())
    {
    	int arr[5];
    	for(int i=0; i<3; i++)
    	{
    		for(int j=0; j<length; j++)
    		{
    			fin>>arr[j];
    		}
    		res=open("fifo1", O_WRONLY);
			write(res, &arr, sizeof(int)*5);
    	}
	}
}

