#ifndef _ATMEGA128_H_
#define _ATMEGA128_H_

#ifdef __AVR_ATmega128__
#define	_AVR_IOM128_H_
#endif


union un_reg{						
	unsigned char ALL;					
	struct {							
		unsigned char BIT0     	:1;		
		unsigned char BIT1     	:1;		
		unsigned char BIT2     	:1;		
		unsigned char BIT3     	:1;		
		unsigned char BIT4     	:1;		
		unsigned char BIT5     	:1;		
		unsigned char BIT6     	:1;		
		unsigned char BIT7     	:1;		
	} BIT;
};


#define	_UCSR1C	(*(volatile union un_reg *)0x9D)
#define	_UDR1	(*(volatile union un_reg *)0x9C)
#define	_UCSR1A	(*(volatile union un_reg *)0x9B)
#define	_UCSR1B	(*(volatile union un_reg *)0x9A)
#define	_UBRR1L	(*(volatile union un_reg *)0x99)
#define	_UBRR1H	(*(volatile union un_reg *)0x98)
#define	_UCSR0C	(*(volatile union un_reg *)0x95)		
#define	_UBRR0H	(*(volatile union un_reg *)0x90)
#define	_TCCR3C	(*(volatile union un_reg *)0x8C)
#define	_TCCR3A	(*(volatile union un_reg *)0x8B)
#define	_TCCR3B	(*(volatile union un_reg *)0x8A)
#define	_TCNT3H	(*(volatile union un_reg *)0x89)
#define	_TCNT3L	(*(volatile union un_reg *)0x88)
#define	_OCR3AH	(*(volatile union un_reg *)0x87)
#define	_OCR3AL	(*(volatile union un_reg *)0x86)
#define	_OCR3BH	(*(volatile union un_reg *)0x85)
#define	_OCR3BL	(*(volatile union un_reg *)0x84)
#define	_OCR3CH	(*(volatile union un_reg *)0x83)
#define	_OCR3CL	(*(volatile union un_reg *)0x82)
#define	_ICR3H	(*(volatile union un_reg *)0x81)
#define	_ICR3L	(*(volatile union un_reg *)0x80)		
#define	_ETIMSK	(*(volatile union un_reg *)0x7D)
#define	_ETIFR	(*(volatile union un_reg *)0x7C)		
#define	_TCCR1C	(*(volatile union un_reg *)0x7A)
#define	_OCR1CH	(*(volatile union un_reg *)0x79)
#define	_OCR1CL	(*(volatile union un_reg *)0x78)
#define	_TWCR	(*(volatile union un_reg *)0x74)
#define	_TWDR	(*(volatile union un_reg *)0x73)
#define	_TWAR	(*(volatile union un_reg *)0x72)
#define	_TWSR	(*(volatile union un_reg *)0x71)
#define	_TWBR	(*(volatile union un_reg *)0x70)
#define	_OSCCAL	(*(volatile union un_reg *)0x6F)		
#define	_XMCRA	(*(volatile union un_reg *)0x6D)
#define	_XMCRB	(*(volatile union un_reg *)0x6C)		
#define	_EICRA	(*(volatile union un_reg *)0x6A)		
#define	_SPMCSR	(*(volatile union un_reg *)0x68)
#define	_PORTG	(*(volatile union un_reg *)0x65)
#define	_DDRG	(*(volatile union un_reg *)0x64)
#define	_PING	(*(volatile union un_reg *)0x63)
#define	_PORTF	(*(volatile union un_reg *)0x62)
#define	_DDRF	(*(volatile union un_reg *)0x61)
#define	_SREG	(*(volatile union un_reg *)0x5F)
#define	_SPH	(*(volatile union un_reg *)0x5E)
#define	_SPL	(*(volatile union un_reg *)0x5D)
#define	_XDIV	(*(volatile union un_reg *)0x5C)
#define	_RAMPZ	(*(volatile union un_reg *)0x5B)
#define	_EICRB	(*(volatile union un_reg *)0x5A)
#define	_EIMSK	(*(volatile union un_reg *)0x59)
#define	_EIFR	(*(volatile union un_reg *)0x58)
#define	_TIMSK	(*(volatile union un_reg *)0x57)
#define	_TIFR	(*(volatile union un_reg *)0x56)
#define	_MCUCR	(*(volatile union un_reg *)0x55)
#define	_MCUCSR	(*(volatile union un_reg *)0x54)
#define	_TCCR0	(*(volatile union un_reg *)0x53)
#define	_TCNT0	(*(volatile union un_reg *)0x52)
#define	_OCR0	(*(volatile union un_reg *)0x51)
#define	_ASSR	(*(volatile union un_reg *)0x50)
#define	_TCCR1A	(*(volatile union un_reg *)0x4F)
#define	_TCCR1B	(*(volatile union un_reg *)0x4E)
#define	_TCNT1H	(*(volatile union un_reg *)0x4D)
#define	_TCNT1L	(*(volatile union un_reg *)0x4C)
#define	_OCR1AH	(*(volatile union un_reg *)0x4B)
#define	_OCR1AL	(*(volatile union un_reg *)0x4A)
#define	_OCR1BH	(*(volatile union un_reg *)0x49)
#define	_OCR1BL	(*(volatile union un_reg *)0x48)
#define	_ICR1H	(*(volatile union un_reg *)0x47)
#define	_ICR1L	(*(volatile union un_reg *)0x46)
#define	_TCCR2	(*(volatile union un_reg *)0x45)
#define	_TCNT2	(*(volatile union un_reg *)0x44)
#define	_OCR2	(*(volatile union un_reg *)0x43)
#define	_OCDR	(*(volatile union un_reg *)0x42)
#define	_WDTCR	(*(volatile union un_reg *)0x41)
#define	_SFIOR	(*(volatile union un_reg *)0x40)
#define	_EEARH	(*(volatile union un_reg *)0x3F)
#define	_EEARL	(*(volatile union un_reg *)0x3E)
#define	_EEDR	(*(volatile union un_reg *)0x3D)
#define	_EECR	(*(volatile union un_reg *)0x3C)
#define	_PORTA	(*(volatile union un_reg *)0x3B)
#define	_DDRA	(*(volatile union un_reg *)0x3A)
#define	_PINA	(*(volatile union un_reg *)0x39)
#define	_PORTB	(*(volatile union un_reg *)0x38)
#define	_DDRB	(*(volatile union un_reg *)0x37)
#define	_PINB	(*(volatile union un_reg *)0x36)
#define	_PORTC	(*(volatile union un_reg *)0x35)
#define	_DDRC	(*(volatile union un_reg *)0x34)
#define	_PINC	(*(volatile union un_reg *)0x33)
#define	_PORTD	(*(volatile union un_reg *)0x32)
#define	_DDRD	(*(volatile union un_reg *)0x31)
#define	_PIND	(*(volatile union un_reg *)0x30)
#define	_SPDR	(*(volatile union un_reg *)0x2F)
#define	_SPSR	(*(volatile union un_reg *)0x2E)
#define	_SPCR	(*(volatile union un_reg *)0x2D)
#define	_UDR0	(*(volatile union un_reg *)0x2C)
#define	_UCSR0A	(*(volatile union un_reg *)0x2B)
#define	_UCSR0B	(*(volatile union un_reg *)0x2A)
#define	_UBRR0L	(*(volatile union un_reg *)0x29)
#define	_ACSR	(*(volatile union un_reg *)0x28)
#define	_ADMUX	(*(volatile union un_reg *)0x27)
#define	_ADCSRA	(*(volatile union un_reg *)0x26)
#define	_ADCH	(*(volatile union un_reg *)0x25)
#define	_ADCL	(*(volatile union un_reg *)0x24)
#define	_PORTE	(*(volatile union un_reg *)0x23)
#define	_DDRE	(*(volatile union un_reg *)0x22)
#define	_PINE	(*(volatile union un_reg *)0x21)
#define	_PINF	(*(volatile union un_reg *)0x20)







