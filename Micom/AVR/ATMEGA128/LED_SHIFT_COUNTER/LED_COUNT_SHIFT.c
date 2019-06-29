/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.4 Standard
Automatic Program Generator

Project : 
Version : 
Date    : 2016-09-02
Author  : 
Company : 
Comments: 


Chip type           : ATmega128
Program type        : Application
Clock frequency     : 4.000000 MHz
Memory model        : Small
External RAM size   : 0
Data Stack size     : 1024
*****************************************************/

#include <mega128.h>
#include <stdio.h>
#include <delay.h>
#include "mydef.h"


void main(void)
{

PORTA=0x00;
DDRA=0x00;

PORTB=0x00;
DDRB=0x00;
 
PORTC=0x00;
DDRC=0x00;

PORTD=0x00;
DDRD=0x00;

PORTE=0x00;
DDRE=0x00;

PORTF=0xFF;
DDRF=0xFF;

PORTG=0x00;
DDRG=0x00;

ASSR=0x00;
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

TCCR1A=0x00;
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

TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

TCCR3A=0x00;
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

EICRA=0x00;
EICRB=0x00;
EIMSK=0x00;

TIMSK=0x00;
ETIMSK=0x00;

ACSR=0x80;
SFIOR=0x00;


while (1)
 {             
 u08 i;
 
        LED_ALL_OFF;   
//�ǽ� 4        
//        for(i=8;i>0;i--) {
   for(i=1;i<9;i++) {
        switch(i)
               {
               case 1: LED_PORT = 0B00000001; break;        //0x01
        
               case 2: LED_PORT = 0B00000010; break;        //0X02
        
               case 3: LED_PORT = 0B00000100; break;        //0X40
        
               case 4: LED_PORT = 0B00001000; break;        //0X08
        
               case 5: LED_PORT = 0B00010000; break;        //0X10
        
               case 6: LED_PORT = 0B00100000; break;        //0X20
        
               case 7: LED_PORT = 0B01000000; break;        //0X40
        
               case 8: LED_PORT = 0B10000000; break;        //0X80
               
               default:
               
               break;          
              }        
        delay_ms(200);       
   
      };
 }
                          
}
