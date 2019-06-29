#include <mega128.h>
#include <stdio.h>
#include <delay.h>
#include "def.h"
#include "lcd.h"

void key_chack(void);
void update_lcd(void);
void set_led(u08 n);

u08 rx_buf[101];
u08 rx_buf_index;
bit rx_start_flag;
bit rx_comp_flag;

//u16 a_pulse_width;
//bit a_pulse_flag;

//u16 b_pulse_width;
//bit b_pulse_flag;

u08 time_count;
bit time_flag;
float fuel_rate;           
float car_speed;      
float instant_fuel;   
float average_fuel;     
float period_fuel; 
float fuel_imsi;

u16 tmp_buf[10];
u08 tmp_index;
bit fuelcut;  
u08 fuel_count =0;    

//eeprom u08 pass_eep[4]={0x00,0x00,0x00,0x00};
//eeprom u08 s_flag_eep[5];
//eeprom u08 wait_time_eep=0x30;
//eeprom u08 test_eep=0x00;
//eeprom u08 g_state_eep=0x00;
//eeprom u08 d_state_eep=0x00;
//eeprom u08 date_eep[2]={0x12,0x19};
//eeprom u08 time_eep[2]={0x00,0x00};
//eeprom u08 id_eep=1;
//eeprom u08 ring_n_eep=0x06;
//eeprom u08 delay_eep=0x01;

eeprom u08 eep_model=1;
eeprom u32 eep_average_fuel=0;

typedef struct pulse__data {
			u08 width_str[7];
			u16 timer_s;
			u16 timer_e;
			u16 timer_value;
			u08 flag;
 			} pulse_data;

struct gps__data {
			u08 latitude[16];
			u08 dir_latitude;
			u08 longitude[16];
			u08 dir_longitude;
			u08 speed[8];
 			} gps_data;

pulse_data a_pulse, b_pulse;
u08 pulse_out_time;

struct fueldata{ 
                 	u16 i_fuel[7];
                 	u16 a_fuel[7];
		}fuel_data;
		
struct car_model{
                 	u08 cc[7];
		}cc_model;		

volatile bit key_flag, p_flag;
volatile u08 old_key, new_key, key_buf;
volatile u08 buzzer_count;

u08 uart_mode;
u08 lcd_mode;
u08 model;
u16 model_cc;

u08 str_logo[] = " MK ELECTRONICS ";
u08 str_welld[] = "  OIL-SAVER 3.0A";
u08 str_a_pulse[] = "LOAD-T :";
u08 str_b_pulse[] = "B Width:";
u08 str_ms[] = " %";
u08 str_latitude[] =  "  GPS Latitude  ";
u08 str_longitude[] = "  GPS Longitude ";
u08 str_average[] =   "T-Fuel:     Km/l";
u08 str_instant[] =   "P-Fuel:     Km/l";
u08 str_model[] =     "  SELECT MODEL  ";   
u08 str_erase[] =     "  CLEAR T-FUEL  ";

u08 str_east[] = "EAST: ";
u08 str_west[] = "WEST: ";
u08 str_north[] = "NORTH:";
u08 str_south[] = "SOUTH:";
u08 str__speed[] = "GPS SPEED DATA->";
u08 str_speed[] = "SPEED:";
u08 str_speed_unit[] = "Km/H";
u08 str_blank[] = "                ";
u08 str_fuelcut[]="   Fuel Cut!!   "; 
u08 str_km_l[] = "km/l";
u08 str_fuel[] = "Fuel:";

u08 str_1200[] ="1200 CC";
u08 str_1500[] ="1500 CC";
u08 str_1800[] ="1800 CC";
u08 str_2000[] ="2000 CC";
u08 str_2400[] ="2400 CC";
u08 str_2500[] ="2500 CC";
u08 str_3000[] ="3000 CC";
u08 str_3500[] ="3500 CC";
u08 str_4000[] ="4000 CC";
u08 str_yes[] = "O.K";
u08 str_del[] = "EREASE?";