#define	UCSR1C	_UCSR1C.ALL	
#define	UMSEL1	_UCSR1C.BIT.BIT6
#define	UPM11	_UCSR1C.BIT.BIT5
#define	UPM10	_UCSR1C.BIT.BIT4
#define	USBS1	_UCSR1C.BIT.BIT3
#define	UCSZ11	_UCSR1C.BIT.BIT2
#define	UCSZ10	_UCSR1C.BIT.BIT1
#define	UCPOL1	_UCSR1C.BIT.BIT0

#define	UDR1	_UDR1.ALL

#define	UCSR1A	_UCSR1A.ALL
#define	RXC1	_UCSR1A.BIT.BIT7
#define	TXC1	_UCSR1A.BIT.BIT6
#define	UDRE1	_UCSR1A.BIT.BIT5
#define	FE1	_UCSR1A.BIT.BIT4
#define	DOR1	_UCSR1A.BIT.BIT3
#define	UPE1	_UCSR1A.BIT.BIT2
#define	U2X1	_UCSR1A.BIT.BIT1
#define	MPCM1	_UCSR1A.BIT.BIT0

#define	UCSR1B	_UCSR1B.ALL
#define	RXCIE1	_UCSR1B.BIT.BIT7
#define	TXCIE1	_UCSR1B.BIT.BIT6
#define	UDRIE1	_UCSR1B.BIT.BIT5
#define	RXEN1	_UCSR1B.BIT.BIT4
#define	TXEN1	_UCSR1B.BIT.BIT3
#define	UCSZ12	_UCSR1B.BIT.BIT2
#define	RXB81	_UCSR1B.BIT.BIT1
#define	TXB81	_UCSR1B.BIT.BIT0

#define	UBRR1L	_UBRR1L.ALL

#define	UBRR1H	_UBRR1H.ALL

#define	UCSR0C	_UCSR0C.ALL
#define	UMSEL0	_UCSR0C.BIT.BIT6
#define	UPM01	_UCSR0C.BIT.BIT5
#define	UPM00	_UCSR0C.BIT.BIT4
#define	USBS0	_UCSR0C.BIT.BIT3
#define	UCSZ01	_UCSR0C.BIT.BIT2
#define	UCSZ00	_UCSR0C.BIT.BIT1
#define	UCPOL0	_UCSR0C.BIT.BIT0

#define	UBRR0H	_UBRR0H.ALL

#define	TCCR3C	_TCCR3C.ALL
#define	FOC3A	_TCCR3C.BIT.BIT7
#define	FOC3B	_TCCR3C.BIT.BIT6
#define	FOC3C	_TCCR3C.BIT.BIT5

#define	TCCR3A	_TCCR3A.ALL
#define	COM3A1	_TCCR3A.BIT.BIT7
#define	COM3A0	_TCCR3A.BIT.BIT6
#define	COM3B1	_TCCR3A.BIT.BIT5
#define	COM3B0	_TCCR3A.BIT.BIT4
#define	COM3C1	_TCCR3A.BIT.BIT3
#define	COM3C0	_TCCR3A.BIT.BIT2
#define	WGM31	_TCCR3A.BIT.BIT1
#define	WGM30	_TCCR3A.BIT.BIT0

#define	TCCR3B	_TCCR3B.ALL
#define	ICNC3	_TCCR3B.BIT.BIT7
#define	ICES3	_TCCR3B.BIT.BIT6
#define	WGM33	_TCCR3B.BIT.BIT4
#define	WGM32	_TCCR3B.BIT.BIT3
#define	CS32	_TCCR3B.BIT.BIT2
#define	CS31	_TCCR3B.BIT.BIT1
#define	CS30	_TCCR3B.BIT.BIT0

