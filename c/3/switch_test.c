#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int rand_init(void)
{
	srand(time(NULL));
	return rand() % 3 +1;
}

void switch_test(int num)
{
	switch(num)
	{
		case 1:
			printf("1 Datacted\n");
			break;
		case 2:
			printf("2 Datacted\n");
			break;
		default:
			printf("Wrong Number\n");
			break;
	}
}

int main(void)
{
	int num = rand_init();
	printf("num = %d\n",num);
	switch_test(num);

	return 0;
}