// External Interrupt 6 service routine
interrupt [EXT_INT6] void ext_int6_isr(void)
{
u16 tmp_val;
	tmp_val = TCNT1;	


	if(EICRB & (0x01 << 4))
	{
//		if(tmp_val < 50) return;
		EXT6_FALLING_EDGE;
		if(tmp_val < b_pulse.timer_s)
		{
			b_pulse.timer_s = 0xffff - b_pulse.timer_s;
			b_pulse.timer_value = tmp_val + b_pulse.timer_s;
		}
		else
		{
			b_pulse.timer_value = tmp_val - b_pulse.timer_s;
		}	
		b_pulse.flag = 1;			
	}	
	else 
	{
		b_pulse.timer_s = tmp_val;
		EXT6_RISING_EDGE;
		TCNT2 = 0xff - pulse_out_time;
		TCCR2 = 0x05;
		P_OUT = 0;
	}	
		tmp_buf[tmp_index] = tmp_val;
		tmp_index++;
		if(tmp_index >= 10) tmp_index = 0;

}

// External Interrupt 7 service routine
interrupt [EXT_INT7] void ext_int7_isr(void)
{
u16 tmp_val;
	tmp_val = TCNT1;	
	if(EICRB & (0x01 << 6))
	{
//		if(tmp_val < 50) return;
		EXT7_FALLING_EDGE;
		if(tmp_val < a_pulse.timer_s)
		{
			a_pulse.timer_s = 0xffff - a_pulse.timer_s;
			a_pulse.timer_value = tmp_val + a_pulse.timer_s;
		}
		else
		{
			a_pulse.timer_value = tmp_val - a_pulse.timer_s;
		}	
		a_pulse.flag = 1;
	}	
	else 
	{
		a_pulse.timer_s = tmp_val;
		EXT7_RISING_EDGE;
	}	
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
	if(!BUZZER) key_chack();
	
	buzzer_count--;
	if(!buzzer_count) BUZZER = 0;
	
	time_count++;
	if(time_count >= 43)
	{
		time_count = 0;
		time_flag = 1;
		if(DEBUG) DEBUG = 0;
		else DEBUG = 1;
	}
}

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
}

interrupt [TIM3_OVF] void timer3_ovf_isr(void)
{
}

interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
	TCCR2 = 0x00;
	P_OUT = 1;
}

interrupt [USART0_RXC] void uart0_rx_isr(void)
{
u08 tmp_status,tmp_data;
	tmp_status = UCSR0A;
	tmp_data = UDR0;
	
	if(rx_comp_flag) return;
	
	if ((tmp_status & (FRAMING_ERROR | DATA_OVERRUN)) == 0)
	{
		rx_buf[rx_buf_index] = tmp_data;
		if(!rx_start_flag)
		{
			if(tmp_data == '$') 
			{
				rx_start_flag = 1;
				rx_buf_index++;
			}	
		}	
		else
		{
			if(tmp_data == 0x0a)
			{
				if(rx_buf[rx_buf_index - 1] == 0x0d)
				{
					if(rx_buf[3] == 'R') rx_comp_flag = 1;
					rx_buf[100] = rx_buf_index;
					rx_start_flag = 0;
					rx_buf_index = 0;
					return;
				}
			}
			rx_buf_index++;
			if(rx_buf_index >= 100)
			{
				rx_start_flag = 0;
				rx_buf_index = 0;
				return;
			}	
			if(tmp_data == '$') 
			{
				rx_start_flag = 1;
				rx_buf_index = 1;
				return;
			}	
		}	
	}
	else 
	{
		rx_buf_index = 0;
		rx_start_flag = 0;
	}	
}

void uart_put_char(u08 tmp_data)
{
	while(!(UCSR0A & (1 << UDRE)));
	UDR0 = tmp_data;
}	

void key_chack(void)
{
u08 tmp_key;
	tmp_key = KEY_IN & KEY_MASK;

	PORTF = tmp_key;
	
	
	if(tmp_key == KEY_MASK) 
	{
		p_flag = 0;
		new_key = old_key = 0;
		return;
	}	
	if(p_flag) 
	{
		p_flag = 0;
		if(new_key != tmp_key) new_key = old_key;
		else
		{
			old_key = new_key;
			key_buf = new_key;
			key_flag = 1;
		}		
	}
	else 
	{
		new_key = tmp_key;
		if(new_key != old_key) p_flag = 1;
	}
}	


void init_port(void)
{
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
}	