#define	TCNT3H	_TCNT3H.ALL

#define	TCNT3L	_TCNT3L.ALL

#define	OCR3AH	_OCR3AH.ALL

#define	OCR3AL	_OCR3AL.ALL

#define	OCR3BH	_OCR3BH.ALL

#define	OCR3BL	_OCR3BL.ALL

#define	OCR3CH	_OCR3CH.ALL

#define	OCR3CL	_OCR3CL.ALL

#define	ICR3H	_ICR3H.ALL

#define	ICR3L	_ICR3L.ALL

#define	ETIMSK	_ETIMSK.ALL
#define	TICIE3	_ETIMSK.BIT.BIT5
#define	OCIE3A	_ETIMSK.BIT.BIT4
#define	OCIE3B	_ETIMSK.BIT.BIT3
#define	TOIE3	_ETIMSK.BIT.BIT2
#define	OCIE3C	_ETIMSK.BIT.BIT1
#define	OCIE1C	_ETIMSK.BIT.BIT0

#define	ETIFR	_ETIFR.ALL	
#define	ICF3	_ETIFR.BIT.BIT5
#define	OCF3A	_ETIFR.BIT.BIT4
#define	OCF3B	_ETIFR.BIT.BIT3
#define	TOV3	_ETIFR.BIT.BIT2
#define	OCF3C	_ETIFR.BIT.BIT1
#define	OCF1C	_ETIFR.BIT.BIT0

#define	TCCR1C	_TCCR1C.ALL
#define	FOC1A	_TCCR1C.BIT.BIT7
#define	FOC1B	_TCCR1C.BIT.BIT6
#define	FOC1C	_TCCR1C.BIT.BIT5

#define	OCR1CH	_OCR1CH.ALL

#define	OCR1CL	_OCR1CL.ALL

#define	TWCR	_TWCR.ALL
#define	TWINT	_TWCR.BIT.BIT7
#define	TWEA	_TWCR.BIT.BIT6
#define	TWSTA	_TWCR.BIT.BIT5
#define	TWSTO	_TWCR.BIT.BIT4
#define	TWWC	_TWCR.BIT.BIT3
#define	TWEN	_TWCR.BIT.BIT2
#define	TWIE	_TWCR.BIT.BIT0

#define	TWDR	_TWDR.ALL

#define	TWAR	_TWAR.ALL
#define	TWA6	_TWAR.BIT.BIT7
#define	TWA5	_TWAR.BIT.BIT6
#define	TWA4	_TWAR.BIT.BIT5
#define	TWA3	_TWAR.BIT.BIT4
#define	TWA2	_TWAR.BIT.BIT3
#define	TWA1	_TWAR.BIT.BIT2
#define	TWA0	_TWAR.BIT.BIT1
#define	TWGCE	_TWAR.BIT.BIT0

#define	TWSR	_TWSR.ALL
#define	TWS7	_TWSR.BIT.BIT7
#define	TWS6	_TWSR.BIT.BIT6
#define	TWS5	_TWSR.BIT.BIT5
#define	TWS4	_TWSR.BIT.BIT4
#define	TWS3	_TWSR.BIT.BIT3
#define	TWPS1	_TWSR.BIT.BIT1
#define	TWPS0	_TWSR.BIT.BIT0

#define	TWBR	_TWBR.ALL

#define	OSCCAL	_OSCCAL.ALL

#define	XMCRA	_XMCRA.ALL
#define	SRL2	_XMCRA.BIT.BIT6
#define	SRL1	_XMCRA.BIT.BIT5
#define	SRL0	_XMCRA.BIT.BIT4
#define	SRW01	_XMCRA.BIT.BIT3
#define	SRW00	_XMCRA.BIT.BIT2
#define	SRW11	_XMCRA.BIT.BIT1


#define	XMCRB	_XMCRB.ALL
#define	XMBK	_XMCRB.BIT.BIT7
#define	XMM2	_XMCRB.BIT.BIT2
#define	XMM1	_XMCRB.BIT.BIT1
#define	XMM0	_XMCRB.BIT.BIT0

#define	EICRA	_EICRA.ALL
#define	ISC31	_EICRA.BIT.BIT7
#define	ISC30	_EICRA.BIT.BIT6
#define	ISC21	_EICRA.BIT.BIT5
#define	ISC20	_EICRA.BIT.BIT4
#define	ISC11	_EICRA.BIT.BIT3
#define	ISC10	_EICRA.BIT.BIT2
#define	ISC01	_EICRA.BIT.BIT1
#define	ISC00	_EICRA.BIT.BIT0

#define	SPMCSR	_SPMCSR.ALL
#define	SPMIE	_SPMCSR.BIT.BIT7
#define	RWWSB	_SPMCSR.BIT.BIT6
#define	RWWSRE	_SPMCSR.BIT.BIT4
#define	BLBSET	_SPMCSR.BIT.BIT3
#define	PGWRT	_SPMCSR.BIT.BIT2
#define	PGERS	_SPMCSR.BIT.BIT1
#define	SPMEN	_SPMCSR.BIT.BIT0

#define	PORTG	_PORTG.ALL
#define	PORTG4	_PORTG.BIT.BIT4
#define	PORTG3	_PORTG.BIT.BIT3
#define	PORTG2	_PORTG.BIT.BIT2
#define	PORTG1	_PORTG.BIT.BIT1
#define	PORTG0	_PORTG.BIT.BIT0

#define	DDRG	_DDRG.ALL
#define	DDG4	_DDRG.BIT.BIT4
#define	DDG3	_DDRG.BIT.BIT3
#define	DDG2	_DDRG.BIT.BIT2
#define	DDG1	_DDRG.BIT.BIT1
#define	DDG0	_DDRG.BIT.BIT0

