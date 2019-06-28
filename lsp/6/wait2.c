#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>


/* 정상종료 했는지 비정상 종료 했는지 확인  */
void term_status(int status)
{
	if(WIFEXITED(status))
		printf("(exit)status : 0x%x\n",WEXITSTATUS(status));
	else if(WTERMSIG(status))
		printf("(signal)status : 0x%x\n",status & 0x7f);
}

/* SIGCHLD가 발생하면 my_sig 동작  */
void my_sig(int signo)
{
	int status;
	wait(&status);
	printf("status = %d\n",status);
	printf("signo = %d\n",signo);

	term_status(status);
}



int main(void)
{
	int i;
	pid_t pid;

	signal(SIGCHLD, my_sig);
	
	if( (pid = fork() ) > 0)
	{
		for(i=0 ; i<10000;i++)
		{
			usleep(50000);
			printf("%d\n", i +1);
		}
	}
	else if(!pid)
	{
		sleep(5);
	}
	else
	{
		perror("fork()");
		exit(-1);
	}

	return 0;
}

