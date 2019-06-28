#include <stdio.h>


int fib(int n)
{
	int  tmp,first=1,second=1;

	#if 0
	
	if문은 조건문임
	조건을 만족하면 if문 아래로 들어가고
	조건을 만족하지 못하면 if문 안으로 들어가지 않음
	즉 n이 2 보다 작거나 같으면 이라는 조건이 참이면 1
	해당 조건을 만족하지 모샇면 그냥 아래쪽으로 내려감
	#endif


	if(n<=2)
		return 1;
	
	n -= 2;
	
	#if 0
	
	while문도 if문이랑 비슷하지만 차이점이 있음
	if문의 경우에는 비교를 한 번만 수행하는 반면
	while문의 경우에는 조건이 만족하는 한 계속해서
	동일한 작업을 반복


	#endif
	while(n--)
	{
		tmp = first + second;
		first = second;
		second = tmp;
	}
	return tmp;
}



int main(void)
{
	int res;
	res = fib(5);
	printf("res = %d\n",res);

	return 0;
}