#define	PING	_PING.ALL
#define	PING4	_PING.BIT.BIT4
#define	PING3	_PING.BIT.BIT3
#define	PING2	_PING.BIT.BIT2
#define	PING1	_PING.BIT.BIT1
#define	PING0	_PING.BIT.BIT0

#define	PORTF	_PORTF.ALL
#define	PORTF7	_PORTF.BIT.BIT7
#define	PORTF6	_PORTF.BIT.BIT6
#define	PORTF5	_PORTF.BIT.BIT5
#define	PORTF4	_PORTF.BIT.BIT4
#define	PORTF3	_PORTF.BIT.BIT3
#define	PORTF2	_PORTF.BIT.BIT2
#define	PORTF1	_PORTF.BIT.BIT1
#define	PORTF0	_PORTF.BIT.BIT0

#define	DDRF	_DDRF.ALL
#define	DDF7	_DDRF.BIT.BIT7
#define	DDF6	_DDRF.BIT.BIT6
#define	DDF5	_DDRF.BIT.BIT5
#define	DDF4	_DDRF.BIT.BIT4
#define	DDF3	_DDRF.BIT.BIT3
#define	DDF2	_DDRF.BIT.BIT2
#define	DDF1	_DDRF.BIT.BIT1
#define	DDF0	_DDRF.BIT.BIT0

#define	SREG	_SREG.ALL
#define	I	_SREG.BIT.BIT7
#define	T	_SREG.BIT.BIT6
#define	H	_SREG.BIT.BIT5
#define	S	_SREG.BIT.BIT4
#define	V	_SREG.BIT.BIT3
#define	N	_SREG.BIT.BIT2
#define	Z	_SREG.BIT.BIT1
#define	C	_SREG.BIT.BIT0

#define	SPH	_SPH.ALL
#define	SP15	_SPH.BIT.BIT7
#define	SP14	_SPH.BIT.BIT6
#define	SP13	_SPH.BIT.BIT5
#define	SP12	_SPH.BIT.BIT4
#define	SP11	_SPH.BIT.BIT3
#define	SP10	_SPH.BIT.BIT2
#define	SP9	_SPH.BIT.BIT1
#define	SP8	_SPH.BIT.BIT0

#define	SPL	_SPL.ALL
#define	SP7	_SPL.BIT.BIT7
#define	SP6	_SPL.BIT.BIT6
#define	SP5	_SPL.BIT.BIT5
#define	SP4	_SPL.BIT.BIT4
#define	SP3	_SPL.BIT.BIT3
#define	SP2	_SPL.BIT.BIT2
#define	SP1	_SPL.BIT.BIT1
#define	SP0	_SPL.BIT.BIT0

#define	XDIV	_XDIV.ALL
#define	XDIVEN	_XDIV.BIT.BIT7
#define	XDIV6	_XDIV.BIT.BIT6
#define	XDIV5	_XDIV.BIT.BIT5
#define	XDIV4	_XDIV.BIT.BIT4
#define	XDIV3	_XDIV.BIT.BIT3
#define	XDIV2	_XDIV.BIT.BIT2
#define	XDIV1	_XDIV.BIT.BIT1
#define	XDIV0	_XDIV.BIT.BIT0

#define	RAMPZ	_RAMPZ.ALL
#define	RAMPZ0	_RAMPZ.BIT.BIT0

#define	EICRB	_EICRB.ALL
#define	ISC71	_EICRB.BIT.BIT7
#define	ISC70	_EICRB.BIT.BIT6
#define	ISC61	_EICRB.BIT.BIT5
#define	ISC60	_EICRB.BIT.BIT4
#define	ISC51	_EICRB.BIT.BIT3
#define	ISC50	_EICRB.BIT.BIT2
#define	ISC41	_EICRB.BIT.BIT1
#define	ISC40	_EICRB.BIT.BIT0

#define	EIMSK	_EIMSK.ALL
#define	INT7	_EIMSK.BIT.BIT7
#define	INT6	_EIMSK.BIT.BIT6
#define	INT5	_EIMSK.BIT.BIT5
#define	INT4	_EIMSK.BIT.BIT4
#define	INT3	_EIMSK.BIT.BIT3
#define	INT2	_EIMSK.BIT.BIT2
#define	INT1	_EIMSK.BIT.BIT1
#define	INT0	_EIMSK.BIT.BIT0

#define	EIFR	_EIFR.ALL
#define	INTF7	_EIFR.BIT.BIT7
#define	INTF6	_EIFR.BIT.BIT6
#define	INTF5	_EIFR.BIT.BIT5
#define	INTF4	_EIFR.BIT.BIT4
#define	INTF3	_EIFR.BIT.BIT3
#define	INTF	_EIFR.BIT.BIT2
#define	INTF1	_EIFR.BIT.BIT1
#define	INTF0	_EIFR.BIT.BIT0

#define	TIMSK	_TIMSK.ALL
#define	OCIE2	_TIMSK.BIT.BIT7
#define	TOIE2	_TIMSK.BIT.BIT6
#define	TICIE1	_TIMSK.BIT.BIT5
#define	OCIE1A	_TIMSK.BIT.BIT4
#define	OCIE1B	_TIMSK.BIT.BIT3
#define	TOIE1	_TIMSK.BIT.BIT2
#define	OCIE0	_TIMSK.BIT.BIT1
#define	TOIE0	_TIMSK.BIT.BIT0

