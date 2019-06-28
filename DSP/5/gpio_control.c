#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <setjmp.h>



#define BUF_SIZE        1024

jmp_buf env;
extern char *dev0;
int fd_on;
int fd_off;




typedef struct sockaddr_in      si;
typedef struct sockaddr *       sap;




void err_handler(char *msg)
{
    fputs(msg,stderr);
    fputs('\n',stderr);
    exit(1);
}

int main(int argc,char **argv)
{
	int ret;
	char *buf[2] = {"on","off"};
	fd_on = serial_config(dev0);
	fd_off = serial_config(dev0);
	int fd_len = strlen(buf[0]);

    int serv_sock,clnt_sock;
    int i,str_len;
    char msg[BUF_SIZE];
    char *gpio[] = {"gpio=0","gpio=1"};
    int len = strlen(gpio[0]);
    
    si serv_addr;
    si clnt_addr;
    socklen_t clnt_addr_size;



    if(argc != 2)
    {
        printf("Usage : %s <port> \n",argv[0]);
        exit(-1);
    }

    serv_sock = socket(PF_INET,SOCK_STREAM,0);

    if(serv_sock == 1)
    {
        err_handler("socket() error");
    }

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));      //port번호 생성

    if(bind(serv_sock,(sap)&serv_addr,sizeof(serv_addr)) == -1)
        err_handler("bind() error");

    if(listen(serv_sock,10) == -1)
        err_handler("listen() error");

    clnt_addr_size = sizeof(clnt_addr);

    for(i=0;i<5;i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

        if(clnt_sock == 1)
            err_handler("accept() error");
        while( (str_len = read(clnt_sock,msg,BUF_SIZE)) != 0)
        {
            if( !strncmp(msg,gpio[0],len) )
            {
                send_data(fd_on,buf[0],fd_len,50);
		printf("led_on\n");
            }
            else if( !strncmp(msg,gpio[1],len))
            {
		send_data(fd_off,buf[1],fd_len,50);
                printf("lef_off\n");
            }
            else
        }
        close(clnt_sock);
    }

    close(serv_sock);
	close_dev(fd_on);
	close_dev(fd_off);
    return 0;
}

