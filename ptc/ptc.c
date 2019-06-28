#include <stdio.h>

int main(void)
{
	int a = 1023;
	unsigned char arr[8] ={0,};

	arr[6] = (unsigned char)(a & 0x0FF);
	arr[7] = (unsigned char)( (a >> 8) & 0x03);
	printf("%d   %d\n",arr[6],arr[7] );
	printf("%d\n",(int)arr[6] + (( (int)arr[7] <<8) ));
	return 0;
}
