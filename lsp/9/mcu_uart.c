#include "HL_sys_common.h"
#include "HL_system.h"
#include "HL_sci.h"

#define TSIZE       7
#define UART    sciREG1


uint8 TEXT[TSIZE] = {'K','\n','\r'};
char txt_buf[32];
char tb_len;


void sciSendText(sciBASE_t *sci, uint8 *text, uint32 len);
void delay(uint32 time);


int main(void)
{
    sciInit();

    for(;;)
    {
        txt_buf[tb_len++] = sciReceiveByte(UART);

        if(txt_buf[tb_len - 1] == '\n')
        {
            sciSendText(UART,&TEXT[0],TSIZE);
            tb_len = 0;
        }
        delay(3333);
    }

    return 0;
}

void sciSendText(sciBASE_t *sci, uint8 *text, uint32 len)
{
    while(len--)
    {
        while( (UART->FLR & 0x4) == 4)
        {
            ;
        }
        sciSendByte(UART,*text++);
    }
}

void delay(uint32 time)
{
    int i;

    for(i=0;i<time;i++)
        ;
}
