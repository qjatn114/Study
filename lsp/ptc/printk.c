#include <stdio.h>

int main(void)
{
	printk("[+]process : %s\n",current->comm);
	printk("[+][debug] message [F:%s, L:%d]: caller:(%pS)\n",__func__,__LINE__,(void *)_builtin_return_address(0));

	return 0;
}
