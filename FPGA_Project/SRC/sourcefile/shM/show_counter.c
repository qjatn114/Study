/* counter.c가 공유 메모리에 넣은 카운터 문자열을 화면에 계속 출력한다
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY_NUM		9527
#define MEM_SIZE	1024

int main(void)
{
	int shm_id;
	void *shm_addr;
	
	if( -1 == (shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT | 0666)))
	{
		printf("shm generation failed\n");
		return -1;
	}
	if( (void *)-1 == (shm_addr = shmat(shm_id, (void *)0 , 0)))
	{
		printf("shm reference failed\n");
		return -1;
	}

	while(1)
	{
		printf("%d\n",(*(int *)shm_addr)++);	//공유메모리 화면에 출력
		sleep(1);
	}

	return 0;
}
