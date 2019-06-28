#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

class Person
{
public:

	int age;
	char name[30];
	char job[20];
	
	void setAge(int i);
	int getAge(void);
	void setName(char *c);
	char *getName(void);
	void setJob(char *c);
	char *getJob(void);

};



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
	Person p = Person();
	
	p.setAge(26);
	cout << "Age=" <<p.getAge() <<endl;

	p.setName("정범수");
	cout <<"이름 = "<<p.getName()<<endl;

	p.setJob("개발자");
	cout <<"직업 :"<<p.getJob() <<endl;

	return 0;
}
