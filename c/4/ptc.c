#include<stdio.h>


void arr_init(int (*arr)[2]);







int main(void)
{
	int arr[3][2] = {0};
	int *prr[3] = {0};
	int (*p)[2] = NULL;
	arr_init(arr);
	prr[0] = arr[0];
	prr[1] = arr[1];
	prr[2] = arr[2];
	
	
	printf("%d\n",*(*prr)+1);
	printf("%d\n",*prr[1]);
	printf("%d\n",*prr[2]);	

	return 0;
}



void arr_init(int (*arr)[2])
{
	int i,j;
	int cnt=1;

	for(i=0;i<3;i++)
	{
		for(j=0;j<2;j++)
		{
			arr[i][j] = cnt++*2;
		//	printf("arr[%d][%d]= %d\n",i,j,arr[i][j]);
		}
	}
//	printf("arr %d \n",**arr);
}
