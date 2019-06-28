#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>


int main(void)
{
	DIR *dp;
	int i = 0;
	struct dirent *p;

	dp = opendir(".");

/*계속 readdir(dp)를한다 현재 위에 있는 모든 파일에 대한 디렉토리 엔트리를 
다 읽을 때 까지 계속 루프를 돌면서 이 안에 무엇이 있는지 뿌리곘다.*/
	while( p = readdir(dp))
	{
		if( p->d_name[0] == '.')		//숨긴파일
			continue;

		printf("%-12s ", p->d_name);

		//if( (i+1) % 5 ==0 )
		if( !((i+1) % 5))
			printf("\n");

		i++;
	}
	
	printf("\n");
	
	closedir(dp);

	return 0;
}