void init_timer(void)
{
	ASSR = 0x00;
	TCCR0 = 0x07;
	TCNT0 = 0x00;
	OCR0 = 0x00;
	
	TCCR1A = 0x00;
	TCCR1B = 0x04;
	TCNT1H = 0x00;
	TCNT1L = 0x00;
	OCR1AH = 0x00;
	OCR1AL = 0x00;
	OCR1BH = 0x00;
	OCR1BL = 0x00;
	OCR1CH = 0x00;
	OCR1CL = 0x00;
	
	TCCR2 = 0x00;
	TCNT2 = 0x00;
	OCR2 = 0x00;
	
	TCCR3A = 0x00;
	TCCR3B = 0x04;
	TCNT3H = 0x00;
	TCNT3L = 0x00;
	OCR3AH = 0x00;
	OCR3AL = 0x00;
	OCR3BH = 0x00;
	OCR3BL = 0x00;
	OCR3CH = 0x00;
	OCR3CL = 0x00;
}	

void init_int(void)
{
	EICRA = 0x00;
	EICRB = 0x00 | 0xa0;
	EIMSK = 0x00 | 0xc0;
	EIFR = 0x00 | 0xc0;

	TIMSK = 0x04 | 0x01 | 0x40;
	ETIMSK = 0x04;
}	

void init_uart(void)
{
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	UBRR0H = 0x00;	
	UBRR0L = RX_BAUDE;
}	
		
void init_sys(void)
{
	init_port();
	init_timer();
	init_int();
	init_uart();
	ACSR = 0x80;
	SFIOR = 0x00;	
}

// 1Knots --> 0.5m/Sec
void cal_speed(void)
{
u08 i;
float tmp_dig, n_dig;
float tmp_speed;
float last_speed;

	tmp_dig = 1;
	tmp_speed = 0;
	i = 8;
	while(1)
	{	
		i--;
		if(gps_data.speed[i] == '.') n_dig = tmp_dig;
		else
		{
			tmp_speed += (tmp_dig * ((float)(gps_data.speed[i] - 0x30)));
			tmp_dig *= 10;
		}
		gps_data.speed[i] = 0;
		if(!i) break;
	}	
	tmp_speed /= n_dig;
	tmp_speed /= 2;
	tmp_speed *= 3600;    
//	tmp_speed = 10000;  //test data
	last_speed = tmp_speed /1000;
//	sprintf(gps_data.speed, "%6.2f", tmp_speed);	
	sprintf(gps_data.speed, "%6.2f", last_speed);		
	car_speed = tmp_speed; 	
}	


void send_data_uart(void)
{
u08 i, k;
u08 tmp_buf[16];
	
	tmp_buf[0] = 0x02;	//stx
	
	UBRR0L = TX_BAUDE;
	delay_ms(1);
	switch(uart_mode)
	{
		case A_PULSE_WIDTH:
		tmp_buf[1] = A_PULSE_WIDTH;
		for(i = 0; i < 6; i++) tmp_buf[i + 2] = a_pulse.width_str[i];
		tmp_buf[8] = 'm';
		tmp_buf[9] = 's'; 
		tmp_buf[10] = ' ';
		tmp_buf[11] = ' ';
		break;
		
		case B_PULSE_WIDTH:
		tmp_buf[1] = B_PULSE_WIDTH;
		for(i = 0; i < 6; i++) tmp_buf[i + 2] = b_pulse.width_str[i];
		tmp_buf[8] = 'm';
		tmp_buf[9] = 's'; 
		tmp_buf[10] = ' ';
		tmp_buf[11] = ' ';
		break;

		case GPS_LATITUDE:
		tmp_buf[1] = GPS_LATITUDE;
		for(i = 0; i < 10; i++) tmp_buf[i + 2] = gps_data.latitude[i];
		break;

		case GPS_LONGITUDE:
		tmp_buf[1] = GPS_LONGITUDE;
		for(i = 0; i < 10; i++) tmp_buf[i + 2] = gps_data.longitude[i];
		break;

		case GPS_SPEED:
		tmp_buf[1] = GPS_SPEED;
		for(i = 0; i < 6; i++) tmp_buf[i + 2] = gps_data.speed[i];
		tmp_buf[8] = 'K';
		tmp_buf[9] = 'm'; 
		tmp_buf[10] = '/';
		tmp_buf[11] = 'H';
		break;
	}   		
	
	k = 0;	
	for(i = 0; i < 12; i++) k += tmp_buf[i];
	tmp_buf[12] = k;
	tmp_buf[13] = 0x03;
	tmp_buf[14] = 0x0d;
	tmp_buf[15] = 0x0a;

	for(i = 0; i < 16; i++)
	{
		uart_put_char(tmp_buf[i]);
	}	

	delay_ms(5);
	UBRR0L = RX_BAUDE;
	delay_ms(1);
}	

