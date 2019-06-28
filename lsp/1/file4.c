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
	int i=0;
	int len;

	char text[64] = "Hello Linux System Programming!";

	len = strlen(text);
	printf("len = %d\n",len);
		
	fd = open("text.txt",O_CREAT| O_WRONLY,0644);
	printf("fd=%d\n",fd);

	while(i<31)
		write(fd,&text[i++],1);

	close(fd);

	return 0;
}
