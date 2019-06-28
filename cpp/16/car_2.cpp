#include <iostream>
#include <string.h>

using namespace std;

class Car
{
private:

	int speed;
	char color[32];

public:

	Car(void);
	Car(int speed,char *c);
	void setSpeed(int s);
	int getSpeed(void);
	void setColor(char *c);
	char *getColor(void);

#if 0
내 코드
	Car(void)		//생성자
	{
		cout << "i'm Car!!"<<endl;
		setSpeed(100);
		setColor("Green");
		//strcpy(color,"blue");

	}
	void setSpeed(int s);
	int getSpeed(void);
	void setColor(char *c);
	char *getColor(void);
#endif

};

Car::Car(void)
{
	cout <<"I'm Car Default Constructor!!!"<<endl;
}

Car::Car(int s,char *c)
{
	speed = s;
	strncpy(color,c,strlen(c));
	cout << "I'm Car Default Consrtuctor too" <<endl;
}

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
	Car c = Car();		// Car() <-생성자	이때 Car(void) 실행
	
	c.setSpeed(180);
	cout << "speed=" << c.getSpeed() <<endl;

	c.setColor("파랑");
	cout <<"색상="<< c.getColor() <<endl;

	char color[32] = "빨강";
	Car c2 = Car(200,color);		// 이 때 Car(int s,char *c)실행
	cout << "Speed="<<c2.getSpeed() <<endl;
	cout << "색생="<<c2.getColor()<<endl;

	return 0;
}
