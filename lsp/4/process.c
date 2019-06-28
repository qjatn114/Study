#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("before\n");

	fork();
	
	printf("after\n");

	return 0;
}
