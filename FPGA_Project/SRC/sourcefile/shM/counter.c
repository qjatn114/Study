/* 공유메모리에 1초마다 0부터 계속 증가하는 카운터 문자열을 공유메모리에 넣으면 
show_counter.c에서 공유메모리를 화면에 출력한다.

counter.c에서는 공유메모리를 생성하고 공유메모리에 카운터 문자열을 계속 갱신하여 넣는다
*/


#include <stdio.h>
#include <unistd.h>	//sleep()
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY_NUM	9527
#define MEM_SIZE	1024



int main(void)
{
	int shm_id;
	void *shm_addr;
	int *count;

	if( -1 == (shm_id = shmget( (key_t)KEY_NUM, MEM_SIZE, IPC_CREAT | 0666)))
	{
		printf("shm generation failed\n");
		return -1;
	}

	if( (void *)-1 == (shm_addr = shmat(shm_id, (void *)0, 0)))
	{
		printf("shm reference failed\n");
		return -1;
	}
	
	count = (int *)shm_addr;
	*count = 10;
	while(1)
	{
		printf("Count PROCESS %d\n",*count);	//공유메모리에 카운터 출력
		sleep(1);
	}

	return 0;
}
