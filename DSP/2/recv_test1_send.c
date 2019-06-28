#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;
extern char *dev0;
int fd;

void call_exit(int signo)
{
    close_dev(fd);
    longjmp(env,1);
}
#if 0
void set_label(void)
{
    for(;;)
        recv_data(fd);
}
#endif

int main(void)
{
    int ret;
    char buf[32] = "message\r\n";
    int len = strlen(buf);

    fd = serial_config(dev0);
    signal(SIGINT,call_exit);

    if( !(ret = setjmp(env)) )
    {
        for(;;)
        {
            send_data(fd,buf,len,50);   //50 = delay time  MCU로 보냄
            recv_data(fd);          //받는거
        }
    }
    return 0;
}

