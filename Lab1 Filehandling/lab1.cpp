#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
char temp;
string sen;
	ifstream fin("input.txt");
	if (fin.is_open())
	{
	ofstream MyFile("output.txt");
	int i=0;
		while (!fin.eof())
		{
			fin>>temp;
			if (temp <'0'|| temp >'9')
				temp=' ';
			sen=sen+temp;
		}
	MyFile<<sen;
	MyFile.close();
	}
	int max=0;
	int temp1;
	ifstream oin("output.txt");
	if (oin.is_open())
	{
		while (!oin.eof())
		{
			oin>>temp1;
			if (temp1>max)
				max=temp1;
		}
		oin.close();
	}
	ifstream gin("output.txt");
	if (gin.is_open())
	{
		while (!gin.eof())
		{
			gin>>temp1;
			cout<<temp1<<" ";
		}
		gin.close();
	}
	cout<<endl<<"Max number is: "<<max<<endl;
}
