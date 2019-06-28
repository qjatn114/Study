#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
	int status;
	int pid;
	
	char *argv[] = {"./ls_l","1_ls_l.c",0};
	char *envp[] = {0};
	if( (pid = fork() ) > 0 )
	{
		wait(&status);
		printf("Child was finished\n");
	}
	else if(!pid)
	{
		execve("./ls_l",argv,envp);
	}
	
	return 0;
}