#define	TIFR	_TIFR.ALL
#define	OCF2	_TIFR.BIT.BIT7
#define	TOV2	_TIFR.BIT.BIT6
#define	ICF1	_TIFR.BIT.BIT5
#define	OCF1A	_TIFR.BIT.BIT4
#define	OCF1B	_TIFR.BIT.BIT3
#define	TOV1	_TIFR.BIT.BIT2
#define	OCF0	_TIFR.BIT.BIT1
#define	TOV0	_TIFR.BIT.BIT0

#define	MCUCR	_MCUCR.ALL
#define	SRE	_MCUCR.BIT.BIT7
#define	SRW10	_MCUCR.BIT.BIT6
#define	SE	_MCUCR.BIT.BIT5
#define	SM1	_MCUCR.BIT.BIT4
#define	SM0	_MCUCR.BIT.BIT3
#define	SM2	_MCUCR.BIT.BIT2
#define	IVSEL	_MCUCR.BIT.BIT1
#define	IVCE	_MCUCR.BIT.BIT0

#define	MCUCSR	_MCUCSR.ALL
#define	JTD	_MCUCSR.BIT.BIT7
#define	JTRF	_MCUCSR.BIT.BIT4
#define	WDRF	_MCUCSR.BIT.BIT3
#define	BORF	_MCUCSR.BIT.BIT2
#define	EXTRF	_MCUCSR.BIT.BIT1
#define	PORF	_MCUCSR.BIT.BIT0

#define	TCCR0	_TCCR0.ALL
#define	FOC0	_TCCR0.BIT.BIT7
#define	WGM00	_TCCR0.BIT.BIT6
#define	COM01	_TCCR0.BIT.BIT5
#define	COM00	_TCCR0.BIT.BIT4
#define	WGM01	_TCCR0.BIT.BIT3
#define	CS02	_TCCR0.BIT.BIT2
#define	CS01	_TCCR0.BIT.BIT1
#define	CS00	_TCCR0.BIT.BIT0

#define	TCNT0	_TCNT0.ALL

#define	OCR0	_OCR0.ALL

#define	ASSR	_ASSR.ALL
#define	AS0	_ASSR.BIT.BIT3
#define	TCN0UB	_ASSR.BIT.BIT2
#define	OCR0UB	_ASSR.BIT.BIT1
#define	TCR0UB	_ASSR.BIT.BIT0

#define	TCCR1A	_TCCR1A.ALL
#define	COM1A1	_TCCR1A.BIT.BIT7
#define	COM1A0	_TCCR1A.BIT.BIT6
#define	COM1B1	_TCCR1A.BIT.BIT5
#define	COM1B0	_TCCR1A.BIT.BIT4
#define	COM1C1	_TCCR1A.BIT.BIT3
#define	COM1C0	_TCCR1A.BIT.BIT2
#define	WGM11	_TCCR1A.BIT.BIT1
#define	WGM10	_TCCR1A.BIT.BIT0

#define	TCCR1B	_TCCR1B.ALL
#define	ICNC1	_TCCR1B.BIT.BIT7
#define	ICES1	_TCCR1B.BIT.BIT6
#define	WGM13	_TCCR1B.BIT.BIT4
#define	WGM12	_TCCR1B.BIT.BIT3
#define	CS12	_TCCR1B.BIT.BIT2
#define	CS11	_TCCR1B.BIT.BIT1
#define	CS10	_TCCR1B.BIT.BIT0

#define	TCNT1H	_TCNT1H.ALL

#define	TCNT1L	_TCNT1L.ALL

#define	OCR1AH	_OCR1AH.ALL

#define	OCR1AL	_OCR1AL.ALL

#define	OCR1BH	_OCR1BH.ALL

#define	OCR1BL	_OCR1BL.ALL

#define	ICR1H	_ICR1H.ALL

#define	ICR1L	_ICR1L.ALL

#define	TCCR2	_TCCR2.ALL
#define	FOC2	_TCCR2.BIT.BIT7
#define	WGM20	_TCCR2.BIT.BIT6
#define	COM21	_TCCR2.BIT.BIT5
#define	COM20	_TCCR2.BIT.BIT4
#define	WGM21	_TCCR2.BIT.BIT3
#define	CS22	_TCCR2.BIT.BIT2
#define	CS21	_TCCR2.BIT.BIT1
#define	CS20	_TCCR2.BIT.BIT0

#define	TCNT2	_TCNT2.ALL

#define	OCR2	_OCR2.ALL

#define	OCDR	_OCDR.ALL
#define	OCDR7	_OCDR.BIT.BIT7
#define	OCDR6	_OCDR.BIT.BIT6
#define	OCDR5	_OCDR.BIT.BIT5
#define	OCDR4	_OCDR.BIT.BIT4
#define	OCDR3	_OCDR.BIT.BIT3
#define	OCDR2	_OCDR.BIT.BIT2
#define	OCDR1	_OCDR.BIT.BIT1
#define	OCDR0	_OCDR.BIT.BIT0

#define	WDTCR	_WDTCR.ALL
#define	WDCE	_WDTCR.BIT.BIT4
#define	WDE	_WDTCR.BIT.BIT3
#define	WDP2	_WDTCR.BIT.BIT2
#define	WDP1	_WDTCR.BIT.BIT1
#define	WDP0	_WDTCR.BIT.BIT0

#define	SFIOR	_SFIOR.ALL
#define	TSM	_SFIOR.BIT.BIT7
#define	ADHSM	_SFIOR.BIT.BIT4
#define	ACME	_SFIOR.BIT.BIT3
#define	PUD	_SFIOR.BIT.BIT2
#define	PSR0	_SFIOR.BIT.BIT1
#define	PSR321	_SFIOR.BIT.BIT0

#define	EEARH	_EEARH.ALL

#define	EEARL	_EEARL.ALL

#define	EEDR	_EEDR.ALL

#define	EECR	_EECR.ALL
#define	EERIE	_EECR.BIT.BIT3
#define	EEMWE	_EECR.BIT.BIT2
#define	EEWE	_EECR.BIT.BIT1
#define	EERE	_EECR.BIT.BIT0

