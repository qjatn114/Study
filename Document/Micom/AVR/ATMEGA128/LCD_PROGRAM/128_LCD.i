
#pragma used+
sfrb PINF=0;
sfrb PINE=1;
sfrb DDRE=2;
sfrb PORTE=3;
sfrb ADCL=4;
sfrb ADCH=5;
sfrw ADCW=4;      
sfrb ADCSRA=6;
sfrb ADMUX=7;
sfrb ACSR=8;
sfrb UBRR0L=9;
sfrb UCSR0B=0xa;
sfrb UCSR0A=0xb;
sfrb UDR0=0xc;
sfrb SPCR=0xd;
sfrb SPSR=0xe;
sfrb SPDR=0xf;
sfrb PIND=0x10;
sfrb DDRD=0x11;
sfrb PORTD=0x12;
sfrb PINC=0x13;
sfrb DDRC=0x14;
sfrb PORTC=0x15;
sfrb PINB=0x16;
sfrb DDRB=0x17;
sfrb PORTB=0x18;
sfrb PINA=0x19;
sfrb DDRA=0x1a;
sfrb PORTA=0x1b;
sfrb EECR=0x1c;
sfrb EEDR=0x1d;
sfrb EEARL=0x1e;
sfrb EEARH=0x1f;
sfrw EEAR=0x1e;   
sfrb SFIOR=0x20;
sfrb WDTCR=0x21;
sfrb OCDR=0x22;
sfrb OCR2=0x23;
sfrb TCNT2=0x24;
sfrb TCCR2=0x25;
sfrb ICR1L=0x26;
sfrb ICR1H=0x27;
sfrw ICR1=0x26;   
sfrb OCR1BL=0x28;
sfrb OCR1BH=0x29;
sfrw OCR1B=0x28;  
sfrb OCR1AL=0x2a;
sfrb OCR1AH=0x2b;
sfrw OCR1A=0x2a;  
sfrb TCNT1L=0x2c;
sfrb TCNT1H=0x2d;
sfrw TCNT1=0x2c;  
sfrb TCCR1B=0x2e;
sfrb TCCR1A=0x2f;
sfrb ASSR=0x30;
sfrb OCR0=0x31;
sfrb TCNT0=0x32;
sfrb TCCR0=0x33;
sfrb MCUCSR=0x34;
sfrb MCUCR=0x35;
sfrb TIFR=0x36;
sfrb TIMSK=0x37;
sfrb EIFR=0x38;
sfrb EIMSK=0x39;
sfrb EICRB=0x3a;
sfrb RAMPZ=0x3b;
sfrb XDIV=0x3c;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x20
	.EQU __sm_mask=0x1C
	.EQU __sm_powerdown=0x10
	.EQU __sm_powersave=0x18
	.EQU __sm_standby=0x14
	.EQU __sm_ext_standby=0x1C
	.EQU __sm_adc_noise_red=0x08
	.SET power_ctrl_reg=mcucr
	#endif
#endasm

#pragma used+

void delay_us(unsigned int n);
void delay_ms(unsigned int n);

#pragma used-

typedef unsigned char		u08;
typedef          char		s08;
typedef unsigned short		u16;
typedef          short		s16;
typedef unsigned long		u32;
typedef          long		s32;

void lcd_init(void);
void lcd_home(void);
void lcd_clear(void);
void lcd_print_data(char* data, u08 n_bytes);
void lcd_control_write(u08 data);
void lcd_data_write(u08 data);  

void lcd_init_HW(void)
{

PORTC.7 = 0;
PORTC.5 = 0;
PORTC.6 = 0;

PORTC.7 = 1;
PORTC.5 = 1;
PORTC.6 = 1;

PORTA = 0xFF;
DDRA = 0x00;
}

void lcd_busy_wait(void)
{
PORTC.7 = 0;                
DDRA = 0x00;     
PORTA = 0xFF;    
PORTC.5 = 1;                
PORTC.6 = 1;                 
delay_us(2);               

while(PINA & (1 << 7      ))
{
PORTC.6 = 0;     
delay_us(2);   
delay_us(2);   
PORTC.6 = 1;     
delay_us(2);   
delay_us(2);   
}
PORTC.6 = 0;         
}

void lcd_control_write(u08 data) 
{
lcd_busy_wait();     
PORTC.7 = 0;            
PORTC.5 = 0;            
PORTC.6 = 1;             
DDRA = 0xFF; 
PORTA = data;
delay_us(2);           
delay_us(2);           
PORTC.6 = 0;             
DDRA = 0x00; 
PORTA = 0xFF;
}

u08 lcd_control_read(void)
{
u08 data;
lcd_busy_wait();      
DDRA = 0x00;  
PORTA = 0xFF; 
PORTC.7 = 0;             
PORTC.5 = 1;             
PORTC.6 = 1;              
delay_us(2);            
delay_us(2);            
data = PINA;  
PORTC.6 = 0;              
return data;
}

void lcd_data_write(u08 data) 
{
lcd_busy_wait();            
PORTC.7 = 1;                   
PORTC.5 = 0;                   
PORTC.6 = 1;                    
DDRA = 0xFF;        
PORTA = data;       
delay_us(2);                  
delay_us(2);                  
PORTC.6 = 0;                    
DDRA = 0x00;        
PORTA = 0xFF;       
}

void lcd_init(void)
{

delay_ms(100);

lcd_control_write(0x3A);
delay_ms(60);    

lcd_control_write(0x01);
delay_ms(60);   

lcd_control_write(0x0C);
delay_ms(20);

lcd_control_write(0x02);
delay_ms(20);

lcd_control_write(0x00);

}

void lcd_home(void)
{

lcd_control_write(0x02);
}

void lcd_clear(void)
{

lcd_control_write(0x01);
}

void lcd_print_data(u08* data, u08 n_bytes)
{
u08 i;

for(i=0; i < n_bytes; i++)
{
lcd_data_write(data[i]);
}
}
