#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void my_sig(int signo)
{
	printf("my_sig signo : %d \n ",signo);
	exit(-1);
}

void my_sig2(int signo)
{
	printf("my_sig2 signo : %d\n",signo);
	exit(-1);
}

int main(void)
{
	void (*old_p)(int);
	void (*old_p2)(int);

	old_p =  signal(SIGINT, my_sig);
	pause();
	old_p2 = signal(SIGINT, my_sig2);
	pause();
	signal(SIGINT, old_p2);
	pause();

	for(;;)
		pause();	
	
	return 0;
}
