#include <stdio.h>

int mult(int num)
{
	return num*2;
}

int main(void)
{
	int res;
	int num1 = 3;
	res = mult(num1);
	printf("res = %d\n",res);
	printf("check (char *) = %lu\n",sizeof(char *));
	printf("Check (int *) = %lu\n",sizeof(int *));
	printf("Check (float *) = %lu\n",sizeof(float *));
	printf("Check (double *) = %lu\n",sizeof(double *));
	return 0;
}