void parse_GPS_data(void)
{
u08 i, j;
	rx_comp_flag = 0;
	for(i = 0; i < 16; i++)
	{
		gps_data.latitude[i] = ' ';
		gps_data.longitude[i] = ' ';
	}		
	j = 0;
	for(i = 0; i < 100; i++)
	{
		if(rx_buf[i] == ',') j++;
		if(j == 3) break;
	}			
	for(j = 0; j < 10; j++)
	{
		i++;
		if(rx_buf[i] == ',') break;
		gps_data.latitude[j] = rx_buf[i];
	}		
	j = 0;
	for(i = 0; i < 100; i++)
	{
		if(rx_buf[i] == ',') j++;
		if(j == 4) break;
	}               			
	i++;
	gps_data.dir_latitude = rx_buf[i];

	j = 0;
	for(i = 0; i < 100; i++)
	{
		if(rx_buf[i] == ',') j++;
		if(j == 5) break;
	}		
	for(j = 0; j < 10; j++)
	{
		i++;
		if(rx_buf[i] == ',') break;
		gps_data.longitude[j] = rx_buf[i];
	}		
//	lcd_goto_XY(0, 1);
//	lcd_print_data(gps_data.longitude, 10);
	j = 0;
	for(i = 0; i < 100; i++)
	{
		if(rx_buf[i] == ',') j++;
		if(j == 6) break;
	}
		

	i++;
	gps_data.dir_longitude = rx_buf[i];

	j = 0;
	for(i = 0; i < 100; i++)
	{
		if(rx_buf[i] == ',') j++;
		if(j == 7) break;
	}
		
	for(j = 0; j < 8; j++) gps_data.speed[j] = '0';
	for(j = 0; j < 8; j++)
	{
		i++;
		if(rx_buf[i] == ',') break;
		gps_data.speed[j] = rx_buf[i];
	}
	cal_speed();
	
	send_data_uart();
}	

void init_variable(void)
{
	rx_buf_index = 0;
	rx_start_flag = 0;
	rx_comp_flag = 0;
	a_pulse.flag = 0;	
	time_count = 0;
	time_flag = 0;   	
	tmp_index = 0;   	
	pulse_out_time = 23;		//b pulse output width	
	uart_mode = 1;
	lcd_mode = 1;
}	

void cal_a_pulse(void)
{
float tmp_val;

	tmp_val = ((float)a_pulse.timer_value) * 0.023;	
	sprintf(a_pulse.width_str, "%6.2f", tmp_val);    

	fuelcut =0;
	if(tmp_val<= 2) {  //fuel-cut
			set_led(1);
			fuelcut =1;
	}	
	else	if(tmp_val<4.1) set_led(2);
		else if(tmp_val<7.0) set_led(3);
		else if(tmp_val<9.0) set_led(4);	
		     else if(tmp_val<11.0) set_led(5);
			  else if(tmp_val<13.0) set_led(6);
			       else if(tmp_val<15.0) set_led(7);
				    else { set_led(8);				
//				    	   BUZZER_ON;
//				    	   delay_ms(200);
//				    	   BUZZER_OFF;
				    }				    
	fuel_rate = tmp_val;      	
	fuel_imsi = tmp_val;
}	

void cal_b_pulse(void)
{
float tmp_val;
float new_fuel;

	tmp_val = ((float)b_pulse.timer_value) * 0.023;	
//	fuel_rate = (2200/800)*1400*(fuel_rate/2.6);    

//	fuel_rate = 2450 *(fuel_rate/2.6);
	fuel_rate = model_cc *(fuel_rate/2.6);
//	fuel_rate = (car_speed*1000)/fuel_rate;	       	    
	
	new_fuel = fuel_rate;		
	fuel_rate = (car_speed)/fuel_rate;	   	    	
	if(fuel_rate<1) fuel_rate = 10000/new_fuel;
	
	sprintf(b_pulse.width_str,"%6.1f",fuel_rate);	
	instant_fuel = (instant_fuel + fuel_rate)/2;
	
	fuel_count++;
	if(fuel_count>=60) { //60초에 한번씩 계산
	period_fuel = (period_fuel + instant_fuel)/2;   //1분에 한번씩 저장 
	average_fuel=  (average_fuel + period_fuel)/2;
  	eep_average_fuel = average_fuel*100;            //메모리에 기록 	
	fuel_count =0;
	}

//	sprintf(fuel_data.i_fuel,"%5.2f",period_fuel);	
//	sprintf(fuel_data.a_fuel,"%5.2f",average_fuel);
}	


