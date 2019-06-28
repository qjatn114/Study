#include <iostream>
#include <string.h>

using namespace std;

class Samsung
{
private:
	int money;
	char company[30];
public:
	Samsung(int,char *);
	int getMoney(void);
	char *getCompany(void);
};

Samsung::Samsung(int m,char *c)
{
	money = m;
	strcpy(company,c);
}

int Samsung::getMoney(void)
{
	return money;
}

char *Samsung::getCompany(void)
{
	return company;
}

class Child : public Samsung
{
	char who[20];
public:
	Child(int,char *,char *);
	char *getWho(void);
	void showInfo(void);
};

Child::Child(int m,char *c,char *w) : Samsung(m,c)
{
	strcpy(who,w);
}

char *Child::getWho(void)
{
	return who;
}
void Child::showInfo(void)
{
	cout << "who : " << getWho() << endl;
	cout << "money : " << getMoney() <<"원"<< endl;
	cout << "company : " << getCompany() << endl;
}


int main(void)
{
	Child a(2100000000,"Everland","JaeYoung");
	a.showInfo();


	return 0;
}
