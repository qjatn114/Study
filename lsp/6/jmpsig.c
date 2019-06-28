#include <stdio.h>

#include <stdlib.h>

#include <signal.h>//시그널을 사용하기 위한 헤더

#include <setjmp.h>//setjmp를 사용하기 위한 헤더

jmp_buf mark_pos;//현재 스택을 저장하기 위한 변수

 

//시그널 핸들러는 선언

void sig_jmp(void)

{          

             printf("\nfunction scanf() time exit\n");

             longjmp(mark_pos,1);//레드헷 계열의 리눅스에서 SIG_DEF로 보내는것을 차단하기 위해 한번더

             //시그널 포획을 설정해준다(책의 내용을 참고함)

             if(signal(SIGALRM,(void*)sig_jmp)==SIG_ERR)

  {

                       perror("signal");

                       exit(1);

             }

}

            

main(int argc,char *argv[]) //아큐먼트를 timeout시간을 설정 받는다

{           unsigned int Time; //시간 저장

             int key;

             int i=0; //longjmp가 리턴하는 값을 저장함

             //값을 저장 안할경우 루프에 빠질수 있다

            

             if(atoi(argv[1])<0)

   {

                       exit(1);

             }

             Time=atoi(argv[1]);

             if(signal(SIGALRM,(void*)sig_jmp)==SIG_ERR)

   {

                       perror("signal");

                       exit(1);

             }

             alarm(Time);//알람 시그널을 보내기위한 알람 설정

             printf("wait input key timeout setting( %02dsecond)====>",Time);

             i=setjmp(mark_pos);//복귀 포인트 설정

             if(i==0)

   {          //시그널 포획함수에서 리턴되는 값을 처리한다. Setjmp는 처음에는 0을 설정한다..

                         //기본적으로 한번은 들어 가야 함으로 0을 설정

                        scanf("%d",&key);

             }

             else

   {

                        //시그널 포착====타임아웃  longjmp의 리턴값은 1이다...프로그램을 종료한다...

                        printf("\nalram program exit now good bye!\n");

             }

             exit(0);

}

