#include <iostream>
#include<fstream>
#include<string>
#include <unistd.h>
using namespace std;
int varcount=0;



int main()
{
int x=fork();
if(x==0)
{
	ifstream f1;
	f1.open("question1.txt");
	if(f1.is_open())
	{
		char temp;
		while(!f1.eof())
		{
			f1 >> temp;
			if (temp== 'a' || temp == 'e' || temp == 'i' || temp == 'o' || temp == 'u' || temp== 'A' || temp == 'E' || temp == 'I' || temp == 'O' || temp == 'U' )
			{
				varcount++;
			}
		}
		cout<<"Variable count is:  "<<varcount<<endl;
	}
	f1.close();
	}
	else if(x>0)
	{
		wait(NULL);
		if (x==0)
			cout<<"Program completed."<<endl;
	}
}
