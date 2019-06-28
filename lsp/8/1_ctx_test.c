#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void print_str(char *str)
{
	while(*str != '\0' )
	{
		putchar(*str++);
		fflush(stdout);
	}
}

int main(void)
{
	if( !fork() )
	{
		print_str("----------------\n");
	}
	else
	{
		print_str("++++++++++++++++\n");
	}
	

	return 0;
}
