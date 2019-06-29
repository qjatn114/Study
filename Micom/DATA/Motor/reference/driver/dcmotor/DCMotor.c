#include "at90can128.h"
#include "pwm.h"
#include <avr/interrupt.h>


/***** DC ���� �� �� *****/
// MOTOR_DIR 			: PORTB2
// MOTOR_PWM 			: PORTB5(OC1A:Channel A)
// MOTOR_ROTATION_SIG 	: PORTD1(INT1), PORTD4(ICP1)
// CURRENT_FAULT		: PORTD0(INT0)


#define DCMOTOR_DIR_PIN	PORTB2
#define DCMOTOR_PWM_PIN	PORTB5



/**
* @fn		void DCMotor_Init(void)
* @brief
*	-DC Motor �ʱ�ȭ �Լ� 
* @remarks
* @param	void
* @return	void			
*/
void DCMotor_Init(void)
{
	/****** ��Ʈ �ʱ�ȭ *****/
	PORTB2 = 0;		// MOTOR_DIR
	DDB2 = 1;	
	PORTB5 = 0;		// MOTOR_PWM
	DDB5 = 1;

	/***** ���ͷ�Ʈ �ʱ�ȭ : CURRENT_FAULT(INT0) *****/
	ISC01 = 1;		// 10 : Falling edge, 11 : Rising edge
	ISC00 = 0;	 		
//	INT0 = 1;		// ���ͷ�Ʈ Ȱ��ȭ 	 

	/***** PWM �ʱ�ȭ *****/
	PWM_Init(PWM_CH_A);			
	PWM_SetDuty(0);
	PWM_A_Disable();
}

/**
* @fn		void DCMotor_Start(void)
* @brief
*	-DC Motor ���۽�Ų��.
* @remarks
* @return	void			
*/
void DCMotor_Start(void)
{
	PWM_A_Enable();		// PWM �� ����Ѵ�. 
}


/**
* @fn		void DCMotor_Stop(void)
* @brief
*	-DC Motor ������Ų��.
* @remarks
* @return	void			
*/
void DCMotor_Stop(void)
{
	PWM_A_Disable();	// PWM����� �����Ѵ�. 
}

/**
* @fn		void DCMotor_SetDuty(unsigned short Duty)
* @brief
*	-DC Motor PWM�� ��Ƽ�� �����Ѵ�. 
* @remarks
* @param	unsigned short Duty	: Duty �� (0 ~ 1023)
* @return	void			
*/
void DCMotor_SetDuty(unsigned short Duty)
{
		PWM_SetDuty(Duty);	
}

unsigned short DCMotor_GetDuty(void)
{
	return PWM_A_GetDuty();
}



void DCMotor_SetDirection(unsigned char Direction)		// 0 : CW,  1 : CCW
{
	DCMOTOR_DIR_PIN = Direction;
}



/**
* @fn		ISR(INT0_vect)
* @brief
*	- �ܺ� ���ͷ�Ʈ 0 ISR(Interrupt Service Routine)  
*	- CURRENT_FAULT ���ͷ�Ʈ 
* @remarks
* @param	INT0_vect	: ���ͷ�Ʈ ���� ��ȣ 
* @return	void			
*/
ISR(INT0_vect)
{
	PWM_A_Disable();	// PWM����� �����Ѵ�. 
}

