#include <stdio.h>




// void (*) (void)
void test(void)
{
	printf("test\n");
}


int num_test(void)
{
	printf("num_test\n");
	
	return 7;
}


// int (*p)[3]    vs   int *p[3]
// int [3](*) p   vs   (int *)[3] p
// int [3]* p   vs   (int *)[3] p




// void (*) (void) test_test(void)
//void (* test_test(void) ) (void)		


// int (*) (void) test_test(void (*p) (void))   인자도 함수포인터 리턴도 함수포인터
int (* test_test(void (*p)(void) )) (void)
{
	printf("test_test\n");
	p();
	return num_test;
}

int main(void)
{
	int res = test_test(test)();
	printf("res = %d\n",res);

	return 0;
}

