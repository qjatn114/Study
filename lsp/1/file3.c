#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int fd;
	int nw;
	char text[64] = "Hello Linux System Programming!";
		
	fd = open("text.txt",O_CREAT| O_WRONLY,0644);
	printf("fd=%d\n",fd);

	nw = write(fd,text,strlen(text)+1);
	printf("nw = %d\n",nw);
	
	write(fd, text,strlen(text)+1);
	close(fd);

	return 0;
}
