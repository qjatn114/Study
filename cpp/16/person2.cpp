#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

class Person
{
private:

	int age;
	char name[30];
	char job[20];

public:	
	Person(int i);
	Person(char *s,char *c);
	void setAge(int i);
	int getAge(void);
	void setName(char *c);
	char *getName(void);
	void setJob(char *c);
	char *getJob(void);

};

Person::Person(int i)
{
	age = i;
}

Person::Person(char *s,char *c)
{
	cout << "I'm Person" <<endl;
	strcpy(name,s);
	strcpy(job,c);
}

void Person::setAge(int i)
{
	age = i;
}

int Person::getAge(void)
{
	return age;
}

void Person::setName(char *c)
{
	strcpy(name,c);
}

char *Person::getName(void)
{
	return name;
}

void Person::setJob(char *c)
{
	strcpy(job,c);
}

char *Person::getJob(void)
{
	return job;
}


int main(void)
{
	int age = 26;
	char name[30] = "BeomSoo";
	char job[20] = "BaekSoo";
	
	Person p1 = Person(age);
	Person p2 = Person(name,job);

	cout << "나이="<< p1.getAge() << endl;
	cout << "이름="<<p2.getName() << endl;
	cout <<"직업="<<p2.getJob()<<endl;

	return 0;
}
