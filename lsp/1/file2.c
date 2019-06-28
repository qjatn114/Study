#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd;
	
	fd = open("text.txt",O_CREAT,0644);
	printf("fd=%d\n",fd);

	return 0;
}
