#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int i;
	int fd;
	off_t new_pos;
	off_t trans;
	char wbuf[32] = "how how how";
	char rbuf[575]="";
	char chg[10]="test";	
	fd = open("reading2.txt",O_RDWR);

	new_pos = lseek(fd,(off_t)0,SEEK_END);
	trans = lseek(fd,(off_t)0,SEEK_SET);	
	printf("new_pos =  %ld\n",new_pos);
	printf("trans= %ld\n",trans);
		
	read(fd,rbuf,sizeof(rbuf));

	for(i=0;i<new_pos;i++)
	{
		if(rbuf[i]=='t'&rbuf[i+1]=='e')
		{
			trans = lseek(fd,(off_t)i,SEEK_SET);
			printf("%d\n",i);	
			write(fd,wbuf,sizeof(wbuf));
			break;
		}
	}

	printf("rbuf=%s\n",rbuf);

	close(fd);

	return 0;	
}
