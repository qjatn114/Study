#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc,char *argv[])
{
	int nr;
	int sfd,dfd;
	char buf[256] = {0};

	sfd = open(argv[1],O_RDONLY);
	//dfd = open(argv[2],O_CREAT | O_RDWR | O_TRUNC,0644);
	dfd = open(argv[2],O_WRONLY);
	
	lseek(dfd,0,SEEK_END);
	
	while(nr = read(sfd,buf,sizeof(buf)))
		write(dfd,buf,nr);

	close(sfd);
	close(dfd);	


	return 0;
}