void select_model(void)
{					
 	switch(model)
 	{
	case 1:	lcd_print_data(str_1200,7); model_cc = 1466;break;
	case 2:	lcd_print_data(str_1500,7); model_cc = 1833;break;
	case 3:	lcd_print_data(str_1800,7); model_cc = 2200;break;
	case 4:	lcd_print_data(str_2000,7); model_cc = 2450;break;
	case 5:	lcd_print_data(str_2400,7); model_cc = 2400;break;  //에러
	case 6:	lcd_print_data(str_2500,7); model_cc = 3055;break;
	case 7:	lcd_print_data(str_3000,7); model_cc = 3680;break;
	case 8:	lcd_print_data(str_3500,7); model_cc = 4235;break;
	case 9:	lcd_print_data(str_4000,7); model_cc = 4888;break;
	case 10:lcd_print_data(str_del,7);  break; 
	default : 		            model_cc = 2200;break;
 	}   
}
 
void set_model(void)
{
 	lcd_clear();
 	delay_ms(100);  
	if(model!=10) {
		lcd_goto_XY(0,0);
		lcd_print_data(str_model,16);
		lcd_goto_XY(4,1);
	}
	else {
	  	lcd_goto_XY(0,0);
		lcd_print_data(str_erase,16);
		lcd_goto_XY(4,1);		
	}
	select_model();	 
}
	

void set_lcd_mode(void)
{
	lcd_clear();
	delay_ms(100);
	switch(lcd_mode)
	{
		case 0x01:
		lcd_goto_XY(0, 0);
		lcd_print_data(str_a_pulse, 8);
		lcd_goto_XY(14, 0);
		lcd_print_data(str_ms, 2);

		lcd_goto_XY(0, 1);
		lcd_print_data(str_fuel,5);	
		lcd_goto_XY(12, 1);			
		lcd_print_data(str_km_l,4);		//1112
		break;
		
		case 0x02:				//방위를 표시함
		lcd_goto_XY(0, 0);
		lcd_print_data(str_latitude,16);   	
		break;

		case 0x03:				//평균연비,구간연비를 표시함
		lcd_goto_XY(0, 0);
		lcd_print_data(str_longitude, 16);
		break;

		case 0x04:
		lcd_goto_XY(0, 0);
		lcd_print_data(str__speed, 16);
				
//		lcd_goto_XY(0, 0);
//		if (fuelcut) lcd_print_data(str_fuelcut,16);
//		else lcd_print_data(str_blank,16);
		
		lcd_goto_XY(0, 1);
		lcd_print_data(str_speed, 6);
		lcd_goto_XY(12, 1);
		lcd_print_data(str_speed_unit, 4);
		break;
		
		case 0x05:
		lcd_goto_XY(0,0);
		lcd_print_data(str_instant,16);
		lcd_goto_XY(12, 0);			
		lcd_print_data(str_km_l,4);		
		lcd_goto_XY(0,1);
		lcd_print_data(str_average,16);
		lcd_goto_XY(12, 1);			
		lcd_print_data(str_km_l,4);
		break;           		
		
		case 0x06: break;
	}
}	

void update_data(void)
{
	time_flag = 0;
	if(a_pulse.flag)
	{
		a_pulse.flag = 0;
		cal_a_pulse();
	}
	else 
	{
		a_pulse.timer_value = 0;
		cal_a_pulse();
	}	
		
	if(b_pulse.flag)
	{
		b_pulse.flag = 0;
		cal_b_pulse();
	}
	else 
	{
		b_pulse.timer_value = 0;
		cal_b_pulse();
	}	
	update_lcd();	
//	send_data_uart();
}	

