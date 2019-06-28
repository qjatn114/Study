#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int rand_init(void)
{
	srand(time(NULL));
	return rand() % 10 +1;
}

void while_test(int num)
{
	int cnt = 0;
	while(num--)
	{
		cnt++;
	}
	printf("cnt = %d\n",cnt);
}

void find_even(int num)
{
	int cnt = 1;
	while(cnt <= num)
	{
		if(!(cnt % 2))
		{
			printf("%4d",cnt);
		}
		cnt++;
	}
}

int main(void)
{
	int num = rand_init();
	printf("num = %d\n",num);
	
	while_test(num);
	find_even(num);

	return 0;
}
