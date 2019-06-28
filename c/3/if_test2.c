#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int init_val(void)
{
	//1-9
	return rand() % 9 +1;
}

void Check_num(int num)
{
	if(num ==0)
	{
		printf("num은 0이다\n");
	}
	else if(num %2)
	{
		printf("num은 홀수\n");
	}
	else
	{
	printf("num은 짝수\n");
	}

}

int main(void)
{
	int num;

	srand(time(NULL));
	
	num = init_val();	
	printf("num = %d\n",num);
	Check_num(num);

	return 0;
}
