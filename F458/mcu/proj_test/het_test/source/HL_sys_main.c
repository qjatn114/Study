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
#include "HL_gio.h"
#include "HL_het.h"
#include "HL_sci.h"
#include <string.h>
#include <stdio.h>
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void sci_display(sciBASE_t *sci, char*buf,int buf_len);
void waitmsbyhet(int num, int delay);
void hetRamInit(void);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    char buf[128];
    int buf_len;

    gioInit();
    hetInit();
    hetRamInit();
    sciInit();

    sprintf(buf,"Init Success!!\n\r\0");
    buf_len=strlen(buf);
    sci_display(sciREG1,buf,buf_len);

   // gioSetBit(gioPORTA,0,1);

    for(;;){
        sprintf(buf,"wait start\n\r\0");
        buf_len=strlen(buf);
        sci_display(sciREG1,buf,buf_len);

        waitmsbyhet(0,1000);

        sprintf(buf,"wait END\n\r\0");
        buf_len=strlen(buf);
        sci_display(sciREG1,buf,buf_len);

        waitmsbyhet(1,1000);
        //gioToggleBit(gioPORTA,0);
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void sci_display(sciBASE_t *sci, char*buf,int buf_len){
    int i;
    for(i=0;i<buf_len;i++){
        sciSendByte(sci,buf[i]);
    }
}

/*
void set_HetTimer(hetRAMBASE_t* hetRAM, int delay){
    hetRAM->Instruction[0]->Control=delay;
}*/
void waitmsbyhet(int num, int delay){
    delay*=5000;
    hetRAM1->Instruction[num].Data=0;
    while(((hetRAM1->Instruction[num].Data)>>7)<delay)
        ;
}

void hetRamInit(void)
{
    //hetINSTRUCTION_t instructions[]
    hetREG1->GCR=(hetREG1->GCR)&0xFFFFFFFE;
    //memset(hetRAM->Instruction[0x0])
    hetRAM1->Instruction[0].Program=0x00002C80U;
    hetRAM1->Instruction[0].Control=0x01FFFFFFU;
    hetRAM1->Instruction[0].Data=0xFFFFFF80U;

    hetRAM1->Instruction[1].Program=0x00000C80U;
    hetRAM1->Instruction[1].Control=0x01FFFFFFU;
    hetRAM1->Instruction[1].Data=0xFFFFFF80U;
    hetREG1->GCR=(hetREG1->GCR)|0x00000001;
}

/* USER CODE END */
