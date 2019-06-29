/**
* @file		led.c
* @brief		LED  ����̹�  
* @author		���̼�/ �ַ�� ���� ���� �п� 	
* @remarks
* @par �����̷� 
*	@li	2012.11.06 : �ʱ�  �Լ� �ۼ�  
*/

#include "at90can128.h"


// LED 0 ~3 : PORTC4 ~ 7 



/**
* @fn		void LED_Init(void)
* @brief
*	- LED �ʱ�ȭ �Լ� 
* @remarks
* @param	void
* @return	void			
*/
void LED_Init(void)
{
	// ��Ʈ �ʱ�ȭ 
	PORTC &= 0x0F;			// PORTC4 ~ 7�� 0 ���
	DDRC |= 0xF0;			// PORTC4 ~ 7�� ��������� ����.
}

/**
* @fn		void LED0_On(unsigned char OnOff)
* @brief
*	- LED0 �� On/Off 
* @remarks
* @param	unsigned char Data		: On/Off ������ 
* @return	void			
*/
void LED0_On(unsigned char OnOff)
{
	PORTC4 = (OnOff)? 1 : 0;
}

/**
* @fn		void LED1_On(unsigned char OnOff)
* @brief
*	- LED0 �� On/Off 
* @remarks
* @param	unsigned char Data		: On/Off ������ 
* @return	void			
*/
void LED1_On(unsigned char OnOff)
{
	PORTC5 = (OnOff)? 1 : 0;
}

/**
* @fn		void LED2_On(unsigned char OnOff)
* @brief
*	- LED0 �� On/Off 
* @remarks
* @param	unsigned char Data		: On/Off ������ 
* @return	void			
*/
void LED2_On(unsigned char OnOff)
{
	PORTC6 = (OnOff)? 1 : 0;
}

/**
* @fn		void LED3_On(unsigned char OnOff)
* @brief
*	- LED0 �� On/Off 
* @remarks
* @param	unsigned char Data		: On/Off ������ 
* @return	void			
*/
void LED3_On(unsigned char OnOff)
{
	PORTC7 = (OnOff)? 1 : 0;
}