void update_lcd(void)
{
	switch(lcd_mode)
	{
		case 0x01:
		lcd_goto_XY(8, 0);
		lcd_print_data(a_pulse.width_str, 6);
		lcd_goto_XY(6, 1);
		lcd_print_data(b_pulse.width_str, 6);
		break;

		case 0x02:
		lcd_goto_XY(0, 1);
		if(gps_data.dir_latitude == 'N') lcd_print_data(str_north, 6);
		else lcd_print_data(str_south, 6);	
		lcd_goto_XY(6, 1);
		lcd_print_data(gps_data.latitude, 10);
		break;

		case 0x03:
		lcd_goto_XY(0, 1);
		if(gps_data.dir_longitude == 'E') lcd_print_data(str_east, 6);
		else lcd_print_data(str_west, 6);	
		lcd_goto_XY(6, 1);
		lcd_print_data(gps_data.longitude, 10);
		break;

		case 0x04:
		lcd_goto_XY(6, 1);
		lcd_print_data(gps_data.speed, 6);

		lcd_goto_XY(0,0);	
		if (fuelcut) lcd_print_data(str_fuelcut,16);
		else lcd_print_data(str_blank,16);		
		break;
		
		case 0x05:
		lcd_goto_XY(7,0);
//		lcd_print_data(fuel_data.i_fuel,5);
		lcd_goto_XY(7,1);
//		lcd_print_data(fuel_data.a_fuel,5);
		break;	    								
		case 0x06: break;		
	}
}	

void parse_key(void)
{
	key_flag = 0;	
	BUZZER = 1;
	buzzer_count = 5;
	switch(key_buf)
	{
		case MODE:
		lcd_mode++;
		if(lcd_mode > 5) lcd_mode = 1;
		set_lcd_mode();
		break;
		
		case MOVE: 		//편집 기능을 말함
		lcd_mode =6;
		model++;
		if(model >10) model =1;
		set_model();
		break;

		case INPUT:
		if(pulse_out_time < 243) pulse_out_time +=10;    //b pulse out width increase
		break;

//		case DOWN:
//		if(pulse_out_time > 23) pulse_out_time -= 10;	//b pulse out width decrease	
//		break;

		case UP:
		uart_mode++;
		if(uart_mode > 5) uart_mode = 1;
		if(lcd_mode==6){			
				lcd_goto_XY(13,1);
				lcd_print_data(str_yes,3);
				delay_ms(500);  
				lcd_mode =1;    
				if(model>=10) { average_fuel =0;
						eep_average_fuel = average_fuel;
					      }
				else {
				eep_model = model; 	
				select_model();
				}						      
				set_lcd_mode();				 
				}
		break;
	}				
}	

void dis_init(void)
{
	lcd_clear();
	lcd_home();

	lcd_goto_XY(0, 0);
	lcd_print_data(str_logo, 16);

	lcd_goto_XY(0, 1);		
	lcd_print_data(str_welld, 16);
	
	delay_ms(3000);

	lcd_clear();
	lcd_home();
	
	set_lcd_mode();
}	

void set_led(u08 n) //ON, POSITION
{
	switch(n)
	{
	 case 0: PORTD = 0x00;  break; // base load condition
	 case 1: PORTD = 0x01;  break; 
	 case 2: PORTD = 0x03;  break;
	 case 3: PORTD = 0x07;  break;
	 case 4: PORTD = 0x0F;	break;
	 case 5: PORTD = 0x1F;	break;
	 case 6: PORTD = 0x3F;  break;
	 case 7: PORTD = 0x7F;  break;
	 case 8: PORTD = 0x80;  break; // high speed 	
	 default: PORTD = 0x01; break;	
	}
}
void main(void)
{
u08 i;
	init_sys();
	init_variable();
	lcd_init();	
	dis_init();

	fuelcut =0;
	instant_fuel =0;	
	period_fuel =0;
	average_fuel = eep_average_fuel;//	
	average_fuel = average_fuel/100;	
	model = eep_model;//
	if(model>9) {model =1; eep_model = model;}//
	select_model();
 
//	BUZZER_ON;
	delay_ms(100);
    BUZZER_OFF;           
              
	for(i=0;i<9;i++) {set_led(i);delay_ms(100);}	
	delay_ms(200);
	for(i=0;i<9;i++) {set_led(i);delay_ms(100);}	
	set_led(1);
	
	fuel_rate = 0;
	car_speed = 0;	

	#asm("sei")

	while (1)
	{        
//		if(rx_comp_flag) parse_GPS_data();
		if(time_flag) update_data();
		if(key_flag) parse_key();    		
	};
}


