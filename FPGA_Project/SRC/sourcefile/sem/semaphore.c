#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


/*   
	상황
하나의 파일에 2개의 프로세스가 동시에 접근하고자 하는데에서 발생한다. 파일에는 count 숫자가 들어있으며 프로세스는 파일을 열어서 count 숫자를 읽어들이고 여기에 1을 더해서 다시 저장하는 작업을 한다. 
*/

#define SEMKEY		2345

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *arr;	
};

static int semid;

int main(int argc, char **argv)
{
	FILE *fp;
	char buf[11];
	char count[11];

	union semun sem_union;

	//open과 close를 위한 sembuf 구조체를 정의한다.
	struct sembuf mysem_open = {0, -1, SEM_UNDO};	//semaphore 얻기
	struct sembuf mysem_close = {0, 1, SEM_UNDO};	//semaphore 돌려주기
	int sem_num;

	memset(buf,0x00,11);
	memset(count,0x00,11);

	//argument가 있으면 생성자. 그렇지 않으면 소비자이다.
	if(argc > 1)
		sem_num = 1;
	else
		sem_num = 0;

	//semaphore 설정
	semid = semget((key_t)234, sem_num, 0660|IPC_CREAT);
	if(semid == -1)
	{
		perror("semget error");
		exit(0);
	}

	//semaphore 초기화
	sem_union.val = 1;
	if( -1 == semctl(semid, 0 , SETVAL, sem_union))
	{
		printf("semctl() -SETVAL 실행오류\n");
		exit(0);
	}
	//파일의 내용을 읽은 후 파일을 처음으로 되돌린다.
	fgets(buf,11,fp);
	rewind(fp);

	//개행문자를 제거
	buf[strlen(buf) -1] = 0x00;
	
	sprintf(count, "%d\n",atoi(buf) +1);
	printf("%s",count);
	
	//10초를 잠들고 count를 파일에 쓴다.
	sleep(10);
	fputs(count,fp);

	fclose(fp);

	//모든 작업이 완료되면 semaphore 자원을 되돌려준다.
	semop(semid, &mysem_close,1);

	return 0;
}
