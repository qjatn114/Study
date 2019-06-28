#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int rand_init(void)
{
	int res;
	srand(time(NULL)); 
	res = rand() % 10 +1;
	printf("res = %d\n",res);

	return res;
}

void arr_init(int arr[10],int num)	// arr 주소가 넘어오는데 arr[10]으로 받을 수?
{
	int i;

	for(i=0; i<num;i++)
	{
		arr[i] = i;
	}
}

void arr_print(int arr[10],int len)	//배열은 지역변수가 아닌가??
{
	int i;
	for(i=0;i<len;i++)
	{
		printf("arr[%d] = %d\n",i,arr[i]);
	}
}


int main(void)
{
	// {0} 자동으로 전부 0으로 초기화
	int arr[10] = {0};
		
	// 배열의 이름은 주소
	arr_init(arr,rand_init());	//rand_init()이 먼저 동작
	arr_print(arr,sizeof(arr)/sizeof(int));

	return 0;
}
