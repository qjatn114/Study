#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
	signal(SIGINT, SIG_IGN);
	pause();
	

	return 0;
}
