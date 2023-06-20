#include<iostream>
#include<string.h>
#include<string>
#include<math.h>
using namespace std;

class process {
public:
	int exc;
	int period;
	process()
	{
		exc = 0;
		period = 0;
	}
};
process* p;

void printscale(int*arr,int end)
{
	for (int m = 0; m < end; m++)
	{
		if (arr[m] == 99)
		{
			cout << " !!!";
		}
		else	
		cout << " " << "P" <<arr[m] << " ";
	}
	cout << endl;
	for (int i = 0; i <= end; i++)
	{
		cout << i << "___";
		if (i == end)
		{
			cout << "|" << endl;	
		}
	}
}

void ratemon(int num)
{
	cout << "RATE MONOTONIC" << endl;
	bool* done = new bool[num];
	for (int i = 0; i < num; i++)
	{
		done[i] = false;
	}
	int time = 0;
	int end = p[num - 1].period;
	int l = 0;
	process* p1 = new process[num];
	for (int i = 0; i < num; i++)
	{
		p1[i].exc = p[i].exc;
		p1[i].period = p[i].period;
	}
	process* p2 = new process[num];
	for (int i = 0; i < num; i++)
	{
		p2[i].exc = p[i].exc;
		p2[i].period = p[i].period;
	}
	int count = 0;
	int limit = 0;
	int c = 0;
	int* result = new int[end];
	while(time<=end)
	for (int i = 0; i < num; i++)
	{ 
		if (time > end)
		{
			break;
		}
		
		if(count < p1[i].exc && done[i] == false)
			while (count < p1[i].exc && done[i] == false)
			{
				c = 0;
				time++;
				if (time > end)
				{
					break;
				}
				count++;
				result[limit] = i;
				l = i;
				limit++;
				for (int k = 0; k < l; k++)
				{
					if (time == p1[k].period)
					{
						done[k] = false;
						p1[k].period = p1[k].period + p[k].period;
					}
				}
				for (int k = 0; k < i; k++)
				{
					int check = 0;
					if (time == p2[k].period)
					{
						p2[k].period = p1[k].period;
						if (count < p1[i].exc)
						{
							p1[i].exc = p1[i].exc - count;
						}
						else
						{
							done[i] = true;
							p1[i].exc = p[i].exc;
						}
						check++;	
					}
					if (check!=0)
					{
						i = k;
						count = 0;
						break;
					}
				}	
			}
		else 
		{
			int z;
			int ch = 0;
			for ( z = 0; z< num; z++)
			{
				if (done[z] == true)
				{
					ch++;
				}
			}
			if (ch == z)
			{
				c = 100;
				time++;
				result[limit] = 99;
				limit++;
				int n = 1000;
				for (int k = 0; k < num; k++)
				{
					if (time == p1[k].period)
					{
						done[k] = false;
						if (n > k)
						{
							n = k;
						}
						p1[k].period = p1[k].period + p[k].period;
					}
				i = n - 1;
				}
			}
			count = 0;
			if(c!=100)
			if (time <= p1[i].period)
			{
				done[i] = true;
				p1[i].exc = p[i].exc;
			}
	}
	printscale(result, p[num - 1].period);
}

void sorting(int n)
{
	int i, j;
	process p1;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (p[j].period > p[j + 1].period)
			{
				p1.exc = p[j].exc;
				p1.period = p[j].period;
				p[j].exc = p[j + 1].exc;
				p[j].period = p[j + 1].period;
				p[j + 1].exc = p1.exc;
				p[j + 1].period = p1.period;
			}
}

void edf(int num)
{
	cout << "EARLIEST DEADLINE FIRST" << endl;
	bool* done = new bool[num];
	for (int i = 0; i < num; i++)
	{
		done[i] = false;
	}
	int time = 0;
	int end = p[num - 1].period;
	int l = 0;
	process* p1 = new process[num];
	for (int i = 0; i < num; i++)
	{
		p1[i].exc = p[i].exc;
		p1[i].period = p[i].period;
	}
	process* p2 = new process[num];
	for (int i = 0; i < num; i++)
	{
		p2[i].exc = p[i].exc;
		p2[i].period = p[i].period;
	}
	int count = 0;
	int limit = 0;
	int c = 0;
	int* result = new int[end];
	while (time <= end)
		for (int i = 0; i < num; i++)
		{
			if (time > end)
			{
				break;
			}
			if (count < p1[i].exc && done[i] == false)
			while (count < p1[i].exc && done[i] == false)
			{
				c = 0;
				time++;
				if (time > end)
				{
					break;
				}
				count++;
				result[limit] = i;
				l = i;
				limit++;
				for (int k = 0; k < l; k++)
					if (time == p1[k].period)
					{
						done[k] = false;
						p1[k].period = p1[k].period + p[k].period;
					}
				for (int k = 0; k < i; k++)
				{
					int check = 0;
					if (time == p2[k].period)
					{
						p2[k].period = p1[k].period;
						if (p1[i].period == p1[k].period&&count!=p1[i].exc)
						{
							break;
						}
						if (count < p1[i].exc)
						{
							p1[i].exc = p1[i].exc - count;
						}
						else
						{
							done[i] = true;
							p1[i].exc = p[i].exc;
						}
						check++;
					}
					if (check != 0)
					{
						i = k;
						count = 0;
						break;
					}
				}
			}
			else
			{
				int z;
				int ch = 0;
				for (z = 0; z < num; z++)
				{
					if (done[z] == true)
					{
						ch++;
					}
				}
				if (ch == z)
				{
					c = 100;
					time++;
					result[limit] = 99;
					limit++;
					int n = 1000;
					for (int k = 0; k < num; k++)
						if (time == p1[k].period)
						{
							done[k] = false;
							if (n > k)
							{
								n = k;
							}
							p1[k].period = p1[k].period + p[k].period;
						}
					i = n - 1;
				}
			}
			count = 0;
			if (time < p1[i].period)
			{
				done[i] = true;
				p1[i].exc = p[i].exc;
			}
		}	
	printscale(result, p[num - 1].period);
}

int main()
{
	int no = 0;
	cout << "ENTER THE NUMBER OF PROCESSES " << endl;
	/*cin >> no;*/
	no = 4;
    p = new process[no];
	/*if (no > 0)
	{
		int i = 0;

		cout << "ENTER THE FOLLOWING DETAILS FOR EACH PROCESS :" << endl;
		while (i<no)
		{ 
			cout << "TIME PERIOD FOR PROCESS " << i << " :";
			cin >> p[i].period;
			cout << "EXECUTION TIME FOR PROCESS " << i << " :";
			cin >> p[i].exc;
			i++;
			cout << endl;
	    }
	}*/
	p[0].period = 6;
	p[0].exc = 2;
	p[1].period = 12;
	p[1].exc = 3;
	p[2].period = 18;
	p[2].exc = 5;
	p[3].period = 24;
	p[3].exc = 6;
	sorting(no);
	ratemon(no);
	cout << endl;
	edf(no);
	float ut=0, u=0, x=0, y = 0;
	for (int i = 0; i < no; i++)
	{
		x = p[i].exc / p[i].period;
		ut += x;
	}
	y = float(no);
	y = y * ((pow(2.0, 1 / y)) - 1);
	u = y;
	cout << endl;
	if (ut < u)
	{
		cout << "IT IS SCHEDULABLE" << endl;
	}
	else
	{
		cout << "NOT SURE" << endl;
	}
	return 0;
}
