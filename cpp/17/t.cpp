#include <iostream>
#include <string.h>

using namespace std;

class GHL
{
private:
	char copporate[32];
	int stock;
	int money;
public:
	GHL(char *,int,int);
	char *getCopporate(void);
	int getStock(void);
	int getMoney(void);
};

GHL::GHL(char *c,int s,int m)
{
	strcpy(copporate,c);
	stock =s;
	money = m;
}

char *GHL::getCopporate(void)
{
	return copporate;
}

int GHL::getMoney(void)
{
	return money;
}

int GHL::getStock(void)
{
	return stock;
}

class JYL : public GHL
{
	char nick[32];
public:
	JYL(char *,char *,int,int);
	char *getNick(void);
	void showInfo(void);
};

JYL::JYL(char *n,char *c,int s,int m) : GHL(c,s,m)
{
	strcpy(nick,n);
}

char *JYL::getNick(void)
{
	return nick;
}

void JYL::showInfo(void)
{
	cout << "nickname :"<<getNick()<<endl;

	cout << "copporate :"<<getCopporate()<<endl;

	cout << "stock :"<<getStock()<<endl;

	cout << "money :"<<getMoney()<<endl;

}

int main(void)
{
	char nick[32] = "다이아 수저";
	char copor[32] = "삼성";

	JYL JaeYoung(nick,copor,21038990,2347892389);
	JaeYoung.showInfo();

	return 0;
}
