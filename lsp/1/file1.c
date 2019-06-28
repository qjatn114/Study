#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
	int fd;
	
	fd = open("text.txt",O_CREAT);
	printf("fd=%d\n",fd);

	close(fd);
	return 0;
}
