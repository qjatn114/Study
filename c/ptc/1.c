#include <stdio.h>


int main(void)
{
	char str[][4] = {"abc","def","ghi"};

	printf("%s\n",*str);
	printf("%s\n",*(str+1));
	printf("%s\n",*(str+2));

	return 0;
}
