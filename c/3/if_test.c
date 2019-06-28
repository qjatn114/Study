#include<stdio.h>
#include<stdbool.h>

bool is_it_even(int value)
{
	if(value %2 )
		return false;
	
	return true;
}


int main(void)
{
	if(is_it_even(3))
	{
		printf("이것은 짝수 \n");
	}
	else
	{
		printf("이것은 홀수\n");
	}

	return 0;
}
