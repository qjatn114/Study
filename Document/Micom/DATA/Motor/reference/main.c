/**
* @file			main.c
* @brief		���� �Լ� 
* @author		���̼�	
* @remarks
* @par �����̷� 
*	@li	2011.09.07 : �ʱ�  �Լ� �ۼ�  
*/


/**
* @mainpage		DC ���� ���� ���α׷� ���� �ڵ� (AT90CAN128)
* @section intro	�Ұ�
*	@li	�Ұ� :  DC ���� ���� ���α׷� ���� �ڵ�   
* @section CREATEINFO �ۼ����� 	
*	@li	�����ڸ� : ���̼� 
* 	@li	���� ����: Solutionbank Motor Contro BD V1.2  
*/


#include "at90can128.h"
#include <avr/interrupt.h>

#include "led.h"
#include "fnd.h"
#include "uart.h"
#include "adc.h"
#include "key.h"
#include "pwm.h"
#include "capture.h"
#include "volume.h"
#include "dcmotor.h"





/***** DC ���Ϳ�  *****/
#define DCMOTOR_MAX_RPM	10000

typedef struct{
	unsigned short DesiredSpeed;		// ���� ������ ADC �� 
	unsigned short MeasuredSpeed;		// ������ �ӵ�(RPM)
	unsigned char MeasuredFlag;
}ST_DCMOTOR;



void Key_Control(void);
void Volume_Control(void);
void UART_Control(void);
void Speed_Calculation(void);
void DCMotor_Test(void);

void Delay(unsigned long Delay);

void OpenLoop_Control(void);
void CloseLoop_Control(void);


ST_DCMOTOR DCMotor;


void Init(void);


/**
* @fn		int main(void)
* @brief
*	- ���� �Լ� 
* @remarks
* @param	void
* @return	int			
*/
int main(void)
{

	Init();

	LED0_On(0);
	LED1_On(1);
	LED2_On(0);
	LED3_On(1);
	
	
	FND_Write( 0, 0, 0);
	FND_Write( 1, 1, 0);
	FND_Write( 2, 2, 0);
	FND_Write( 3, 3, 0);

	UART_WriteString("\r\n===============================");
	UART_WriteString("\r\n= DC Motor ���� ���α׷� V1.0 =");
	UART_WriteString("\r\n===============================");	

	/* DC Motor �׽�Ʈ�� ��Ʈ �ʱ�ȭ */
//	PORTB2 = 0;
//	PORTB5 = 0;
//	DDB2 = 1;
//	DDB5 = 1;

	sei();
	
	while(1)
	{
		//DCMotor_Test();
		Key_Control();
		Speed_Calculation();	
		Volume_Control();
		UART_Control();
		//OpenLoop_Control();	
		CloseLoop_Control();
	}

	return 0;
}




/**
* @fn		void Init(void)
* @brief
*	@li		�ý��� �ʱ�ȭ �Լ� 
* @remarks
* @param	void
* @return	void			
*/
void Init(void)
{
	/* ����̹� �ʱ�ȭ */
	LED_Init();
	FND_Init();
	UART_Init();
	ADC_Init();
	Key_Init();
	DCMotor_Init();	
	Capture_Init();
	Volume_Init();


	DCMotor.DesiredSpeed = 0;
	DCMotor.DesiredSpeed = 0;
	DCMotor.MeasuredFlag = 0;
	

}


void Key_Control(void)
{
	KEY_CODE Key;
	
	Key = Key_GetKey();

	if(Key == KEY_NOTHING)
	{
		return;
	}

	switch(Key)
	{
		case KEY_UP :
			DCMotor_Start();
			UART_WriteString("\r\nKey-Up");
			break;
		case KEY_DOWN :
			DCMotor_Stop();
			UART_WriteString("\r\nKey-Down");
			break;			
		case KEY_LEFT :
			DCMotor_SetDirection(0);
			UART_WriteString("\r\nKey-Left");
			break;
		case KEY_RIGHT :
			DCMotor_SetDirection(1);
			UART_WriteString("\r\nKey-Right");
			break;
		case KEY_CENTER :
			UART_WriteString("\r\nKey-Center");
			break;
		default :
			break;

	}
}

