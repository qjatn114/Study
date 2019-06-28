#include<stdio.h>

int main(void)
{
	unsigned char num = 10;
	char num2 = 10;
	printf("not num = %u\n",(unsigned)~num);
	printf("not num2 = %u\n",(char)~num2);
	return 0;
}
