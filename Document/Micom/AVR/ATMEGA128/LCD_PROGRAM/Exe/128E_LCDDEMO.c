#include <mega128.h>
#include <stdio.h>
#include <delay.h>
#include "mydef.h"
#include "lcd.h"

void update_lcd(void);
void set_led(u08 n);        
u08 time_count;
bit time_flag;        
u16 tmp_buf[10];
u08 tmp_index;

eeprom u08 eep_model=1;
eeprom u32 eep_average_fuel=0;

volatile u08 buzzer_count;

u08 lcd_mode;
u08 count;

u08 str_mega128[] = "MEGA128 ";
u08 str_welcome[] = "WELCOME:";

u08 str_countup[] = "CNT-UP: ";
u08 str_ea[] = "EA";
u08 str_blank[] = "       ";
 

void set_led(u08 n) //ON, POSITION
{
	switch(n)
	{
	 case 0: PORTF = 0x00;  break; 
	 case 1: PORTF = 0x01;  break; 
	 case 2: PORTF = 0x03;  break;
	 case 3: PORTF = 0x07;  break;
	 case 4: PORTF = 0x0F;	break;
	 case 5: PORTF = 0x1F;	break;
	 case 6: PORTF = 0x3F;  break;
	 case 7: PORTF = 0x7F;  break;
	 case 8: PORTF = 0xFF;  break;  	
	 default: PORTD = 0x01; break;	
	}
}
void main(void)
{
u08 i;

	PORTA = 0x00;
	DDRA = 0x00;
	
	DDRB = 0x40; 		//INPUT MODE AND BUZZER = OUPUT
	PORTB = 0x0F;           //PULL UP ON
	
	PORTC = 0x00;
	DDRC = 0xFF;	
	
	PORTD=0x00; //output all 0 ,PULL UP OFF
	DDRD= (0x01<<7)|(0x01<<6)|(0x01<<5)|(0x01<<4)|(0x01<<3)|(0x01<<2)|(0x01<<1)|(0x01<<0); //all output set
	
	PORTE = 0x00 | (0x03 << 6);
	DDRE = 0x00;
	
	PORTF = 0x00;
	DDRF = 0xFF;
	
	PORTG = 0x03;           
	DDRG = 0x01;
//-----------------------------------------------
    ASSR=0x00;
    TCCR0==0x00;
    TCNT0=0x00;
    OCR0=0x00;    

    TCCR1A==0x00;
    TCCR1B=0x00;
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;
    OCR1CH=0x00;
    OCR1CL=0x00;

    TCCR2==0x00;
    TCNT2=0x00;
    OCR2=0x00;

    TCCR3A==0x00;
    TCCR3B=0x00;
    TCNT3H=0x00;
    TCNT3L=0x00;
    ICR3H=0x00;
    ICR3L=0x00;
    OCR3AH=0x00;
    OCR3AL=0x00;
    OCR3BH=0x00;
    OCR3BL=0x00;
    OCR3CH=0x00;
    OCR3CL=0x00;

    EICRA==0x00;
    EICRB=0x00;
    EIMSK==0x00;	
    
	EIFR = 0x00 | 0xc0;      
     
    TIMSK=0x00;
    ETIMSK=0x00;
    
    UCSR0B=0x00;
    UCSR1B==0x00; 
    ACSR=0x08;
    SFIOR==0x00;

    ADCSRA==0x00;
    SPCR==0x00;

    TWCR==0x00;
//********************************************** 
	
	lcd_mode = 1;
    
	lcd_init();
    lcd_clear();
	lcd_home();

    lcd_control_write(0x80);
	lcd_print_data(str_welcome,8);
    
    delay_ms(500);
    
    lcd_control_write(0xC0);		
    lcd_print_data(str_mega128,8);	
	delay_ms(3000);    
	delay_ms(3000);

	lcd_home();	
	lcd_clear();

    lcd_control_write(0x80);		    
    lcd_print_data(str_countup,8);
    lcd_control_write(0xC5);		    
    lcd_print_data(str_ea,2);    	              
        
//	#asm("sei")

    count = 0;

	while (1)
	{        
	    for(i=1;i<9;i++) {set_led(i);delay_ms(100);}	
//	    BUZZER_ON;
//	    delay_ms(200);
//      BUZZER_OFF;   
        
        for(i=8;i>0;i--) {set_led(i);delay_ms(100);}	
    	BUZZER_ON;
    	delay_ms(200);
        BUZZER_OFF;
        
        count = count+1;          
        if (count>9) count = 0;        
        
        lcd_control_write(0xC1);		
        lcd_data_write(0x30+count); //ASCII CODE 	
	    delay_ms(500);         
    	
	};
}



