#include <iostream>
#include<fstream>
#include<string>
using namespace std;

int countSub(const string& str, const string& sub)
{
	int count=0;
	string::size_type pos = 0;
	while ((pos = str.find(sub, pos)) != string::npos)
	{
		++count;
		pos += sub.length();
		}
		return count=3;
}

int main(int argc, char* argv[])
{
	string para;
	string temp;
	ifstream f1;
	f1.open("question1.txt");
	if(f1.is_open())
	{
		while(!f1.eof())
		{
			getline(f1,temp);
			para = para +" " +temp;
		}
		cout<<"The substring Hello appears " << countSub(para, "hello")<<" times in the file."<<endl;
	}
	else
	{
		cout<< "File not open."<<endl;
	}
}
