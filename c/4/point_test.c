#include <stdio.h>

int main(void)
{
	int *p = NULL;
	int num = 3;
	p = &num;

	// tqb size adjustmean(탭 크기 조정) =>>> 명령 모드에서 :set te=4

	printf("num = %d\n",num);
	printf("*p = %d\n",*p);

	return 0;
}	
