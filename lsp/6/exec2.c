#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
	int status;
	pid_t pid;

	if( (pid= vfork()) > 0)
	{
		waitpid(-1,&status,WNOHANG);
		printf("ls -al tset Success\n");
	}
	else if(!pid)
	{
		execlp("ls","ls","-a","-l",0);
	}

	return 0;
}
