#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<iostream>
using namespace std;

bool isPalindrome(int n)
{
	int reversed = 0, remainder, original;
    original = n;
    while (n != 0)
    {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    if (original == reversed)
    	return true;
    else
    	return false;
    return 0;
}

int main()
{
	int res, n;
	int arr[5];
	int length=5;
	for(int i=0; i<3; i++)
    {
    	res=open("fifo1",O_RDONLY);
		n=read(res,arr,sizeof(int)*5);
    	for(int j=0; j<length; j++)
    	{
    		if (isPalindrome(arr[j]))
    			cout<<arr[j]<<" ";
   		}
   		cout<<endl;
	}
}
