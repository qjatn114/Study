#include <stdio.h>
#include <string.h>
#include <signal.h>

extern char *dev0;
int fd;

void call_exit(int signo)
{
	close_dev(fd);
}

int main(void)
{
	int ret;
	fd = serial_config(dev0);
	signal(SIGINT,call_exit);

		for(;;)
			recv_data(fd);

	return 0;
}

