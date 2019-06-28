#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define TEST1		777777777
#define TEST2		2222222222
#define PTEST		250000000
#define T1		250000000/4
#define T2		250000000/2
#define T3		(25000000*3)/4
int arr[PTEST] = {7};
int init[PTEST];
int brr[PTEST] = {7};


typedef struct timeval tv;

void *t1(void *x)
{
	int i;	
	int result=0;
	for(i=0;i<T1;i++)
	{
		arr[i] = init[i] + arr[0];
		result += init[i];
	}
	arr[T1-1] = reslut;
}
void *t2(void *x)
{
	int i;
	
	for(i=T1;i<T2;i++)
	{
		arr[i] =  init[i];
		resultT2 += init[i];
	}
}
void *t3(void *x)
{
	int i;
	
	for(i=0;i<T3;i++)
	{
		arr[i] = init[i];
		resultT3 += init[i];
	}
}
void *t4(void *x)
{
	int i;
	
	for(i=T3;i<PTEST;i++)
	{
		arr[i] = init[i];
		resultT4 += init[i];
	}
	arr[PTEST -1] = arr[0] + resultT1 + resultT2 + resultT3 + resultT4;
}
int get_runtime(tv start, tv end)
{
	end.tv_usec = end.tv_usec - start.tv_usec;
	end.tv_sec = end.tv_sec - start.tv_sec;
	end.tv_usec += end.tv_sec * 1000000;

	printf("run time = %.9lf sec\n",end.tv_usec/1000000.0);

	return end.tv_usec / 1000000.0;
}

int main(void)
{
	pthread_t A,B,C,D;
	unsigned int i , cnt = 0;
	tv start,end;

	srand(time(NULL));
	for(i=0;i<PTEST;i++)
		init[i] = rand() %10 +1;

	gettimeofday(&start,NULL);
	
	for(i=1;i<PTEST;i++)	
	{
			brr[i] = brr[i-1] + init[i];
	}
	printf("brr[%d] = %d\n",PTEST-1,brr[PTEST-1]);
	gettimeofday(&end,NULL);

	get_runtime(start,end);


	pthread_create(&A,NULL,t1,NULL);
	pthread_create(&B,NULL,t2,NULL);
	pthread_create(&C,NULL,t3,NULL);
	pthread_create(&D,NULL,t4,NULL);


	gettimeofday(&start,NULL);
	
	pthread_join(A,NULL);
	pthread_join(B,NULL);
	pthread_join(C,NULL);
	pthread_join(D,NULL);
	gettimeofday(&end,NULL);

	printf("arr[%d] = %d\n",PTEST-1 , arr[PTEST-1]);

	get_runtime(start,end);
	
	return 0;
}
