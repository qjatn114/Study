#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

int init_num(void)
{
	return rand() %33 + 1;
}

bool Check_num(int num,int c1, int c2)
{
	if( !(num % c1) || !(num % c2))
	{
		return true;
	}
	return false;
}

int main(void)
{
	int num;

	srand(time(NULL));

	num = init_num();
	
	printf("num = %d\n",num);

	if(Check_num(num,2,3))
	{
		printf("이것은 2 혹은  3의 배수\n");
	}
	else
	{
		printf("이것은 2 혹은  3의 배수가 아님\n");
	}

	return 0;

}
