
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

typedef char *va_list;

#pragma used+

char getchar(void);
void putchar(char c);
void puts(char *str);
void putsf(char flash *str);
int printf(char flash *fmtstr,...);
int sprintf(char *str, char flash *fmtstr,...);
int vprintf(char flash * fmtstr, va_list argptr);
int vsprintf(char *str, char flash * fmtstr, va_list argptr);

char *gets(char *str,unsigned int len);
int snprintf(char *str, unsigned int size, char flash *fmtstr,...);
int vsnprintf(char *str, unsigned int size, char flash * fmtstr, va_list argptr);

int scanf(char flash *fmtstr,...);
int sscanf(char *str, char flash *fmtstr,...);

#pragma used-

#pragma library stdio.lib

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

void set_led(u08 n) 
{
switch(n)
{
case 0: (*(unsigned char *) 0x62) = 0x00;  break; 
case 1: (*(unsigned char *) 0x62) = 0x01;  break; 
case 2: (*(unsigned char *) 0x62) = 0x03;  break;
case 3: (*(unsigned char *) 0x62) = 0x07;  break;
case 4: (*(unsigned char *) 0x62) = 0x0F;	break;
case 5: (*(unsigned char *) 0x62) = 0x1F;	break;
case 6: (*(unsigned char *) 0x62) = 0x3F;  break;
case 7: (*(unsigned char *) 0x62) = 0x7F;  break;
case 8: (*(unsigned char *) 0x62) = 0xFF;  break;  	
default: PORTD = 0x01; break;	
}
}
void main(void)
{
u08 i;

PORTA = 0x00;
DDRA = 0x00;

DDRB = 0x40; 		
PORTB = 0x0F;           

PORTC = 0x00;
DDRC = 0xFF;	

PORTD=0x00; 
DDRD= (0x01<<7)|(0x01<<6)|(0x01<<5)|(0x01<<4)|(0x01<<3)|(0x01<<2)|(0x01<<1)|(0x01<<0); 

PORTE = 0x00 | (0x03 << 6);
DDRE = 0x00;

(*(unsigned char *) 0x62) = 0x00;
(*(unsigned char *) 0x61) = 0xFF;

(*(unsigned char *) 0x65) = 0x03;           
(*(unsigned char *) 0x64) = 0x01;

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
(*(unsigned char *) 0x79)=0x00;
(*(unsigned char *) 0x78)=0x00;

TCCR2==0x00;
TCNT2=0x00;
OCR2=0x00;

(*(unsigned char *) 0x8b)==0x00;
(*(unsigned char *) 0x8a)=0x00;
(*(unsigned char *) 0x89)=0x00;
(*(unsigned char *) 0x88)=0x00;
(*(unsigned char *) 0x81)=0x00;
(*(unsigned char *) 0x80)=0x00;
(*(unsigned char *) 0x87)=0x00;
(*(unsigned char *) 0x86)=0x00;
(*(unsigned char *) 0x85)=0x00;
(*(unsigned char *) 0x84)=0x00;
(*(unsigned char *) 0x83)=0x00;
(*(unsigned char *) 0x82)=0x00;

(*(unsigned char *) 0x6a)==0x00;
EICRB=0x00;
EIMSK==0x00;	

EIFR = 0x00 | 0xc0;      

TIMSK=0x00;
(*(unsigned char *) 0x7d)=0x00;

UCSR0B=0x00;
(*(unsigned char *) 0x9a)==0x00; 
ACSR=0x08;
SFIOR==0x00;

ADCSRA==0x00;
SPCR==0x00;

(*(unsigned char *) 0x74)==0x00;

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

count = 0;

while (1)
{        
for(i=1;i<9;i++) {set_led(i);delay_ms(100);}	

for(i=8;i>0;i--) {set_led(i);delay_ms(100);}	
PORTB.6 = 1;
delay_ms(200);
PORTB.6 = 0;

count = count+1;          
if (count>9) count = 0;     

lcd_control_write(0xC1);		
lcd_data_write(0x30+count); 
delay_ms(500);         

};
}

