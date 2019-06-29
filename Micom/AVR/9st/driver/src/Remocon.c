#include "Atmega128.h"
#include <avr/interrupt.h>
#include "Remocon.h"
#include "Uart.h"

#define NEC_LEADING_CODE_LENGTH  0x103
#define NEC_LOGIC1_CODE_LENGTH   0x40
#define NEC_LOGIC0_CODE_LENGTH   0x20
#define NEC_REPEAT_CODE_LENGTH   0x144
#define NEC_CODE_LENGTH_VARIATION 4


#define NEC_LEADING_CODE 'L'
#define NEC_LOGIC1_CODE  '1'
#define NEC_LOGIC0_CODE  '0'
#define NEC_ERROR_CODE   'E'

typedef enum
{
	LEADING_WAIT,
	SINAL_GET
}REMOCON_Signal_State_t;

Remocon_Handle_t Remocon_Handle = NULL;

void Remocon_Init(void)
{
	/* 레지스터 초기화 */
	WGM33 = 0;      // 0000 : Normal Mode
	WGM32 = 0;
	WGM31 = 0;
	WGM30 = 0;

	ICNC3 = 0; // 0 : Noise Cancle Disable
	ICES3 = 0; // 0 : Falling Edge

	CS32  = 1; // 100 : clk/256
	CS31  = 0;
	CS30  = 0;

	TICIE3 = 1; // 인터럽트 활성화
}

void Remocon_Open(Remocon_Handle_t Handle)
{
	Remocon_Handle = Handle;
}

void Remocon_Close(void)
{
	Remocon_Handle = NULL;
}

ISR(TIMER3_CAPT_vect)
{
	uint16_t CurTime; 		  // 현재 시간
	static uint16_t PrevTime; // 이전 시간
	uint16_t Interval;        // 시간 간격
	uint8_t Code;
	volatile uint8_t cmd_bar;
	Remocon_Code_t Remocon_Code;
	static REMOCON_Signal_State_t Signal_State = LEADING_WAIT;
	static uint8_t Signal_Cnt = 0;
	static uint32_t CodeBits;

	/*  길이 계산 */
	CurTime = ICR3L + ((uint16_t)ICR3H << 8);
	Interval = CurTime - PrevTime;
	PrevTime = CurTime;

	/* 0/1/L 구별 */
	/* 코드 구별 ( 0, 1, Leading) */
 	if((Interval > (NEC_LEADING_CODE_LENGTH - NEC_CODE_LENGTH_VARIATION))
 	&& (Interval <= (NEC_LEADING_CODE_LENGTH + NEC_CODE_LENGTH_VARIATION)))
 	{
 		Code = NEC_LEADING_CODE;
 	}
 	else if((Interval > (NEC_LOGIC1_CODE_LENGTH - NEC_CODE_LENGTH_VARIATION))
 	&& (Interval <= (NEC_LOGIC1_CODE_LENGTH + NEC_CODE_LENGTH_VARIATION)))
 	{
 		Code = NEC_LOGIC1_CODE;
 	}
 	else if((Interval > (NEC_LOGIC0_CODE_LENGTH - NEC_CODE_LENGTH_VARIATION))
 	&& (Interval <= (NEC_LOGIC0_CODE_LENGTH + NEC_CODE_LENGTH_VARIATION)))
 	{
 		Code = NEC_LOGIC0_CODE;
 	}
 	else
 	{
 		Code = NEC_ERROR_CODE;
 	} 
	//UART_PutChar(Code);

	/* NEC 코드 구별 */
	switch(Signal_State)
	{
		case LEADING_WAIT:
			if(Code == NEC_LEADING_CODE)
			{
				Signal_Cnt = 0;
				Signal_State = SINAL_GET;
			}
			break;

		case SINAL_GET:
			if(Code == NEC_LOGIC1_CODE)
			{
				CodeBits >>= 1;
				CodeBits |= 0x80000000;
				Signal_Cnt++;
			}
			else if(Code == NEC_LOGIC0_CODE)
			{
				CodeBits >>= 1;
				Signal_Cnt++;
			}
			else
			{			
				Signal_State = LEADING_WAIT;
			}

			if(Signal_Cnt >= 32)
			{
				cmd_bar = ~((CodeBits>>24) & 0xFF);			
				if(((CodeBits & 0xFF) == ((CodeBits>>8) & 0xFF))
				&& (((CodeBits>>16) & 0xFF) == cmd_bar))
				{
					Remocon_Code = ((CodeBits>>16) & 0xFF);
					if(Remocon_Handle)
					{
						Remocon_Handle(Remocon_Code);
					}
				}
				Signal_State = LEADING_WAIT;
			}
			break;

		default:
			Signal_State = LEADING_WAIT;
			break;
	}
	
}