#define	PORTA	_PORTA.ALL
#define	PORTA7	_PORTA.BIT.BIT7
#define	PORTA6	_PORTA.BIT.BIT6
#define	PORTA5	_PORTA.BIT.BIT5
#define	PORTA4	_PORTA.BIT.BIT4
#define	PORTA3	_PORTA.BIT.BIT3
#define	PORTA2	_PORTA.BIT.BIT2
#define	PORTA1	_PORTA.BIT.BIT1
#define	PORTA0	_PORTA.BIT.BIT0

#define	DDRA	_DDRA.ALL
#define	DDA7	_DDRA.BIT.BIT7
#define	DDA6	_DDRA.BIT.BIT6
#define	DDA5	_DDRA.BIT.BIT5
#define	DDA4	_DDRA.BIT.BIT4
#define	DDA3	_DDRA.BIT.BIT3
#define	DDA2	_DDRA.BIT.BIT2
#define	DDA1	_DDRA.BIT.BIT1
#define	DDA0	_DDRA.BIT.BIT0

#define	PINA	_PINA.ALL
#define	PINA7	_PINA.BIT.BIT7
#define	PINA6	_PINA.BIT.BIT6
#define	PINA5	_PINA.BIT.BIT5
#define	PINA4	_PINA.BIT.BIT4
#define	PINA3	_PINA.BIT.BIT3
#define	PINA2	_PINA.BIT.BIT2
#define	PINA1	_PINA.BIT.BIT1
#define	PINA0	_PINA.BIT.BIT0

#define	PORTB	_PORTB.ALL
#define	PORTB7	_PORTB.BIT.BIT7
#define	PORTB6	_PORTB.BIT.BIT6
#define	PORTB5	_PORTB.BIT.BIT5
#define	PORTB4	_PORTB.BIT.BIT4
#define	PORTB3	_PORTB.BIT.BIT3
#define	PORTB2	_PORTB.BIT.BIT2
#define	PORTB1	_PORTB.BIT.BIT1
#define	PORTB0	_PORTB.BIT.BIT0

#define	DDRB	_DDRB.ALL
#define	DDB7	_DDRB.BIT.BIT7
#define	DDB6	_DDRB.BIT.BIT6
#define	DDB5	_DDRB.BIT.BIT5
#define	DDB4	_DDRB.BIT.BIT4
#define	DDB3	_DDRB.BIT.BIT3
#define	DDB2	_DDRB.BIT.BIT2
#define	DDB1	_DDRB.BIT.BIT1
#define	DDB0	_DDRB.BIT.BIT0

#define	PINB	_PINB.ALL
#define	PINB7	_PINB.BIT.BIT7
#define	PINB6	_PINB.BIT.BIT6
#define	PINB5	_PINB.BIT.BIT5
#define	PINB4	_PINB.BIT.BIT4
#define	PINB3	_PINB.BIT.BIT3
#define	PINB2	_PINB.BIT.BIT2
#define	PINB1	_PINB.BIT.BIT1
#define	PINB0	_PINB.BIT.BIT0

#define	PORTC	_PORTC.ALL
#define	PORTC7	_PORTC.BIT.BIT7
#define	PORTC6	_PORTC.BIT.BIT6
#define	PORTC5	_PORTC.BIT.BIT5
#define	PORTC4	_PORTC.BIT.BIT4
#define	PORTC3	_PORTC.BIT.BIT3
#define	PORTC2	_PORTC.BIT.BIT2
#define	PORTC1	_PORTC.BIT.BIT1
#define	PORTC0	_PORTC.BIT.BIT0

#define	DDRC	_DDRC.ALL
#define	DDC7	_DDRC.BIT.BIT7
#define	DDC6	_DDRC.BIT.BIT6
#define	DDC5	_DDRC.BIT.BIT5
#define	DDC4	_DDRC.BIT.BIT4
#define	DDC3	_DDRC.BIT.BIT3
#define	DDC2	_DDRC.BIT.BIT2
#define	DDC1	_DDRC.BIT.BIT1
#define	DDC0	_DDRC.BIT.BIT0

#define	PINC	_PINC.ALL
#define	PINC7	_PINC.BIT.BIT7
#define	PINC6	_PINC.BIT.BIT6
#define	PINC5	_PINC.BIT.BIT5
#define	PINC4	_PINC.BIT.BIT4
#define	PINC3	_PINC.BIT.BIT3
#define	PINC2	_PINC.BIT.BIT2
#define	PINC1	_PINC.BIT.BIT1
#define	PINC0	_PINC.BIT.BIT0

#define	PORTD	_PORTD.ALL
#define	PORTD7	_PORTD.BIT.BIT7
#define	PORTD6	_PORTD.BIT.BIT6
#define	PORTD5	_PORTD.BIT.BIT5
#define	PORTD4	_PORTD.BIT.BIT4
#define	PORTD3	_PORTD.BIT.BIT3
#define	PORTD2	_PORTD.BIT.BIT2
#define	PORTD1	_PORTD.BIT.BIT1
#define	PORTD0	_PORTD.BIT.BIT0

#define	DDRD	_DDRD.ALL
#define	DDD7	_DDRD.BIT.BIT7
#define	DDD6	_DDRD.BIT.BIT6
#define	DDD5	_DDRD.BIT.BIT5
#define	DDD4	_DDRD.BIT.BIT4
#define	DDD3	_DDRD.BIT.BIT3
#define	DDD2	_DDRD.BIT.BIT2
#define	DDD1	_DDRD.BIT.BIT1
#define	DDD0	_DDRD.BIT.BIT0

