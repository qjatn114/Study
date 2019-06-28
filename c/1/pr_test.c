#include <stdio.h>


int func(int num1,int num2,int num3,int num4)
{
	int result;
	result = num3-num2;
	num4= num4<<1;
	result=result<<1;
	return num4+result;
}




int main(void)
{
	int num1 =1;
	int num2 =2;
	int num3 =3;
	int num4 =4;
	int result;

	result = func(1,2,3,4);
	printf("func = %d\n",result);

	return 0;
}
