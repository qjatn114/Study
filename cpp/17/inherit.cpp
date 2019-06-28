#include <iostream>
#include <string.h>

using namespace std;

class Person
{
private:
	int age;
	char name[20];
public:
	Person(int,char *);
	int getAge(void);
	char *getName(void);
};

Person::Person(int a,char *n)
{
	age = a;
	strcpy(name,n);
}

char *Person::getName(void)
{
	return name;
}

int Person::getAge(void)
{
	return age;
}

class Student : public Person		//상속
{
	char major[20];
public:
	Student(int,char *,char *);	// 상속받은 변수2개 + 본인 인자1개
	char *getMajor(void);
	void showInfo(void);
};

Student::Student(int a,char *n,char *m) : Person(a,n)	// a,n은 person에서 처리 m은 student에서처리
{
	strcpy(major,m);
}

char *Student::getMajor(void)
{
	return major;
}

void Student::showInfo(void)
{
	cout <<"name : "<<getName()<<endl;
	cout <<"age : "<<getAge() << endl;
	cout <<"major : " << getMajor() << endl;
}

int main(void)
{
	Student Kim(24,"Jeong","baeksoo");
	Kim.showInfo();

	return 0;
}
