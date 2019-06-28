#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;
	fd = open("reading.txt",O_CREAT | O_RDWR);

	close(fd);

	return 0;
}
