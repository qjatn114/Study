#include <stdio.h>


int BSearch(int *arr,int first,int last,int target);

int main(void)
{
	int arr[] = {1,3,5,6,8,9};
	int idx;


	idx = BSearch(arr,0,sizeof(arr)/sizeof(int)-1,7);
	if(idx == -1)
		printf("fail\n");
	else
		printf("%d\n",idx);

	idx = BSearch(arr,0,sizeof(arr)/sizeof(int)-1,5);
	if(idx == -1)
		printf("fail\n");
	else
		printf("%d\n",idx);


	return 0;
}

int BSearch(int *arr,int first,int last,int target)
{
	int mid;
	
	if(first > last)
		return -1;
	
	mid = (first + last)/2;

	if(arr[mid] == target)
		return mid;
	else if(arr[mid] < target)
		BSearch(arr,mid+1,last,target);
	else
		BSearch(arr,first,last-1,target);
}