#define	PIND	_PIND.ALL
#define	PIND7	_PIND.BIT.BIT7
#define	PIND6	_PIND.BIT.BIT6
#define	PIND5	_PIND.BIT.BIT5
#define	PIND4	_PIND.BIT.BIT4
#define	PIND3	_PIND.BIT.BIT3
#define	PIND2	_PIND.BIT.BIT2
#define	PIND1	_PIND.BIT.BIT1
#define	PIND0	_PIND.BIT.BIT0

#define	SPDR	_SPDR.ALL

#define	SPSR	_SPSR.ALL
#define	SPIF	_SPSR.BIT.BIT7
#define	WCOL	_SPSR.BIT.BIT6
#define	SPI2X	_SPSR.BIT.BIT0

#define	SPCR	_SPCR.ALL
#define	SPIE	_SPCR.BIT.BIT7
#define	SPE		_SPCR.BIT.BIT6
#define	DORD	_SPCR.BIT.BIT5
#define	MSTR	_SPCR.BIT.BIT4
#define	CPOL	_SPCR.BIT.BIT3
#define	CPHA	_SPCR.BIT.BIT2
#define	SPR1	_SPCR.BIT.BIT1
#define	SPR0	_SPCR.BIT.BIT0

#define	UDR0	_UDR0.ALL

#define	UCSR0A	_UCSR0A.ALL
#define	RXC0	_UCSR0A.BIT.BIT7
#define	TXC0	_UCSR0A.BIT.BIT6
#define	UDRE0	_UCSR0A.BIT.BIT5
#define	FE0		_UCSR0A.BIT.BIT4
#define	DOR0	_UCSR0A.BIT.BIT3
#define	UPE0	_UCSR0A.BIT.BIT2
#define	U2X0	_UCSR0A.BIT.BIT1
#define	MPCM0	_UCSR0A.BIT.BIT0

#define	UCSR0B	_UCSR0B.ALL
#define	RXCIE0	_UCSR0B.BIT.BIT7
#define	TXCIE0	_UCSR0B.BIT.BIT6
#define	UDRIE0	_UCSR0B.BIT.BIT5
#define	RXEN0	_UCSR0B.BIT.BIT4
#define	TXEN0	_UCSR0B.BIT.BIT3
#define	UCSZ02	_UCSR0B.BIT.BIT2
#define	RXB80	_UCSR0B.BIT.BIT1
#define	TXB80	_UCSR0B.BIT.BIT0

#define	UBRR0L	_UBRR0L.ALL

#define	ACSR	_ACSR.ALL
#define	ACD	_ACSR.BIT.BIT7
#define	ACBG	_ACSR.BIT.BIT6
#define	ACO	_ACSR.BIT.BIT5
#define	ACI	_ACSR.BIT.BIT4
#define	ACIE	_ACSR.BIT.BIT3
#define	ACIC	_ACSR.BIT.BIT2
#define	ACIS1	_ACSR.BIT.BIT1
#define	ACIS0	_ACSR.BIT.BIT0

#define	ADMUX	_ADMUX.ALL
#define	REFS1	_ADMUX.BIT.BIT7
#define	REFS0	_ADMUX.BIT.BIT6
#define	ADLAR	_ADMUX.BIT.BIT5
#define	MUX4	_ADMUX.BIT.BIT4
#define	MUX3	_ADMUX.BIT.BIT3
#define	MUX2	_ADMUX.BIT.BIT2
#define	MUX1	_ADMUX.BIT.BIT1
#define	MUX0	_ADMUX.BIT.BIT0

#define	ADCSRA	_ADCSRA.ALL
#define	ADEN	_ADCSRA.BIT.BIT7
#define	ADSC	_ADCSRA.BIT.BIT6
#define	ADFR	_ADCSRA.BIT.BIT5
#define	ADIF	_ADCSRA.BIT.BIT4
#define	ADIE	_ADCSRA.BIT.BIT3
#define	ADPS2	_ADCSRA.BIT.BIT2
#define	ADPS1	_ADCSRA.BIT.BIT1
#define	ADPS0	_ADCSRA.BIT.BIT0

#define	ADCH	_ADCH.ALL

#define	ADCL	_ADCL.ALL

#define	PORTE	_PORTE.ALL
#define	PORTE7	_PORTE.BIT.BIT7
#define	PORTE6	_PORTE.BIT.BIT6
#define	PORTE5	_PORTE.BIT.BIT5
#define	PORTE4	_PORTE.BIT.BIT4
#define	PORTE3	_PORTE.BIT.BIT3
#define	PORTE2	_PORTE.BIT.BIT2
#define	PORTE1	_PORTE.BIT.BIT1
#define	PORTE0	_PORTE.BIT.BIT0

#define	DDRE	_DDRE.ALL
#define	DDE7	_DDRE.BIT.BIT7
#define	DDE6	_DDRE.BIT.BIT6
#define	DDE5	_DDRE.BIT.BIT5
#define	DDE4	_DDRE.BIT.BIT4
#define	DDE3	_DDRE.BIT.BIT3
#define	DDE2	_DDRE.BIT.BIT2
#define	DDE1	_DDRE.BIT.BIT1
#define	DDE0	_DDRE.BIT.BIT0

#define	PINE	_PINE.ALL
#define	PINE7	_PINE.BIT.BIT7
#define	PINE6	_PINE.BIT.BIT6
#define	PINE5	_PINE.BIT.BIT5
#define	PINE4	_PINE.BIT.BIT4
#define	PINE3	_PINE.BIT.BIT3
#define	PINE2	_PINE.BIT.BIT2
#define	PINE1	_PINE.BIT.BIT1
#define	PINE0	_PINE.BIT.BIT0

