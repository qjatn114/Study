#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 쓰레드 함수
void *t_function(void *data)
{
	char a[10000];	
	int num = *((int *)data);
	printf("THread Start\n");
	sleep(5);
	printf("Thread End\n");
}

int main()
{
    pthread_t p_thread;
    int thr_id;
    int status;
    int a = 100;

	printf("Before Thread\n");
	

    // 쓰레드 생성 아규먼트로 1 을 넘긴다.  
    thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
	pthread_detach(p_thread);
	pause();
    return 0;
}
