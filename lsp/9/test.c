#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd;
	char buf[32]= "";
	int len;

	len = read(0,buf,strlen(buf));
	printf("%s\n",buf);

	return 0;
}
