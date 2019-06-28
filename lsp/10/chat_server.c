#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_CLNT 256
#define BUF_SIZE 1024

int clnt_cnt =0;
int clnt_socks[MAX_CLNT];

pthread_mutex_t mtx;

typedef struct sockaddr_in si;
typedef struct sockaddr * sap;

void err_handler(char *msg)
{
	fputs(msg, stderr);
	fputc('\n',stderr);
	exit(1);
}

void send_msg(char *msg, int len)
{
	int i;
	pthread_mutex_lock(&mtx);
	for(i = 0; i < clnt_cnt; i++)
		write(clnt_socks[i],msg,len);

	pthread_mutex_unlock(&mtx);
}

void *clnt_handler(void *arg)//thread
{
	int i =0;
	int clnt_sock = *((int *)arg);
	int str_len = 0;
	char msg[BUF_SIZE];

	while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0)
		send_msg(msg, str_len);

	//다른 쓰레드에서 socket을 지울시 꼬이면 안되니까 뮤텍스를 걸어준다.(동작 보장)
	pthread_mutex_lock(&mtx);

	//client 관리(클라이언트가 종료되면 클라이언트 socket에서 제거)
	for(i =0; i < clnt_cnt; i++)
	{
		if(clnt_sock == clnt_cnt -1)
		{
			while(i++ <clnt_cnt -1)
				clnt_socks[i] = clnt_socks[i+1];
			break;
		}
	}

	clnt_cnt--;
	pthread_mutex_unlock(&mtx);

	close(clnt_sock);

	return NULL;
}

int main(int argc, char **argv)
{
	int serv_sock, clnt_sock;
	si serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	pthread_t t_id;

	char msg[BUF_SIZE] ={0,};

	if(argc != 2)
	{
		printf("Usage: %s <port>\n",argv[0]);// PORT는 65535개 특수 사용 포트 불가능(ex 80번 포트)
		exit(-1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM,0); //소켓 생성

	if(serv_sock == -1)
		err_handler("socket() error");
	memset(&serv_addr, 0, sizeof(serv_addr)); //serv_addr 구조체 변수 공간 초기화
	serv_addr.sin_family = AF_INET; //TCP 사용
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//ip
	serv_addr.sin_port = htons(atoi(argv[1]));//setting port

	if(bind(serv_sock, (sap) & serv_addr, sizeof(serv_addr)) == -1)// socket에 ip주소와  포트 번호 연결(커널에서 알아서)
		err_handler("bind() error");
	if(listen(serv_sock,10) == -1) //client 받을 수 있도록 설정
		err_handler("listen() error");

	for(;;)
	{
		clnt_addr_size = sizeof(clnt_addr);
		clnt_sock =  accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size); //client 연결 대기

		pthread_mutex_lock(&mtx);
		clnt_socks[clnt_cnt++] = clnt_sock;
		pthread_mutex_unlock(&mtx);


		pthread_create(&t_id, NULL, clnt_handler, (void *)&clnt_sock);//clnt 접속한 만큼 thread 만들어짐
		pthread_detach(t_id);// thread 알아서 동작
		printf("Connection Client IP : %s\n", inet_ntoa(clnt_addr.sin_addr));
	}
	close(serv_sock);

	return 0;
}

