#include <stdio.h>

#define SIGINT	(2)

typedef void (*handler_t)(int);
handler_t signal(int, handler_t);

handler_t old;

void linux_sig(int signo)
{
	printf("linux_sig(%d)\n",signo);
	signal(SIGINT,old);
}

int main(void)
{
	old = signal(SIGINT,linux_sig);
	while(1)
		;
	return 0;
}