#define	PINF	_PINF.ALL
#define	PINF7	_PINF.BIT.BIT7
#define	PINF6	_PINF.BIT.BIT6
#define	PINF5	_PINF.BIT.BIT5
#define	PINF4	_PINF.BIT.BIT4
#define	PINF3	_PINF.BIT.BIT3
#define	PINF2	_PINF.BIT.BIT2
#define	PINF1	_PINF.BIT.BIT1
#define	PINF0	_PINF.BIT.BIT0


/* Interrupt vectors */

/* External Interrupt Request 0 */
#define INT0_vect			_VECTOR(1)
#define SIG_INTERRUPT0			_VECTOR(1)

/* External Interrupt Request 1 */
#define INT1_vect			_VECTOR(2)
#define SIG_INTERRUPT1			_VECTOR(2)

/* External Interrupt Request 2 */
#define INT2_vect			_VECTOR(3)
#define SIG_INTERRUPT2			_VECTOR(3)

/* External Interrupt Request 3 */
#define INT3_vect			_VECTOR(4)
#define SIG_INTERRUPT3			_VECTOR(4)

/* External Interrupt Request 4 */
#define INT4_vect			_VECTOR(5)
#define SIG_INTERRUPT4			_VECTOR(5)

/* External Interrupt Request 5 */
#define INT5_vect			_VECTOR(6)
#define SIG_INTERRUPT5			_VECTOR(6)

/* External Interrupt Request 6 */
#define INT6_vect			_VECTOR(7)
#define SIG_INTERRUPT6			_VECTOR(7)

/* External Interrupt Request 7 */
#define INT7_vect			_VECTOR(8)
#define SIG_INTERRUPT7			_VECTOR(8)

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect		_VECTOR(9)
#define SIG_OUTPUT_COMPARE2		_VECTOR(9)

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect			_VECTOR(10)
#define SIG_OVERFLOW2			_VECTOR(10)

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect		_VECTOR(11)
#define SIG_INPUT_CAPTURE1		_VECTOR(11)

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect		_VECTOR(12)
#define SIG_OUTPUT_COMPARE1A		_VECTOR(12)

/* Timer/Counter Compare Match B */
#define TIMER1_COMPB_vect		_VECTOR(13)
#define SIG_OUTPUT_COMPARE1B		_VECTOR(13)

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			_VECTOR(14)
#define SIG_OVERFLOW1			_VECTOR(14)

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect		_VECTOR(15)
#define SIG_OUTPUT_COMPARE0		_VECTOR(15)

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			_VECTOR(16)
#define SIG_OVERFLOW0			_VECTOR(16)

/* SPI Serial Transfer Complete */
#define SPI_STC_vect			_VECTOR(17)
#define SIG_SPI				_VECTOR(17)

/* USART0, Rx Complete */
#define USART0_RX_vect			_VECTOR(18)
#define SIG_USART0_RECV			_VECTOR(18)
#define SIG_UART0_RECV			_VECTOR(18)

/* USART0 Data Register Empty */
#define USART0_UDRE_vect		_VECTOR(19)
#define SIG_USART0_DATA			_VECTOR(19)
#define SIG_UART0_DATA			_VECTOR(19)

/* USART0, Tx Complete */
#define USART0_TX_vect			_VECTOR(20)
#define SIG_USART0_TRANS		_VECTOR(20)
#define SIG_UART0_TRANS			_VECTOR(20)

/* ADC Conversion Complete */
#define ADC_vect			_VECTOR(21)
#define SIG_ADC				_VECTOR(21)

/* EEPROM Ready */
#define EE_READY_vect			_VECTOR(22)
#define SIG_EEPROM_READY		_VECTOR(22)

/* Analog Comparator */
#define ANALOG_COMP_vect		_VECTOR(23)
#define SIG_COMPARATOR			_VECTOR(23)

/* Timer/Counter1 Compare Match C */
#define TIMER1_COMPC_vect		_VECTOR(24)
#define SIG_OUTPUT_COMPARE1C		_VECTOR(24)

/* Timer/Counter3 Capture Event */
#define TIMER3_CAPT_vect		_VECTOR(25)
#define SIG_INPUT_CAPTURE3		_VECTOR(25)

/* Timer/Counter3 Compare Match A */
#define TIMER3_COMPA_vect		_VECTOR(26)
#define SIG_OUTPUT_COMPARE3A		_VECTOR(26)

/* Timer/Counter3 Compare Match B */
#define TIMER3_COMPB_vect		_VECTOR(27)
#define SIG_OUTPUT_COMPARE3B		_VECTOR(27)

/* Timer/Counter3 Compare Match C */
#define TIMER3_COMPC_vect		_VECTOR(28)
#define SIG_OUTPUT_COMPARE3C		_VECTOR(28)

/* Timer/Counter3 Overflow */
#define TIMER3_OVF_vect			_VECTOR(29)
#define SIG_OVERFLOW3			_VECTOR(29)

/* USART1, Rx Complete */
#define USART1_RX_vect			_VECTOR(30)
#define SIG_USART1_RECV			_VECTOR(30)
#define SIG_UART1_RECV			_VECTOR(30)

/* USART1, Data Register Empty */
#define USART1_UDRE_vect		_VECTOR(31)
#define SIG_USART1_DATA			_VECTOR(31)
#define SIG_UART1_DATA			_VECTOR(31)

/* USART1, Tx Complete */
#define USART1_TX_vect			_VECTOR(32)
#define SIG_USART1_TRANS		_VECTOR(32)
#define SIG_UART1_TRANS			_VECTOR(32)

/* 2-wire Serial Interface */
#define TWI_vect			_VECTOR(33)
#define SIG_2WIRE_SERIAL		_VECTOR(33)

/* Store Program Memory Read */
#define SPM_READY_vect			_VECTOR(34)
#define SIG_SPM_READY			_VECTOR(34)

#define _VECTORS_SIZE 140



#endif
