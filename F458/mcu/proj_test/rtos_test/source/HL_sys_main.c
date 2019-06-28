/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "HL_system.h"
#include "HL_etpwm.h"
#include "HL_sci.h"
#include "HL_het.h"
#include "HL_ecap.h"
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "os_queue.h"

#include <stdio.h>
#include <string.h>
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void init_all(void);
void sci_display(char* buf, int len);
void motor_bldc(void* pbParameters);
void wait_ms(int num, int delay);
void motor_servo(void* pbParameters);
void hetRamInit(void);

int throttle;
int rudder;
int init_back_flag=1;


TaskHandle_t bldc_Handle;
TaskHandle_t servo_Handle;
SemaphoreHandle_t bldc_sem;
SemaphoreHandle_t servo_sem;
BaseType_t cap_Give;

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    char buf[128];
    int buf_len;

    init_all();
/*
    sprintf(buf,"init Complete:\n\r\0");
    buf_len=strlen(buf);
    sci_display(buf,buf_len);
*/
    bldc_sem=xSemaphoreCreateBinary();//이진세마포어 2개 생성
    servo_sem=xSemaphoreCreateBinary();

    if(xTaskCreate(motor_bldc,"bldc",configMINIMAL_STACK_SIZE*2,NULL,1,bldc_Handle)!=pdPASS){//bldc 태스크 생성부분
        for(;;)
            ;
    }

    if(xTaskCreate(motor_servo,"servo",configMINIMAL_STACK_SIZE*2,NULL,1,servo_Handle)!=pdPASS){//servo 태스크 생성부분
        for(;;)
            ;
    }

    vTaskStartScheduler();//스케줄링을 시작 (태스크 제어 시작.)

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void wait_ms(int num, int delay){//Het을 이용해 ms단위로 딜레이를 주기 위해 사용한 함수
    delay*=5000;//기본이 200ns 이므로 5000을 곱해서 1ms로 맞추어줌
    hetRAM1->Instruction[num].Data=0;//0~delay까지 대기
    while(((hetRAM1->Instruction[num].Data)>>7)<delay)//cnt의 data의 하위 7bit는 쓰지 않는 부분으로 상위 25bit로부터 값을 얻어옴
        ;
}

void motor_servo(void* pbParameters)
{
    char buf[64];
    int buf_len;

    for(;;){
        if(xSemaphoreTake(servo_sem,(TickType_t )0x01)==pdTRUE){
            sprintf(buf,"********servo_Start**********\n\r\0");
            buf_len=strlen(buf);
            sci_display(buf,buf_len);

            rudder=(int)(((float)rudder)*0.9);
            rudder=2700-rudder;//조종기의 좌우와 차량의 좌우가 불일치 하므로 방향에 맞게끔 처리
            if(rudder>=1250&&rudder<1450){//중립 범위 조정(조종 편의성을 위함)
                rudder=1250;
            }
            if(rudder>=900&&rudder<=1800)
                etpwmREG1->CMPB=rudder;// 900 1250 1800(서보의 범위 우측 최대, 중립, 좌측 최대 )
            wait_ms(1,100);

            sprintf(buf,"**********servo_End rudder:%d*********\n\r\0",rudder);
            buf_len=strlen(buf);
            sci_display(buf,buf_len);

            ecapEnableInterrupt(ecapREG2,ecapInt_CEVT3);
        }else{
            sprintf(buf,"servo Blocked\n\r\0");
            buf_len=strlen(buf);
            sci_display(buf,buf_len);
        }
    }
}

void motor_bldc(void* pbParameters)
{
    char buf[64];
    int buf_len;

    for(;;){
        if(xSemaphoreTake(bldc_sem,(TickType_t)0x01)==pdTRUE){
           // ecapDisableInterrupt(ecapREG1,ecapInt_CEVT3);//중간에 capInterrupt Disable

            sprintf(buf,"bldc Start\n\r\0");
            buf_len=strlen(buf);
            sci_display(buf,buf_len);

            if(throttle>=950&&throttle<1450){//모터 구동부
                if(init_back_flag){//최초 후진시 필요
                    etpwmREG1->CMPA=1500;
                    wait_ms(0,100);
                    etpwmREG1->CMPA=1000;
                    wait_ms(0,100);
                    etpwmREG1->CMPA=1500;
                    wait_ms(0,100);
                    init_back_flag=0;
                    sprintf(buf,"---------init back-----------\n\r\0");
                    buf_len=strlen(buf);
                    sci_display(buf,buf_len);
                }
            }else if(throttle>=1550&&throttle<=2000){
                init_back_flag=1;
            }else{
                throttle=1500;
            }
            etpwmREG1->CMPA=throttle;//모터 pwm주기
            wait_ms(0,100);

            sprintf(buf,"bldc_task_end CMPA:%d\n\r\0",throttle);
            buf_len=strlen(buf);
            sci_display(buf,buf_len);

            ecapEnableInterrupt(ecapREG1,ecapInt_CEVT3);//인터럽트 다시 활성화

        }else{
            sprintf(buf,"-------------bldc_task_blocked--------------\n\r\0");
            buf_len=strlen(buf);
            sci_display(buf,buf_len);
        }
    }

}

