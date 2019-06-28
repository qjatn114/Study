#include<iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>



using namespace std;


class Sample
{
private:
	float time[256];
	int velocity[256];
	
public:
	Sample(void);
	void setTime(void);
	void setVel(void);
	void printData(void);
	friend float integral(Sample &s);
};

Sample::Sample(void)
{
	int i;
	cout << "Im Default Constructor"<<endl;

	for(i=0;i<256;i++)
	{
		time[i] = pow(10,-3);
		velocity[i] = rand() %200 -75;
	}
}


void Sample::setTime(void)
{
	int i;
	for(i=0;i<256;i++)
	{
		time[i] = pow(10,-3);
	}
}

void Sample::setVel(void)
{
	int i;
	for(i=0;i<256;i++)
	{
		velocity[i] = rand()%201-100;
	}
}

void Sample::printData(void)
{
	int i;
	for(i=0;i<256;i++)
		cout <<"vel="<< velocity[i] << "m/s"<< endl;
}

float integral(Sample &s)
{
	int i;
	float sum = 0.0f;

	for(i=0;i<255;i++)
	{
		sum +=( (s.velocity[i+1] + s.velocity[i])*s.time[i])/2.0f;
	}
	return sum;
}

int main(void)
{
	srand(time(NULL));

	Sample s;
	s.printData();
	cout << "replacement = "<< integral(s) << "m" << endl;
	
	return 0;	
}
