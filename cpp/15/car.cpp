#include <iostream>
#include <string.h>

using namespace std;

class Car
{
public:

	int speed;
	char color[32];

	void setSpeed(int);
	int getSpeed(void);
	void setColor(char *);
	char *getColor(void);
};

void Car::setSpeed(int s)
{
	speed = s;
}

int Car::getSpeed(void)
{
	return speed;
}

void Car::setColor(char *c)
{
	strcpy(color,c);
}

char *Car::getColor(void)
{
	return color;
}


int main(void)
{
	Car c = Car();		// Car() <-생성자
	
	c.setSpeed(180);
	cout << "speed" << c.getSpeed() <<endl;

	c.setColor("파랑");
	cout <<"색상="<< c.getColor() <<endl;

	return 0;
}
