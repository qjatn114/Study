#include <stdio.h>

#define IM	(1 <<4)
#define COEF	( (IM) - 1)


int and_not(int num)
{
	return num & ~( (1 << 12) - 1 );
}

int main(void)
{
	int res = and_not(4095);
	
	printf("res =%d\n",res);
	
	res = and_not(7183);
	printf("res = %d\n",res);

	res = and_not(4222);
	printf("res =%d\n",res);

	res = and_not(99999);
	printf("res =%d\n",res);

	res = and_not(8888);
	printf("res =%d\n",res);
	
	return 0;
}
