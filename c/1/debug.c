#include <stdio.h>



#if __SPECIAL__
int mult(int num)
{
	return num <<1;
/*
	return num * 2;
*/
}
#endif

int main(void)
{
	int res;
	int num1 = 3;

	res = mult(num1);
	printf("res = %d\n",res);
	
	return 0;
	
}