void Volume_Control(void)
{
	unsigned short Volume;
//	static unsigned char Temp = 0;
	
	if(Volume_GetData(&Volume) == 0)
	{
		return;
	}

	DCMotor.DesiredSpeed = (unsigned long) Volume * DCMOTOR_MAX_RPM / 1023;
	//DCMotor_SetDuty(Volume);

//	if((Temp % 4) == 0)
//	{	
	cli();			// ���ͷ�Ʈ�� ���� �����Ǵ� ���� ���� : �������� ������ �ٲ���� ���� 
	UART_WriteString("<D>");
	UART_WriteDecimal(DCMotor.DesiredSpeed);
	sei();
//	}

}

void UART_Control(void)
{
	unsigned char Data;
	
	if(UART_GetData(&Data) == 0)
	{
		return;
	}

	switch(Data)
	{
		case 'S' :			// ���� ���� 
			DCMotor_Start();
			break;
		case 'T' :			// ���� ����  
			DCMotor_Stop();
			break;			
		case 'F' :			// ���� ���� : ������ 
			DCMotor_SetDirection(0);
			break;
		case 'B' :			// ���� ���� : �ι��� 
			DCMotor_SetDirection(1);
			break;
		default :
			break;
	}	

}





void DCMotor_Test(void)
{
	PORTB5 = 1;
	Delay(100);
//	PORTB5 = 0;
//	Delay(1);
}

void Delay(unsigned long Delay)
{
	volatile unsigned long i;

	for(i = 0; i < Delay; i++)
	{
		i = i;
	}
}

void Speed_Calculation(void)
{
	unsigned long Time;

	static unsigned char Temp = 0;

	if(Capture_GetTime(&Time) == 0)
	{
		return;
	}

	Time = Time * 600 / 14;

	DCMotor.MeasuredSpeed = Time;
	DCMotor.MeasuredFlag = 1;

//	if((Temp % 4) == 0)
//	{
	UART_WriteString("<S>");
	UART_WriteDecimal(Time);
	FND_Write(Time  % 10, 0, 0);
	FND_Write(Time / 10 % 10, 1, 0);
	FND_Write(Time / 100 % 10, 2, 0);
	FND_Write(Time / 1000 % 10, 3, 0);		
//	}
	Temp++;
}


void OpenLoop_Control(void)
{
	unsigned short Duty;
	
	Duty = (unsigned long)DCMotor.DesiredSpeed * 1023 /DCMOTOR_MAX_RPM ;
	DCMotor_SetDuty(Duty);
}




double Kp = 0.01;
double Ki = 0.001;
double Kd = 0;

void CloseLoop_Control(void)
{
	
	short CurError;
	static short PrevError = 0;
	static long ErrorSum = 0;

	short PWM_Duty;
	
	if(DCMotor.MeasuredFlag == 0)
	{
		return;
	}
	DCMotor.MeasuredFlag = 0;
	
	// calculate the motor signal according the PID equation.
	// the derivative and the integral are approximated using simple linear approximations.
	CurError = DCMotor.DesiredSpeed - DCMotor.MeasuredSpeed;
	ErrorSum += CurError;
	PWM_Duty = DCMotor_GetDuty();
	PWM_Duty = PWM_Duty + Kp * CurError + Ki*ErrorSum + Kd*(CurError - PrevError);

	/* PWM Duty�� �����Ѽ��� �����Ѵ�. */
	if(PWM_Duty < 0)
	{
		PWM_Duty = 0;
	}
	else if(PWM_Duty > 1023)
	{
		PWM_Duty = 1023;
	}

	DCMotor_SetDuty(PWM_Duty);

	PrevError = CurError;		// ���� �������� ���� ���������� ��ü 
}







