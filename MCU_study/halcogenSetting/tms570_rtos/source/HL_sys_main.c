#include "HL_sys_common.h"


#include <math.h>

#include "HL_sys_core.h"
#include "HL_system.h"
#include "HL_sci.h"
#include "HL_can.h"
#include "HL_gio.h"
#include "HL_etpwm.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#include "os_queue.h"
#include "os_semphr.h"
#include "os_task.h"

xTaskHandle task0;
xTaskHandle task1;

QueueHandle_t mutex = NULL;

uint8_t rx_data[8];

int accel;
int steering;

int collision;

void sci_display(sciBASE_t *, uint8_t *, uint32_t);
void task0_func(void *);
void task1_func(void *);
void wait(uint32_t);


int main(void)
{

    sciInit();
    gioInit();
    canInit();
    etpwmInit();
    etpwmStartTBCLK();

    etpwmREG1->CMPA = 1000;
    wait(3333333);
    etpwmREG1->CMPA = 2000;
    wait(3333333);
    etpwmREG1->CMPA = 1500;
    wait(3333333);

    canEnableErrorNotification(canREG1);

    if(xTaskCreate(task0_func, "decision", configMINIMAL_STACK_SIZE, NULL, 5, &task0)!= pdTRUE )
        for(;;)
            ;

    if(xTaskCreate(task1_func, "collision decision", configMINIMAL_STACK_SIZE, NULL, 1, &task0) != pdTRUE)
        for(;;)
            ;

    vTaskStartScheduler();  // 경쟁시키겠다. 멀티태스킹을 시작하겠다.


    return 0;
}

void task0_func(void *pbParameters)
{
    int i, cnt = 3;

    for(;;)
    {
        if(xSemaphoreTake(mutex, (TickType_t)0x01) == pdTRUE)
        {
            if(rx_data[0])
                sci_display(sciREG1, rx_data, 8);

            switch(rx_data[0])
            {
            case 1:
                gioToggleBit(gioPORTA, 4);
                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;
            case 6:
                collision = true;
                break;
            case 12:
                for(i=1; i<5; i++)
                    accel += rx_data[i]  * pow(10, cnt--);

                etpwmREG1->CMPA = accel;

                cnt = 3;
                accel = 0;

                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;
            case 13:
                for(i=1; i<5; i++)
                    steering += rx_data[i] * pow(10, cnt--);

                etpwmREG2->CMPA = steering;

                cnt = 3;
                steering = 0;

                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;
            default:
                xSemaphoreGive(mutex);
                vTaskDelay(10);
                break;
            }
        }
    }
}

void task1_func(void *pbParameters)
{
    for(;;)
    {
        if(collision)
        {
            if(xSemaphoreTake(mutex, (TickType_t)portMAX_DELAY) == pdTRUE)
            {
                //gioSetBit(gioPORTB, 2, 1);
                etpwmREG3->CMPA = 2300;
                vTaskDelay(10);
            }
            else
            {
                xSemaphoreGive(mutex);
                vTaskDelay(10);
            }
        }
        else
        {
            etpwmREG3->CMPA = 0;
            //gioSetBit(gioPORTB, 2, 0);
            xSemaphoreGive(mutex);
            vTaskDelay(10);
        }
    }
}

void wait(uint32_t delay)
{
    for(; delay>0; delay--)
        ;
}

void sci_display(sciBASE_t *sci, uint8_t *text, uint32_t len)
{
    while(len--)
    {
#if 0
        while((UART->FLR & 0x4) == 4)
            ;
#endif
        sciSendByte(sciREG1, *text++);
    }
    sciSendByte(sciREG1, '\r');
    sciSendByte(sciREG1, '\n');
}

void canMessageNotification(canBASE_t *node, uint32_t messageBox)
{
    while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2))
        ;
    canGetData(canREG1, canMESSAGE_BOX2, (uint8_t *)&rx_data[0]);
}