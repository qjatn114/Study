#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int rand_init(void)
{
	srand(time(NULL));
	return rand() %9 +1;
}

void for_test(int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		printf("num = %d\n",i);
	}
}

int main(void)
{
	int num = rand_init();
	for_test(num);

	return 0;
}
