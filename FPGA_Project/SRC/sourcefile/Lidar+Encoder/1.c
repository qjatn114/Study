#include <stdio.h>

void func(int *data)
{
	*data =20;
}

int main(void)
{

	int data=10;
	
	func(&data);

	printf("%d\n",data);

	return 0;
}
