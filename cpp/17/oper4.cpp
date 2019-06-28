#include <iostream>

using namespace std;

class Point
{
private:
	int x,y;

public:
	Point(int,int);
	void showXY(void);
	Point operator+(int);
	friend Point operator+(int, Point &);
};

Point::Point(int x,int y)
{
	this->x = x;
	this->y = y;
}

void Point::showXY(void)
{
	cout << x << ", "<< y<< endl;
}

Point Point::operator+(int val)
{
	Point tmp(x+val,y+val);
	return tmp;
}

Point operator+(int val,Point &p)
{
	return p+val;			//이 함수가 위에 operator+(int val)를 호출해서 실행
}

int main(void)
{
	Point p1(3,7);
	Point p2 = p1+3;
	p1.showXY();
	
	Point p3 = 7 + p2;
	p3.showXY();

	return 0;
}
