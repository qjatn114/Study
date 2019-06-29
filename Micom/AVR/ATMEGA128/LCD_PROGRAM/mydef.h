#ifndef		__def__h
#define		__def__h

#include <delay.h> 

typedef unsigned char		u08;
typedef          char		s08;
typedef unsigned short		u16;
typedef          short		s16;
typedef unsigned long		u32;
typedef          long		s32;

#define ON		0x01
#define OFF		0x00

//(�ǽ�1)
//#define LED_ALL_ON	PORTF = 1
//#define LED_ALL_OFF	PORTF = 0

//(�ǽ�2)
//#define LED_ALL_ON	PORTF = 0xFF
//#define LED_ALL_OFF	PORTF = 0

//(�Ǻ�3)
//#define LED_ALL_ON	PORTF = 0B11110000
//#define LED_ALL_OFF	PORTF = 0B00001111


// LED DEFINE
#define LED8		PORTF.0 =0
#define LED7		PORTF.1	=0
#define LED6		PORTF.2	=0
#define LED5		PORTF.3	=0
#define LED4		PORTF.4	=0
#define LED3		PORTF.5	=0
#define LED2		PORTF.6	=0
#define LED1		PORTF.7	=0

#define DEBUG		PORTB.7
#define BUZZER		PORTB.6
#define	BUZZER_ON	PORTB.6 = 1
#define BUZZER_OFF	PORTB.6 = 0

#define KEY_IN		PINB
#define KEY_MASK	0x0F


#define LCD_RS_0	PORTC.7 = 0
#define LCD_RS_1	PORTC.7 = 1
#define LCD_RW_0	PORTC.5 = 0
#define LCD_RW_1	PORTC.5 = 1
#define LCD_E_0		PORTC.6 = 0
#define LCD_E_1		PORTC.6 = 1



#define LCD_RS_0	PORTC.7 = 0
#define LCD_RS_1	PORTC.7 = 1
#define LCD_RW_0	PORTC.5 = 0
#define LCD_RW_1	PORTC.5 = 1
#define LCD_E_0		PORTC.6 = 0
#define LCD_E_1		PORTC.6 = 1

#define LCD_DELAY	delay_us(2)

#define LCD_DATA_DDR		DDRA
#define LCD_DATA_POUT		PORTA
#define LCD_DATA_PIN		PINA

// Key Definition
#define MODE		0x6    //SW1 
#define MOVE		0xD    //SW2
#define UP		0xB    //SW3  
#define INPUT		0x7    //SW4 

#endif

