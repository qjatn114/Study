#include <iostream>

using namespace std;

class Vector
{
	int x;
	int y;
	int z;
	int num_inner;

public:
	Vector(int,int,int);
	Vector operator+(Vector &);
	Vector operator-(Vector &);
	friend Vector operator*(int ,Vector &);
	Vector operator*(int);
	Vector inner(Vector &);
	void print(Vector &);
};

Vector::Vector(int x,int y,int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector Vector::operator+(Vector &p)
{
	Vector tmp(x+p.x,y+p.y,z+p.z);
	return tmp;
}

Vector Vector::operator-(Vector &p)
{
	Vector tmp(x-p.x,y-p.y,z-p.z);
	return tmp;
}

Vector operator*(int val,Vector &p)
{
	return p*val;
}
Vector Vector::operator*(int val)
{
	Vector tmp(val*x,val*y,val*z);
	return tmp;
}

Vector Vector::inner(Vector &p)
{
	num_inner = x*p.x + y*p.y +z*p.z;
	return *this;
}

void Vector::print(Vector &p)
{
	cout << "x=" <<x<< "y= "<<y << "z = "<< z<<"num_inner = "<<num_inner<<endl;
}


int main(void)
{
	Vector p1(1,2,3);
	Vector p2(4,5,6);
	Vector p3 = p1+p2;
	p3.print(p3);
	Vector p4 = 5 * p1;
	p4.print(p4);
	Vector p5 = p1.inner(p2);
	p5.print(p5);

	return 0;
}
