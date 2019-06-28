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
//void (* test_test(void) ) (void) <-		

//           ..
// int (*) (void) test_test(void (*p) (void))   인자도 함수포인터 리턴도 함수포인터
int (* test_test(void (*p)(void) )) (void)
{
	printf("test_test\n");
	p();
	return num_test;
}
// ???? pof_test ????
// {
//	return test_test;
// }
// int (*) (void) test_test(void (*p) (void)
// int (*) (void) (*pof_test)(void (*o)(void) ) 리턴타입
// void (*)(void) 인자
// int (*)(void) (*)(void (*p)(void))
//     pof_test(void (*p)(void))
// int (*)(void) (*pof_test(void (*p)(void) )) (void (*)(void))
// int (*(* pof_test(void (*p)(void)))(void (*)(void)))(void)

int ( * ( * pof_test( void (*p)(void) ) ) ( void (*)(void) ) ) (void)
{
	printf("pof_test\n");
	p();
	return test_test;
}

int main(void)
{
	int res = pof_test(test)(test)();
	printf("res = %d\n",res);

	return 0;
}

