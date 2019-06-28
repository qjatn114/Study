#include <stdio.h>

int main(void)
{
	int num1 = 1;
	float num2 = 2.2f;
	double num3 = 4.4;

	printf("num * num = %lf\n",num1 * num2);
	printf("num / num = %lf\n",num2 / num3);
	printf("num1 %%7 = %d\n",num1 % 7);
	printf("num1 %%2 = %d\n",num1 % 2);

	return 0;
}

