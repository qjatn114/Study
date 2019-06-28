#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int fd,len,nr;
	char buf[100] ="";

	fd = open("readtest.txt",O_CREAT | O_RDWR,0644);
	len = sizeof(buf);
	
	while(len !=0 && (nr = read(fd,buf,len)) != 0)
	{
		len -= nr;
		buf = & buf[nr];
	}
	printf("%s\n",buf);

	close(fd);	

	return 0;
}
