#include <stdio.h>


int b(int a,int b)
{
	printf("Success\n");
}


int main(void)
{
	void (*a)(int) =b;
	a(1,2);

	return 0;
}
