#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;
	off_t new_pos;
	char wbuf[32] = "test test test";
	char rbuf[32] = "";

	fd = open("reading.txt",O_RDWR);

	new_pos = lseek(fd,(off_t)10,SEEK_SET);

	printf("new_pos =  %ld\n",new_pos);
		
	read(fd,rbuf,sizeof(rbuf));

	printf("rbuf=%s\n",rbuf);

	close(fd);

	return 0;	
}
