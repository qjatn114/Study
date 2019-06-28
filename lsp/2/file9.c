#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
long replace_text(int fd,char *tstr,char *cstr)
{
	char buf[32] ={0};
	int len = strlen(tstr);
	int cnt=0;
	int nr;
	int i;

	while(nr = read(fd,buf,sizeof(buf)))
	{
		for(i=0;i<nr;i++)
		{
			if(!strncmp(&buf[i],tstr,4))
			{
				lseek(fd,(off_t)i + (32*cnt),SEEK_SET);
				write(fd,cstr,4);
			}
		}
		cnt++;
	}
}

int main(int argc, char **argv)
{
	int fd;
	long pos;
	
	if(argc != 3)
	{
		printf("Usage : exe target_text,changing_txt\n");
		exit(-1);
	}

	if( ( fd = open("reading2.txt",O_RDWR) ) < 0)
	{
		printf("There are no reading2.txt\n");
		exit(-1);
	}
	printf("fd = %d\n",fd);

	pos = replace_text(fd,argv[1],argv[2]);
	close(fd);

	return 0;	
}
