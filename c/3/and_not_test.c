#include <stdio.h>

#define IM	(1 <<4)
#define COEF	( (IM) - 1)


int and_not(int num)
{
	return num & ~( (1 << 4) - 1 );
}

int main(void)
{
	int res = and_not(33);
	
	printf("res =%d\n",res);
	
	res = and_not(0xa0);
	printf("res = %d\n",res);

	res = and_not(65);
	printf("res =%d\n",res);

	res = and_not(63);
	printf("res =%d\n",res);

	res = and_not(21);
	printf("res =%d\n",res);
	
	return 0;
}