void sci_display(char* buf, int len){
    for(;len>0;len--){
        sciSendByte(sciREG1,*buf++);
    }
}

void init_all(void){//초기화 부분을 모아둔 함수
    etpwmInit();
    ecapInit();
    hetInit();
    hetRamInit();
    sciInit();
    _enable_interrupt_();
    etpwmStartTBCLK();
    ecapStartCounter(ecapREG1);
    ecapStartCounter(ecapREG2);
    ecapEnableCapture(ecapREG1);
    ecapEnableCapture(ecapREG2);
    init_back_flag=1;
}


void ecapNotification(ecapBASE_t *ecap, uint16 flag)
{
    int cap[2];
    char buf[128];
    int buf_len;

    cap[0]=ecap->CAP1;
    cap[1]=ecap->CAP2;


    if(ecap==ecapREG1){
        ecapDisableInterrupt(ecapREG1,ecapInt_CEVT3);//모터 구동 태스크와 번갈아 가며 실행되기 위해 인터럽트를 꺼둠, 수정수정수정수정

        sprintf(buf,"cap1 Start\n\r\0");
        buf_len=strlen(buf);
        sci_display(buf,buf_len);

        throttle=(cap[1]-cap[0])/VCLK3_FREQ;


        if(throttle<950){//수신기가 꺼져있을때 처리.
            throttle=1500;
        }

        throttle=(throttle-1000)*0.4+1300;//throttle범위 조정

        if(throttle>1450&&throttle<1550){//중립 보정
            throttle=1500;
        }

        sprintf(buf,"cap output throttle:%d\n\r\0",throttle);
        buf_len=strlen(buf);
        sci_display(buf,buf_len);

        xSemaphoreGiveFromISR(bldc_sem,&cap_Give);//binary semaphore를 사용가능하게끔 Give 실행
    }else{
        ecapDisableInterrupt(ecapREG2,ecapInt_CEVT3);//서보모터와 번갈아가며 실행되기 위함.

        sprintf(buf,"cap2 Start\n\r\0");
        buf_len=strlen(buf);
        sci_display(buf,buf_len);

        rudder=(cap[1]-cap[0])/VCLK3_FREQ;
        if(rudder<950){//신호 끊겼을 때 중립처리
            rudder=1500;
        }

        sprintf(buf,"cap2 output rudder:%d\n\r\0",rudder);
        buf_len=strlen(buf);
        sci_display(buf,buf_len);
        xSemaphoreGiveFromISR(servo_sem,&cap_Give);//서보모터용 세마포어를 Give
    }
    portYIELD_FROM_ISR(cap_Give);//인터럽트 서비스 루틴에서 세마포어 사용시 이걸 써주어야 한다고 예제 코드에 있길래 추가.
}

void hetRamInit(void)//hetRAM 초기화
{
    hetREG1->GCR=(hetREG1->GCR)&0xFFFFFFFE;//우선 HET 끄기
    hetRAM1->Instruction[0].Program=0x00002C80U;//HETRAM 첫번째에 cnt 명령어 할당
    hetRAM1->Instruction[0].Control=0x01FFFFFFU;
    hetRAM1->Instruction[0].Data=0xFFFFFF80U;

    hetRAM1->Instruction[1].Program=0x00000C80U;//hetRAM 두번째에도 cnt 명령어 할당
    hetRAM1->Instruction[1].Control=0x01FFFFFFU;
    hetRAM1->Instruction[1].Data=0xFFFFFF80U;
    hetREG1->GCR=(hetREG1->GCR)|0x00000001;//HET 동작 시작
}
/* USER CODE END */
