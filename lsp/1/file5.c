#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int rfd,wfd;
	int nr;
	int i=0;
	int len;

	//char text[64] = "Hello Linux System Programming!";
	char buf[64] = {0};
		
	rfd = open("reading.txt",O_RDONLY,0644);
	wfd = open("test.txt",O_CREAT | O_RDWR | O_TRUNC,0644);
	printf("rfd=%d wfd = %d\n",rfd,wfd);

	while((nr = read(rfd,buf,sizeof(buf)))>0)
	{
		printf("nr = %d\n",nr);
//		write(wfd,buf,nr);
		printf("buf = %s\n",buf);
	}
	close(rfd);
	close(wfd);

	return 0;
}
