#ifndef _AT90CAN128_H_
#define _AT90CAN128_H_

#ifdef __AVR_AT90CAN128__
#define	_AVR_IOCANXX_H_
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


#define	_CANMSG		(*(volatile union un_reg *)0xFA)
#define	_CANSTMH	(*(volatile union un_reg *)0xF9)
#define	_CANSTML	(*(volatile union un_reg *)0xF8)
#define	_CANIDM1	(*(volatile union un_reg *)0xF7)
#define	_CANIDM2	(*(volatile union un_reg *)0xF6)
#define	_CANIDM3	(*(volatile union un_reg *)0xF5)
#define	_CANIDM4	(*(volatile union un_reg *)0xF4)
#define	_CANIDT1	(*(volatile union un_reg *)0xF3)
#define	_CANIDT2	(*(volatile union un_reg *)0xF2)
#define	_CANIDT3	(*(volatile union un_reg *)0xF1)
#define	_CANIDT4	(*(volatile union un_reg *)0xF0)
#define	_CANCDMOB	(*(volatile union un_reg *)0xEF)
#define	_CANSTMOB	(*(volatile union un_reg *)0xEE)
#define	_CANPAGE	(*(volatile union un_reg *)0xED)
#define	_CANHPMOB	(*(volatile union un_reg *)0xEC)
#define	_CANREC		(*(volatile union un_reg *)0xEB)
#define	_CANTEC		(*(volatile union un_reg *)0xEA)
#define	_CANTTCH	(*(volatile union un_reg *)0xE9)
#define	_CANTTCL	(*(volatile union un_reg *)0xE8)
#define	_CANTIMH	(*(volatile union un_reg *)0xE7)
#define	_CANTIML	(*(volatile union un_reg *)0xE6)
#define	_CANTCON	(*(volatile union un_reg *)0xE5)
#define	_CANBT3		(*(volatile union un_reg *)0xE4)
#define	_CANBT2		(*(volatile union un_reg *)0xE3)
#define	_CANBT1		(*(volatile union un_reg *)0xE2)
#define	_CANSIT1	(*(volatile union un_reg *)0xE1)
#define	_CANSIT2	(*(volatile union un_reg *)0xE0)
#define	_CANIE1		(*(volatile union un_reg *)0xDF)
#define	_CANIE2		(*(volatile union un_reg *)0xDE)
#define	_CANEN1		(*(volatile union un_reg *)0xDD)
#define	_CANEN2		(*(volatile union un_reg *)0xDC)
#define	_CANGIE		(*(volatile union un_reg *)0xDB)
#define	_CANGIT		(*(volatile union un_reg *)0xDA)
#define	_CANGSTA	(*(volatile union un_reg *)0xD9)
#define	_CANGCON	(*(volatile union un_reg *)0xD8)
#define	_UDR1		(*(volatile union un_reg *)0xCE)
#define	_UBRR1H		(*(volatile union un_reg *)0xCD)
#define	_UBRR1L		(*(volatile union un_reg *)0xCC)
#define	_UCSR1C		(*(volatile union un_reg *)0xCA)
#define	_UCSR1B		(*(volatile union un_reg *)0xC9)
#define	_UCSR1A		(*(volatile union un_reg *)0xC8)
#define	_UDR0		(*(volatile union un_reg *)0xC6)
#define	_UBRR0H		(*(volatile union un_reg *)0xC5)
#define	_UBRR0L		(*(volatile union un_reg *)0xC4)
#define	_UCSR0C		(*(volatile union un_reg *)0xC2)
#define	_UCSR0B		(*(volatile union un_reg *)0xC1)
#define	_UCSR0A		(*(volatile union un_reg *)0xC0)
#define	_TWCR		(*(volatile union un_reg *)0xBC)
#define	_TWDR		(*(volatile union un_reg *)0xBB)
#define	_TWAR		(*(volatile union un_reg *)0xBA)
#define	_TWSR		(*(volatile union un_reg *)0xB9)
#define	_TWBR		(*(volatile union un_reg *)0xB8)
#define	_ASSR		(*(volatile union un_reg *)0xB6)
#define	_OCR2A		(*(volatile union un_reg *)0xB3)
#define	_TCNT2		(*(volatile union un_reg *)0xB2)
#define	_TCCR2A		(*(volatile union un_reg *)0xB0)
#define	_OCR3CH		(*(volatile union un_reg *)0x9D)
#define	_OCR3CL		(*(volatile union un_reg *)0x9C)
#define	_OCR3BH		(*(volatile union un_reg *)0x9B)
#define	_OCR3BL		(*(volatile union un_reg *)0x9A)
#define	_OCR3AH		(*(volatile union un_reg *)0x99)
#define	_OCR3AL		(*(volatile union un_reg *)0x98)
#define	_ICR3H		(*(volatile union un_reg *)0x97)
#define	_ICR3L		(*(volatile union un_reg *)0x96)
#define	_TCNT3H		(*(volatile union un_reg *)0x95)
#define	_TCNT3L		(*(volatile union un_reg *)0x94)
#define	_TCCR3C		(*(volatile union un_reg *)0x92)
#define	_TCCR3B		(*(volatile union un_reg *)0x91)
#define	_TCCR3A		(*(volatile union un_reg *)0x90)
#define	_OCR1CH		(*(volatile union un_reg *)0x8D)
#define	_OCR1CL		(*(volatile union un_reg *)0x8C)
#define	_OCR1BH		(*(volatile union un_reg *)0x8B)
#define	_OCR1BL		(*(volatile union un_reg *)0x8A)
#define	_OCR1AH		(*(volatile union un_reg *)0x89)
#define	_OCR1AL		(*(volatile union un_reg *)0x88)
#define	_ICR1H		(*(volatile union un_reg *)0x87)
#define	_ICR1L		(*(volatile union un_reg *)0x86)
#define	_TCNT1H		(*(volatile union un_reg *)0x85)
#define	_TCNT1L		(*(volatile union un_reg *)0x84)
#define	_TCCR1C		(*(volatile union un_reg *)0x82)
#define	_TCCR1B		(*(volatile union un_reg *)0x81)
#define	_TCCR1A		(*(volatile union un_reg *)0x80)
#define	_DIDR1		(*(volatile union un_reg *)0x7F)
#define	_DIDR0		(*(volatile union un_reg *)0x7E)
#define	_ADMUX		(*(volatile union un_reg *)0x7C)
#define	_ADCSRB		(*(volatile union un_reg *)0x7B)
#define	_ADCSRA		(*(volatile union un_reg *)0x7A)
#define	_ADCH		(*(volatile union un_reg *)0x79)
#define	_ADCL		(*(volatile union un_reg *)0x78)
#define	_XMCRB		(*(volatile union un_reg *)0x75)
#define	_XMCRA		(*(volatile union un_reg *)0x74)
#define	_TIMSK3		(*(volatile union un_reg *)0x71)
#define	_TIMSK2		(*(volatile union un_reg *)0x70)
#define	_TIMSK1		(*(volatile union un_reg *)0x6F)
#define	_TIMSK0		(*(volatile union un_reg *)0x6E)
#define	_EICRB		(*(volatile union un_reg *)0x6A)
#define	_EICRA		(*(volatile union un_reg *)0x69)
#define	_OSCCAL		(*(volatile union un_reg *)0x66)
#define	_CLKPR		(*(volatile union un_reg *)0x61)
#define	_WDTCR		(*(volatile union un_reg *)0x60)
#define	_SREG		(*(volatile union un_reg *)0x5F)
#define	_SPH		(*(volatile union un_reg *)0x5E)
#define	_SPL		(*(volatile union un_reg *)0x5D)
#define	_RAMPZ		(*(volatile union un_reg *)0x5B)
#define	_SPMCSR		(*(volatile union un_reg *)0x57)
#define	_MCUCR		(*(volatile union un_reg *)0x55)
#define	_MCUSR		(*(volatile union un_reg *)0x54)
#define	_SMCR		(*(volatile union un_reg *)0x53)
#define	_OCDR		(*(volatile union un_reg *)0x51)
#define	_ACSR		(*(volatile union un_reg *)0x50)
#define	_SPDR		(*(volatile union un_reg *)0x4E)
#define	_SPSR		(*(volatile union un_reg *)0x4D)
#define	_SPCR		(*(volatile union un_reg *)0x4C)
#define	_GPIOR2		(*(volatile union un_reg *)0x4B)
#define	_GPIOR1		(*(volatile union un_reg *)0x4A)
#define	_OCR0A		(*(volatile union un_reg *)0x47)
#define	_TCNT0		(*(volatile union un_reg *)0x46)
#define	_TCCR0A		(*(volatile union un_reg *)0x44)
#define	_GTCCR		(*(volatile union un_reg *)0x43)
#define	_EEARH		(*(volatile union un_reg *)0x42)
#define	_EEARL		(*(volatile union un_reg *)0x41)
#define	_EEDR		(*(volatile union un_reg *)0x40)
#define	_EECR		(*(volatile union un_reg *)0x3F)
#define	_GPIOR0		(*(volatile union un_reg *)0x3E)
#define	_EIMSK		(*(volatile union un_reg *)0x3D)
#define	_EIFR		(*(volatile union un_reg *)0x3C)
#define	_TIFR3		(*(volatile union un_reg *)0x38)
#define	_TIFR2		(*(volatile union un_reg *)0x37)
#define	_TIFR1		(*(volatile union un_reg *)0x36)
#define	_TIFR0		(*(volatile union un_reg *)0x35)
#define	_PORTG		(*(volatile union un_reg *)0x34)
#define	_DDRG		(*(volatile union un_reg *)0x33)
#define	_PING		(*(volatile union un_reg *)0x32)
#define	_PORTF		(*(volatile union un_reg *)0x31)
#define	_DDRF		(*(volatile union un_reg *)0x30)
#define	_PINF		(*(volatile union un_reg *)0x2F)
#define	_PORTE		(*(volatile union un_reg *)0x2E)
#define	_DDRE		(*(volatile union un_reg *)0x2D)
#define	_PINE		(*(volatile union un_reg *)0x2C)
#define	_PORTD		(*(volatile union un_reg *)0x2B)
#define	_DDRD		(*(volatile union un_reg *)0x2A)
#define	_PIND		(*(volatile union un_reg *)0x29)
#define	_PORTC		(*(volatile union un_reg *)0x28)
#define	_DDRC		(*(volatile union un_reg *)0x27)
#define	_PINC		(*(volatile union un_reg *)0x26)
#define	_PORTB		(*(volatile union un_reg *)0x25)
#define	_DDRB		(*(volatile union un_reg *)0x24)
#define	_PINB		(*(volatile union un_reg *)0x23)
#define	_PORTA		(*(volatile union un_reg *)0x22)
#define	_DDRA		(*(volatile union un_reg *)0x21)
#define	_PINA		(*(volatile union un_reg *)0x20)




#define	CANMSG		_CANMSG.ALL
#define	MSG7		_CANMSG.BIT.BIT7
#define	MSG6		_CANMSG.BIT.BIT6
#define	MSG5		_CANMSG.BIT.BIT5
#define	MSG4		_CANMSG.BIT.BIT4
#define	MSG3		_CANMSG.BIT.BIT3
#define	MSG2		_CANMSG.BIT.BIT2
#define	MSG1		_CANMSG.BIT.BIT1
#define	MSG0		_CANMSG.BIT.BIT0

#define	CANSTMH		_CANSTMH.ALL
#define	TIMSTM15	_CANSTMH.BIT.BIT7
#define	TIMSTM14	_CANSTMH.BIT.BIT6
#define	TIMSTM13	_CANSTMH.BIT.BIT5
#define	TIMSTM12	_CANSTMH.BIT.BIT4
#define	TIMSTM11	_CANSTMH.BIT.BIT3
#define	TIMSTM10	_CANSTMH.BIT.BIT2
#define	TIMSTM9		_CANSTMH.BIT.BIT1
#define	TIMSTM8		_CANSTMH.BIT.BIT0

#define	CANSTML		_CANSTML.ALL
#define	TIMSTM7		_CANSTML.BIT.BIT7
#define	TIMSTM6		_CANSTML.BIT.BIT6
#define	TIMSTM5		_CANSTML.BIT.BIT5
#define	TIMSTM4		_CANSTML.BIT.BIT4
#define	TIMSTM3		_CANSTML.BIT.BIT3
#define	TIMSTM2		_CANSTML.BIT.BIT2
#define	TIMSTM1		_CANSTML.BIT.BIT1
#define	TIMSTM0		_CANSTML.BIT.BIT0

#define	CANIDM1		_CANIDM1.ALL
#define	IDMSK28		_CANIDM1.BIT.BIT7
#define	IDMSK27		_CANIDM1.BIT.BIT6
#define	IDMSK26		_CANIDM1.BIT.BIT5
#define	IDMSK25		_CANIDM1.BIT.BIT4
#define	IDMSK24		_CANIDM1.BIT.BIT3
#define	IDMSK23		_CANIDM1.BIT.BIT2
#define	IDMSK22		_CANIDM1.BIT.BIT1
#define	IDMSK21		_CANIDM1.BIT.BIT0

#define	CANIDM2		_CANIDM2.ALL
#define	IDMSK20		_CANIDM2.BIT.BIT7
#define	IDMSK19		_CANIDM2.BIT.BIT6
#define	IDMSK18		_CANIDM2.BIT.BIT5
#define	IDMSK17		_CANIDM2.BIT.BIT4
#define	IDMSK16		_CANIDM2.BIT.BIT3
#define	IDMSK15		_CANIDM2.BIT.BIT2
#define	IDMSK14		_CANIDM2.BIT.BIT1
#define	IDMSK13		_CANIDM2.BIT.BIT0

#define	CANIDM3		_CANIDM3.ALL
#define	IDMSK12		_CANIDM3.BIT.BIT7
#define	IDMSK11		_CANIDM3.BIT.BIT6
#define	IDMSK10		_CANIDM3.BIT.BIT5
#define	IDMSK9		_CANIDM3.BIT.BIT4
#define	IDMSK8		_CANIDM3.BIT.BIT3
#define	IDMSK7		_CANIDM3.BIT.BIT2
#define	IDMSK6		_CANIDM3.BIT.BIT1
#define	IDMSK5		_CANIDM3.BIT.BIT0

#define	CANIDM4		_CANIDM4.ALL
#define	IDMSK4		_CANIDM4.BIT.BIT7
#define	IDMSK3		_CANIDM4.BIT.BIT6
#define	IDMSK2		_CANIDM4.BIT.BIT5
#define	IDMSK1		_CANIDM4.BIT.BIT4
#define	IDMSK0		_CANIDM4.BIT.BIT3
#define	RTRMSK		_CANIDM4.BIT.BIT2
#define	IDEMSK		_CANIDM4.BIT.BIT0

#define	CANIDT1		_CANIDT1.ALL
#define	IDT28		_CANIDT1.BIT.BIT7
#define	IDT27		_CANIDT1.BIT.BIT6
#define	IDT26		_CANIDT1.BIT.BIT5
#define	IDT25		_CANIDT1.BIT.BIT4
#define	IDT24		_CANIDT1.BIT.BIT3
#define	IDT23		_CANIDT1.BIT.BIT2
#define	IDT22		_CANIDT1.BIT.BIT1
#define	IDT21		_CANIDT1.BIT.BIT0

#define	CANIDT2		_CANIDT2.ALL
#define	IDT20		_CANIDT2.BIT.BIT7
#define	IDT19		_CANIDT2.BIT.BIT6
#define	IDT18		_CANIDT2.BIT.BIT5
#define	IDT17		_CANIDT2.BIT.BIT4
#define	IDT16		_CANIDT2.BIT.BIT3
#define	IDT15		_CANIDT2.BIT.BIT2
#define	IDT14		_CANIDT2.BIT.BIT1
#define	IDT13		_CANIDT2.BIT.BIT0

#define	CANIDT3		_CANIDT3.ALL
#define	IDT12		_CANIDT3.BIT.BIT7
#define	IDT11		_CANIDT3.BIT.BIT6
#define	IDT10		_CANIDT3.BIT.BIT5
#define	IDT9		_CANIDT3.BIT.BIT4
#define	IDT8		_CANIDT3.BIT.BIT3
#define	IDT7		_CANIDT3.BIT.BIT2
#define	IDT6		_CANIDT3.BIT.BIT1
#define	IDT5		_CANIDT3.BIT.BIT0

#define	CANIDT4		_CANIDT4.ALL
#define	IDT4		_CANIDT4.BIT.BIT7
#define	IDT3		_CANIDT4.BIT.BIT6
#define	IDT2		_CANIDT4.BIT.BIT5
#define	IDT1		_CANIDT4.BIT.BIT4
#define	IDT0		_CANIDT4.BIT.BIT3
#define	RTRTAG		_CANIDT4.BIT.BIT2
#define	RB1TAG		_CANIDT4.BIT.BIT1
#define	RB0TAG		_CANIDT4.BIT.BIT0

#define	CANCDMOB	_CANCDMOB.ALL
#define	CONMOB1		_CANCDMOB.BIT.BIT7
#define	CONMOB0		_CANCDMOB.BIT.BIT6
#define	RPLV		_CANCDMOB.BIT.BIT5
#define	IDE			_CANCDMOB.BIT.BIT4
#define	DLC3		_CANCDMOB.BIT.BIT3
#define	DLC2		_CANCDMOB.BIT.BIT2
#define	DLC1		_CANCDMOB.BIT.BIT1
#define	DLC0		_CANCDMOB.BIT.BIT0

#define	CANSTMOB	_CANSTMOB.ALL
#define	DLCW		_CANSTMOB.BIT.BIT7
#define	TXOK		_CANSTMOB.BIT.BIT6
#define	RXOK		_CANSTMOB.BIT.BIT5
#define	BERR		_CANSTMOB.BIT.BIT4
#define	SERR		_CANSTMOB.BIT.BIT3
#define	CERR		_CANSTMOB.BIT.BIT2
#define	FERR		_CANSTMOB.BIT.BIT1
#define	AERR		_CANSTMOB.BIT.BIT0

#define	CANPAGE		_CANPAGE.ALL
#define	MOBNB3		_CANPAGE.BIT.BIT7
#define	MOBNB2		_CANPAGE.BIT.BIT6
#define	MOBNB1		_CANPAGE.BIT.BIT5
#define	MOBNB0		_CANPAGE.BIT.BIT4
#define	AINC		_CANPAGE.BIT.BIT3
#define	INDX2		_CANPAGE.BIT.BIT2
#define	INDX1		_CANPAGE.BIT.BIT1
#define	INDX0		_CANPAGE.BIT.BIT0

#define	CANHPMOB	_CANHPMOB.ALL
#define	HPMOB3		_CANHPMOB.BIT.BIT7
#define	HPMOB2		_CANHPMOB.BIT.BIT6
#define	HPMOB1		_CANHPMOB.BIT.BIT5
#define	HPMOB0		_CANHPMOB.BIT.BIT4
#define	CGP3		_CANHPMOB.BIT.BIT3
#define	CGP2		_CANHPMOB.BIT.BIT2
#define	CGP1		_CANHPMOB.BIT.BIT1
#define	CGP0		_CANHPMOB.BIT.BIT0

#define	CANREC		_CANREC.ALL
#define	REC7		_CANREC.BIT.BIT7
#define	REC6		_CANREC.BIT.BIT6
#define	REC5		_CANREC.BIT.BIT5
#define	REC4		_CANREC.BIT.BIT4
#define	REC3		_CANREC.BIT.BIT3
#define	REC2		_CANREC.BIT.BIT2
#define	REC1		_CANREC.BIT.BIT1
#define	REC0		_CANREC.BIT.BIT0

#define	CANTEC		_CANTEC.ALL
#define	TEC7		_CANTEC.BIT.BIT7
#define	TEC6		_CANTEC.BIT.BIT6
#define	TEC5		_CANTEC.BIT.BIT5
#define	TEC4		_CANTEC.BIT.BIT4
#define	TEC3		_CANTEC.BIT.BIT3
#define	TEC2		_CANTEC.BIT.BIT2
#define	TEC1		_CANTEC.BIT.BIT1
#define	TEC0		_CANTEC.BIT.BIT0

#define	CANTTCH		_CANTTCH.ALL
#define	TIMTTC15	_CANTTCH.BIT.BIT7
#define	TIMTTC14	_CANTTCH.BIT.BIT6
#define	TIMTTC13	_CANTTCH.BIT.BIT5
#define	TIMTTC12	_CANTTCH.BIT.BIT4
#define	TIMTTC11	_CANTTCH.BIT.BIT3
#define	TIMTTC10	_CANTTCH.BIT.BIT2
#define	TIMTTC9		_CANTTCH.BIT.BIT1
#define	TIMTTC8		_CANTTCH.BIT.BIT0

#define	CANTTCL		_CANTTCL.ALL
#define	TIMTTC7		_CANTTCL.BIT.BIT7
#define	TIMTTC6		_CANTTCL.BIT.BIT6
#define	TIMTTC5		_CANTTCL.BIT.BIT5
#define	TIMTTC4		_CANTTCL.BIT.BIT4
#define	TIMTTC3		_CANTTCL.BIT.BIT3
#define	TIMTTC2		_CANTTCL.BIT.BIT2
#define	TIMTTC1		_CANTTCL.BIT.BIT1
#define	TIMTTC0		_CANTTCL.BIT.BIT0

#define	CANTIMH		_CANTIMH.ALL
#define	CANTIM15	_CANTIMH.BIT.BIT7
#define	CANTIM14	_CANTIMH.BIT.BIT6
#define	CANTIM13	_CANTIMH.BIT.BIT5
#define	CANTIM12	_CANTIMH.BIT.BIT4
#define	CANTIM11	_CANTIMH.BIT.BIT3
#define	CANTIM10	_CANTIMH.BIT.BIT2
#define	CANTIM9		_CANTIMH.BIT.BIT1
#define	CANTIM8		_CANTIMH.BIT.BIT0

#define	CANTIML		_CANTIML.ALL
#define	CANTIM7		_CANTIML.BIT.BIT7
#define	CANTIM6		_CANTIML.BIT.BIT6
#define	CANTIM5		_CANTIML.BIT.BIT5
#define	CANTIM4		_CANTIML.BIT.BIT4
#define	CANTIM3		_CANTIML.BIT.BIT3
#define	CANTIM2		_CANTIML.BIT.BIT2
#define	CANTIM1		_CANTIML.BIT.BIT1
#define	CANTIM0		_CANTIML.BIT.BIT0

#define	CANTCON		_CANTCON.ALL
#define	TPRSC7		_CANTCON.BIT.BIT7
#define	TPRSC6		_CANTCON.BIT.BIT6
#define	TPRSC5		_CANTCON.BIT.BIT5
#define	TPRSC4		_CANTCON.BIT.BIT4
#define	TPRSC3		_CANTCON.BIT.BIT3
#define	TPRSC2		_CANTCON.BIT.BIT2
#define	TRPSC1		_CANTCON.BIT.BIT1
#define	TPRSC0		_CANTCON.BIT.BIT0

#define	CANBT3		_CANBT3.ALL
#define	PHS22		_CANBT3.BIT.BIT6
#define	PHS21		_CANBT3.BIT.BIT5
#define	PHS20		_CANBT3.BIT.BIT4
#define	PHS12		_CANBT3.BIT.BIT3
#define	PHS11		_CANBT3.BIT.BIT2
#define	PHS10		_CANBT3.BIT.BIT1
#define	SMP			_CANBT3.BIT.BIT0

#define	CANBT2		_CANBT2.ALL
#define	SJW1		_CANBT2.BIT.BIT6
#define	SJW0		_CANBT2.BIT.BIT5
#define	PRS2		_CANBT2.BIT.BIT3
#define	PRS1		_CANBT2.BIT.BIT2
#define	PRS0		_CANBT2.BIT.BIT1

#define	CANBT1		_CANBT1.ALL
#define	BRP5		_CANBT1.BIT.BIT6
#define	BRP4		_CANBT1.BIT.BIT5
#define	BRP3		_CANBT1.BIT.BIT4
#define	BRP2		_CANBT1.BIT.BIT3
#define	BRP1		_CANBT1.BIT.BIT2
#define	BRP0		_CANBT1.BIT.BIT1

#define	CANSIT1		_CANSIT1.ALL
#define	SIT14		_CANSIT1.BIT.BIT6
#define	SIT13		_CANSIT1.BIT.BIT5
#define	SIT12		_CANSIT1.BIT.BIT4
#define	SIT11		_CANSIT1.BIT.BIT3
#define	SIT10		_CANSIT1.BIT.BIT2
#define	SIT9		_CANSIT1.BIT.BIT1
#define	SIT8		_CANSIT1.BIT.BIT0

#define	CANSIT2		_CANSIT2.ALL
#define	SIT7		_CANSIT2.BIT.BIT7
#define	SIT6		_CANSIT2.BIT.BIT6
#define	SIT5		_CANSIT2.BIT.BIT5
#define	SIT4		_CANSIT2.BIT.BIT4
#define	SIT3		_CANSIT2.BIT.BIT3
#define	SIT2		_CANSIT2.BIT.BIT2
#define	SIT1		_CANSIT2.BIT.BIT1
#define	SIT0		_CANSIT2.BIT.BIT0

#define	CANIE1		_CANIE1.ALL
#define	IEMOB14		_CANIE1.BIT.BIT6
#define	IEMOB13		_CANIE1.BIT.BIT5
#define	IEMOB12		_CANIE1.BIT.BIT4
#define	IEMOB11		_CANIE1.BIT.BIT3
#define	IEMOB10		_CANIE1.BIT.BIT2
#define	IEMOB9		_CANIE1.BIT.BIT1
#define	IEMOB8		_CANIE1.BIT.BIT0

#define	CANIE2		_CANIE2.ALL
#define	IEMOB7		_CANIE2.BIT.BIT7
#define	IEMOB6		_CANIE2.BIT.BIT6
#define	IEMOB5		_CANIE2.BIT.BIT5
#define	IEMOB4		_CANIE2.BIT.BIT4
#define	IEMOB3		_CANIE2.BIT.BIT3
#define	IEMOB2		_CANIE2.BIT.BIT2
#define	IEMOB1		_CANIE2.BIT.BIT1
#define	IEMOB0		_CANIE2.BIT.BIT0

#define	CANEN1		_CANEN1.ALL
#define	ENMOB14		_CANEN1.BIT.BIT6
#define	ENMOB13		_CANEN1.BIT.BIT5
#define	ENMOB12		_CANEN1.BIT.BIT4
#define	ENMOB11		_CANEN1.BIT.BIT3
#define	ENMOB10		_CANEN1.BIT.BIT2
#define	ENMOB9		_CANEN1.BIT.BIT1
#define	ENMOB8		_CANEN1.BIT.BIT0

#define	CANEN2		_CANEN2.ALL
#define	ENMOB7		_CANEN2.BIT.BIT7
#define	ENMOB6		_CANEN2.BIT.BIT6
#define	ENMOB5		_CANEN2.BIT.BIT5
#define	ENMOB4		_CANEN2.BIT.BIT4
#define	ENMOB3		_CANEN2.BIT.BIT3
#define	ENMOB2		_CANEN2.BIT.BIT2
#define	ENMOB1		_CANEN2.BIT.BIT1
#define	ENMOB0		_CANEN2.BIT.BIT0

#define	CANGIE		_CANGIE.ALL
#define	ENIT		_CANGIE.BIT.BIT7
#define	ENBOFF		_CANGIE.BIT.BIT6
#define	ENRX		_CANGIE.BIT.BIT5
#define	ENTX		_CANGIE.BIT.BIT4
#define	ENERR		_CANGIE.BIT.BIT3
#define	ENBX		_CANGIE.BIT.BIT2
#define	ENERG		_CANGIE.BIT.BIT1
#define	ENOVRT		_CANGIE.BIT.BIT0

#define	CANGIT		_CANGIT.ALL
#define	CANIT		_CANGIT.BIT.BIT7
#define	BOFFIT		_CANGIT.BIT.BIT6
#define	OVRTIM		_CANGIT.BIT.BIT5
#define	BXOK		_CANGIT.BIT.BIT4
#define	SERG		_CANGIT.BIT.BIT3
#define	CERG		_CANGIT.BIT.BIT2
#define	FERG		_CANGIT.BIT.BIT1
#define	AERG		_CANGIT.BIT.BIT0

#define	CANGSTA		_CANGSTA.ALL
#define	OVRG		_CANGSTA.BIT.BIT6
#define	TXBSY		_CANGSTA.BIT.BIT4
#define	RXBSY		_CANGSTA.BIT.BIT3
#define	ENFG		_CANGSTA.BIT.BIT2
#define	BOFF		_CANGSTA.BIT.BIT1
#define	ERRP		_CANGSTA.BIT.BIT0

#define	CANGCON		_CANGCON.ALL
#define	ABRQ		_CANGCON.BIT.BIT7
#define	OVRQ		_CANGCON.BIT.BIT6
#define	TTC			_CANGCON.BIT.BIT5
#define	SYNTTC		_CANGCON.BIT.BIT4
#define	LISTEN		_CANGCON.BIT.BIT3
#define	TEST		_CANGCON.BIT.BIT2
#define	ENA_STB		_CANGCON.BIT.BIT1
#define	SWRES		_CANGCON.BIT.BIT0

#define	UDR1		_UDR1.ALL
#define	UDR17		_UDR1.BIT.BIT7
#define	UDR16		_UDR1.BIT.BIT6
#define	UDR15		_UDR1.BIT.BIT5
#define	UDR14		_UDR1.BIT.BIT4
#define	UDR13		_UDR1.BIT.BIT3
#define	UDR12		_UDR1.BIT.BIT2
#define	UDR11		_UDR1.BIT.BIT1
#define	UDR10		_UDR1.BIT.BIT0

#define	UBRR1H		_UBRR1H.ALL
#define	UBRR111		_UBRR1H.BIT.BIT3
#define	UBRR110		_UBRR1H.BIT.BIT2
#define	UBRR19		_UBRR1H.BIT.BIT1
#define	UBRR18		_UBRR1H.BIT.BIT0

#define	UBRR1L		_UBRR1L.ALL
#define	UBRR17		_UBRR1L.BIT.BIT7
#define	UBRR16		_UBRR1L.BIT.BIT6
#define	UBRR15		_UBRR1L.BIT.BIT5
#define	UBRR14		_UBRR1L.BIT.BIT4
#define	UBRR13		_UBRR1L.BIT.BIT3
#define	UBRR12		_UBRR1L.BIT.BIT2
#define	UBRR11		_UBRR1L.BIT.BIT1
#define	UBRR10		_UBRR1L.BIT.BIT0

#define	UCSR1C		_UCSR1C.ALL
#define	UMSEL1		_UCSR1C.BIT.BIT6
#define	UPM11		_UCSR1C.BIT.BIT5
#define	UPM10		_UCSR1C.BIT.BIT4
#define	USBS1		_UCSR1C.BIT.BIT3
#define	UCSZ11		_UCSR1C.BIT.BIT2
#define	UCSZ10		_UCSR1C.BIT.BIT1
#define	UCPOL1		_UCSR1C.BIT.BIT0

#define	UCSR1B		_UCSR1B.ALL
#define	RXCIE1		_UCSR1B.BIT.BIT7
#define	TXCIE1		_UCSR1B.BIT.BIT6
#define	UDRIE1		_UCSR1B.BIT.BIT5
#define	RXEN1		_UCSR1B.BIT.BIT4
#define	TXEN1		_UCSR1B.BIT.BIT3
#define	UCSZ12		_UCSR1B.BIT.BIT2
#define	RXB81		_UCSR1B.BIT.BIT1
#define	TXB81		_UCSR1B.BIT.BIT0

#define	UCSR1A		_UCSR1A.ALL
#define	RXC1		_UCSR1A.BIT.BIT7
#define	TXC1		_UCSR1A.BIT.BIT6
#define	UDRE1		_UCSR1A.BIT.BIT5
#define	FE1			_UCSR1A.BIT.BIT4
#define	DOR1		_UCSR1A.BIT.BIT3
#define	UPE1		_UCSR1A.BIT.BIT2
#define	U2X1		_UCSR1A.BIT.BIT1
#define	MPCM1		_UCSR1A.BIT.BIT0

#define	UDR0		_UDR0.ALL
#define	UDR07		_UDR0.BIT.BIT7
#define	UDR06		_UDR0.BIT.BIT6
#define	UDR05		_UDR0.BIT.BIT5
#define	UDR04		_UDR0.BIT.BIT4
#define	UDR03		_UDR0.BIT.BIT3
#define	UDR02		_UDR0.BIT.BIT2
#define	UDR01		_UDR0.BIT.BIT1
#define	UDR00		_UDR0.BIT.BIT0

#define	UBRR0H		_UBRR0H.ALL
#define	UBRR011		_UBRR0H.BIT.BIT3
#define	UBRR010		_UBRR0H.BIT.BIT2
#define	UBRR09		_UBRR0H.BIT.BIT1
#define	UBRR08		_UBRR0H.BIT.BIT0

#define	UBRR0L		_UBRR0L.ALL
#define	UBRR07		_UBRR0L.BIT.BIT7
#define	UBRR06		_UBRR0L.BIT.BIT6
#define	UBRR05		_UBRR0L.BIT.BIT5
#define	UBRR04		_UBRR0L.BIT.BIT4
#define	UBRR03		_UBRR0L.BIT.BIT3
#define	UBRR02		_UBRR0L.BIT.BIT2
#define	UBRR01		_UBRR0L.BIT.BIT1
#define	UBRR00		_UBRR0L.BIT.BIT0

#define	UCSR0C		_UCSR0C.ALL
#define	UMSEL0		_UCSR0C.BIT.BIT6
#define	UPM01		_UCSR0C.BIT.BIT5
#define	UPM00		_UCSR0C.BIT.BIT4
#define	USBS0		_UCSR0C.BIT.BIT3
#define	UCSZ01		_UCSR0C.BIT.BIT2
#define	UCSZ00		_UCSR0C.BIT.BIT1
#define	UCPOL0		_UCSR0C.BIT.BIT0

#define	UCSR0B		_UCSR0B.ALL
#define	RXCIE0		_UCSR0B.BIT.BIT7
#define	TXCIE0		_UCSR0B.BIT.BIT6
#define	UDRIE0		_UCSR0B.BIT.BIT5
#define	RXEN0		_UCSR0B.BIT.BIT4
#define	TXEN0		_UCSR0B.BIT.BIT3
#define	UCSZ02		_UCSR0B.BIT.BIT2
#define	RXB80		_UCSR0B.BIT.BIT1
#define	TXB80		_UCSR0B.BIT.BIT0

#define	UCSR0A		_UCSR0A.ALL
#define	RXC0		_UCSR0A.BIT.BIT7
#define	TXC0		_UCSR0A.BIT.BIT6
#define	UDRE0		_UCSR0A.BIT.BIT5
#define	FE0			_UCSR0A.BIT.BIT4
#define	DOR0		_UCSR0A.BIT.BIT3
#define	UPE0		_UCSR0A.BIT.BIT2
#define	U2X0		_UCSR0A.BIT.BIT1
#define	MPCM0		_UCSR0A.BIT.BIT0

#define	TWCR		_TWCR.ALL
#define	TWINT		_TWCR.BIT.BIT7
#define	TWEA		_TWCR.BIT.BIT6
#define	TWSTA		_TWCR.BIT.BIT5
#define	TWSTO		_TWCR.BIT.BIT4
#define	TWWC		_TWCR.BIT.BIT3
#define	TWEN		_TWCR.BIT.BIT2
#define	TWIE		_TWCR.BIT.BIT0

#define	TWDR		_TWDR.ALL
#define	TWDR7		_TWDR.BIT.BIT7
#define	TWDR6		_TWDR.BIT.BIT6
#define	TWDR5		_TWDR.BIT.BIT5
#define	TWDR4		_TWDR.BIT.BIT4
#define	TWDR3		_TWDR.BIT.BIT3
#define	TWDR2		_TWDR.BIT.BIT2
#define	TWDR1		_TWDR.BIT.BIT1
#define	TWDR0		_TWDR.BIT.BIT0

#define	TWAR		_TWAR.ALL
#define	TWAR6		_TWAR.BIT.BIT7
#define	TWAR5		_TWAR.BIT.BIT6
#define	TWAR4		_TWAR.BIT.BIT5
#define	TWAR3		_TWAR.BIT.BIT4
#define	TWAR2		_TWAR.BIT.BIT3
#define	TWAR1		_TWAR.BIT.BIT2
#define	TWAR0		_TWAR.BIT.BIT1
#define	TWGCE		_TWAR.BIT.BIT0

#define	TWSR		_TWSR.ALL
#define	TWS7		_TWSR.BIT.BIT7
#define	TWS6		_TWSR.BIT.BIT6
#define	TWS5		_TWSR.BIT.BIT5
#define	TWS4		_TWSR.BIT.BIT4
#define	TWS3		_TWSR.BIT.BIT3
#define	TWPS1		_TWSR.BIT.BIT1
#define	TWPS0		_TWSR.BIT.BIT0

#define	TWBR		_TWBR.ALL
#define	TWBR7		_TWBR.BIT.BIT7
#define	TWBR6		_TWBR.BIT.BIT6
#define	TWBR5		_TWBR.BIT.BIT5
#define	TWBR4		_TWBR.BIT.BIT4
#define	TWBR3		_TWBR.BIT.BIT3
#define	TWBR2		_TWBR.BIT.BIT2
#define	TWBR1		_TWBR.BIT.BIT1
#define	TWBR0		_TWBR.BIT.BIT0

#define	ASSR		_ASSR.ALL
#define	EXCLK		_ASSR.BIT.BIT4
#define	AS2			_ASSR.BIT.BIT3
#define	TCN2UB		_ASSR.BIT.BIT2
#define	OCR2UB		_ASSR.BIT.BIT1
#define	TCR2UB		_ASSR.BIT.BIT0

#define	OCR2A		_OCR2A.ALL
#define	OCR2A7		_OCR2A.BIT.BIT7
#define	OCR2A6		_OCR2A.BIT.BIT6
#define	OCR2A5		_OCR2A.BIT.BIT5
#define	OCR2A4		_OCR2A.BIT.BIT4
#define	OCR2A3		_OCR2A.BIT.BIT3
#define	OCR2A2		_OCR2A.BIT.BIT2
#define	OCR2A1		_OCR2A.BIT.BIT1
#define	OCR2A0		_OCR2A.BIT.BIT0

#define	TCNT2		_TCNT2.ALL
#define	TCNT27		_TCNT2.BIT.BIT7
#define	TCNT26		_TCNT2.BIT.BIT6
#define	TCNT25		_TCNT2.BIT.BIT5
#define	TCNT24		_TCNT2.BIT.BIT4
#define	TCNT23		_TCNT2.BIT.BIT3
#define	TCNT22		_TCNT2.BIT.BIT2
#define	TCNT21		_TCNT2.BIT.BIT1
#define	TCNT20		_TCNT2.BIT.BIT0

#define	TCCR2A		_TCCR2A.ALL
#define	FOC2A		_TCCR2A.BIT.BIT7
#define	WGM20		_TCCR2A.BIT.BIT6
#define	COM2A1		_TCCR2A.BIT.BIT5
#define	COM2A0		_TCCR2A.BIT.BIT4
#define	WGM21		_TCCR2A.BIT.BIT3
#define	CS22		_TCCR2A.BIT.BIT2
#define	CS21		_TCCR2A.BIT.BIT1
#define	CS20		_TCCR2A.BIT.BIT0

#define	OCR3CH		_OCR3CH.ALL
#define	OCR3C15		_OCR3CH.BIT.BIT7
#define	OCR3C14		_OCR3CH.BIT.BIT6
#define	OCR3C13		_OCR3CH.BIT.BIT5
#define	OCR3C12		_OCR3CH.BIT.BIT4
#define	OCR3C11		_OCR3CH.BIT.BIT3
#define	OCR3C10		_OCR3CH.BIT.BIT2
#define	OCR3C9		_OCR3CH.BIT.BIT1
#define	OCR3C8		_OCR3CH.BIT.BIT0

#define	OCR3CL		_OCR3CL.ALL
#define	OCR3C7		_OCR3CL.BIT.BIT7
#define	OCR3C6		_OCR3CL.BIT.BIT6
#define	OCR3C5		_OCR3CL.BIT.BIT5
#define	OCR3C4		_OCR3CL.BIT.BIT4
#define	OCR3C3		_OCR3CL.BIT.BIT3
#define	OCR3C2		_OCR3CL.BIT.BIT2
#define	OCR3C1		_OCR3CL.BIT.BIT1
#define	OCR3C0		_OCR3CL.BIT.BIT0

#define	OCR3BH		_OCR3BH.ALL
#define	OCR3B15		_OCR3BH.BIT.BIT7
#define	OCR3B14		_OCR3BH.BIT.BIT6
#define	OCR3B13		_OCR3BH.BIT.BIT5
#define	OCR3B12		_OCR3BH.BIT.BIT4
#define	OCR3B11		_OCR3BH.BIT.BIT3
#define	OCR3B10		_OCR3BH.BIT.BIT2
#define	OCR3B9		_OCR3BH.BIT.BIT1
#define	OCR3B8		_OCR3BH.BIT.BIT0

#define	OCR3BL		_OCR3BL.ALL
#define	OCR3B7		_OCR3BL.BIT.BIT7
#define	OCR3B6		_OCR3BL.BIT.BIT6
#define	OCR3B5		_OCR3BL.BIT.BIT5
#define	OCR3B4		_OCR3BL.BIT.BIT4
#define	OCR3B3		_OCR3BL.BIT.BIT3
#define	OCR3B2		_OCR3BL.BIT.BIT2
#define	OCR3B1		_OCR3BL.BIT.BIT1
#define	OCR3B0		_OCR3BL.BIT.BIT0

#define	OCR3AH		_OCR3AH.ALL
#define	OCR3A15		_OCR3AH.BIT.BIT7
#define	OCR3A14		_OCR3AH.BIT.BIT6
#define	OCR3A13		_OCR3AH.BIT.BIT5
#define	OCR3A12		_OCR3AH.BIT.BIT4
#define	OCR3A11		_OCR3AH.BIT.BIT3
#define	OCR3A10		_OCR3AH.BIT.BIT2
#define	OCR3A9		_OCR3AH.BIT.BIT1
#define	OCR3A8		_OCR3AH.BIT.BIT0

#define	OCR3AL		_OCR3AL.ALL
#define	OCR3A7		_OCR3AL.BIT.BIT7
#define	OCR3A6		_OCR3AL.BIT.BIT6
#define	OCR3A5		_OCR3AL.BIT.BIT5
#define	OCR3A4		_OCR3AL.BIT.BIT4
#define	OCR3A3		_OCR3AL.BIT.BIT3
#define	OCR3A2		_OCR3AL.BIT.BIT2
#define	OCR3A1		_OCR3AL.BIT.BIT1
#define	OCR3A0		_OCR3AL.BIT.BIT0

#define	ICR3H		_ICR3H.ALL
#define	ICR315		_ICR3H.BIT.BIT7
#define	ICR314		_ICR3H.BIT.BIT6
#define	ICR313		_ICR3H.BIT.BIT5
#define	ICR312		_ICR3H.BIT.BIT4
#define	ICR311		_ICR3H.BIT.BIT3
#define	ICR310		_ICR3H.BIT.BIT2
#define	ICR39		_ICR3H.BIT.BIT1
#define	ICR38		_ICR3H.BIT.BIT0

#define	ICR3L		_ICR3L.ALL
#define	ICR37		_ICR3L.BIT.BIT7
#define	ICR36		_ICR3L.BIT.BIT6
#define	ICR35		_ICR3L.BIT.BIT5
#define	ICR34		_ICR3L.BIT.BIT4
#define	ICR33		_ICR3L.BIT.BIT3
#define	ICR32		_ICR3L.BIT.BIT2
#define	ICR31		_ICR3L.BIT.BIT1
#define	ICR30		_ICR3L.BIT.BIT0

#define	TCNT3H		_TCNT3H.ALL
#define	TCNT315		_TCNT3H.BIT.BIT7
#define	TCNT314		_TCNT3H.BIT.BIT6
#define	TCNT313		_TCNT3H.BIT.BIT5
#define	TCNT312		_TCNT3H.BIT.BIT4
#define	TCNT311		_TCNT3H.BIT.BIT3
#define	TCNT310		_TCNT3H.BIT.BIT2
#define	TCNT39		_TCNT3H.BIT.BIT1
#define	TCNT38		_TCNT3H.BIT.BIT0

#define	TCNT3L		_TCNT3L.ALL
#define	TCNT37		_TCNT3L.BIT.BIT7
#define	TCNT36		_TCNT3L.BIT.BIT6
#define	TCNT35		_TCNT3L.BIT.BIT5
#define	TCNT34		_TCNT3L.BIT.BIT4
#define	TCNT33		_TCNT3L.BIT.BIT3
#define	TCNT32		_TCNT3L.BIT.BIT2
#define	TCNT31		_TCNT3L.BIT.BIT1
#define	TCNT30		_TCNT3L.BIT.BIT0

#define	TCCR3C		_TCCR3C.ALL
#define	FOC3A		_TCCR3C.BIT.BIT7
#define	FOC3B		_TCCR3C.BIT.BIT6
#define	FOC3C		_TCCR3C.BIT.BIT5

#define	TCCR3B		_TCCR3B.ALL
#define	ICNC3		_TCCR3B.BIT.BIT7
#define	ICES3		_TCCR3B.BIT.BIT6
#define	WGM33		_TCCR3B.BIT.BIT4
#define	WGM32		_TCCR3B.BIT.BIT3
#define	CS32		_TCCR3B.BIT.BIT2
#define	CS31		_TCCR3B.BIT.BIT1
#define	CS30		_TCCR3B.BIT.BIT0

#define	TCCR3A		_TCCR3A.ALL
#define	COM3A1		_TCCR3A.BIT.BIT7
#define	COM3A0		_TCCR3A.BIT.BIT6
#define	COM3B1		_TCCR3A.BIT.BIT5
#define	COM3B0		_TCCR3A.BIT.BIT4
#define	COM3C1		_TCCR3A.BIT.BIT3
#define	COM3C0		_TCCR3A.BIT.BIT2
#define	WGM31		_TCCR3A.BIT.BIT1
#define	WGM30		_TCCR3A.BIT.BIT0

#define	OCR1CH		_OCR1CH.ALL
#define	OCR1C15		_OCR1CH.BIT.BIT7
#define	OCR1C14		_OCR1CH.BIT.BIT6
#define	OCR1C13		_OCR1CH.BIT.BIT5
#define	OCR1C12		_OCR1CH.BIT.BIT4
#define	OCR1C11		_OCR1CH.BIT.BIT3
#define	OCR1C10		_OCR1CH.BIT.BIT2
#define	OCR1C9		_OCR1CH.BIT.BIT1
#define	OCR1C8		_OCR1CH.BIT.BIT0

#define	OCR1CL		_OCR1CL.ALL
#define	OCR1C7		_OCR1CL.BIT.BIT7
#define	OCR1C6		_OCR1CL.BIT.BIT6
#define	OCR1C5		_OCR1CL.BIT.BIT5
#define	OCR1C4		_OCR1CL.BIT.BIT4
#define	OCR1C3		_OCR1CL.BIT.BIT3
#define	OCR1C2		_OCR1CL.BIT.BIT2
#define	OCR1C1		_OCR1CL.BIT.BIT1
#define	OCR1C0		_OCR1CL.BIT.BIT0

#define	OCR1BH		_OCR1BH.ALL
#define	OCR1B15		_OCR1BH.BIT.BIT7
#define	OCR1B14		_OCR1BH.BIT.BIT6
#define	OCR1B13		_OCR1BH.BIT.BIT5
#define	OCR1B12		_OCR1BH.BIT.BIT4
#define	OCR1B11		_OCR1BH.BIT.BIT3
#define	OCR1B10		_OCR1BH.BIT.BIT2
#define	OCR1B9		_OCR1BH.BIT.BIT1
#define	OCR1B8		_OCR1BH.BIT.BIT0

#define	OCR1BL		_OCR1BL.ALL
#define	OCR1B7		_OCR1BL.BIT.BIT7
#define	OCR1B6		_OCR1BL.BIT.BIT6
#define	OCR1B5		_OCR1BL.BIT.BIT5
#define	OCR1B4		_OCR1BL.BIT.BIT4
#define	OCR1B3		_OCR1BL.BIT.BIT3
#define	OCR1B2		_OCR1BL.BIT.BIT2
#define	OCR1B1		_OCR1BL.BIT.BIT1
#define	OCR1B0		_OCR1BL.BIT.BIT0

#define	OCR1AH		_OCR1AH.ALL
#define	OCR1A15		_OCR1AH.BIT.BIT7
#define	OCR1A14		_OCR1AH.BIT.BIT6
#define	OCR1A13		_OCR1AH.BIT.BIT5
#define	OCR1A12		_OCR1AH.BIT.BIT4
#define	OCR1A11		_OCR1AH.BIT.BIT3
#define	OCR1A10		_OCR1AH.BIT.BIT2
#define	OCR1A9		_OCR1AH.BIT.BIT1
#define	OCR1A8		_OCR1AH.BIT.BIT0

#define	OCR1AL		_OCR1AL.ALL
#define	OCR1A7		_OCR1AL.BIT.BIT7
#define	OCR1A6		_OCR1AL.BIT.BIT6
#define	OCR1A5		_OCR1AL.BIT.BIT5
#define	OCR1A4		_OCR1AL.BIT.BIT4
#define	OCR1A3		_OCR1AL.BIT.BIT3
#define	OCR1A2		_OCR1AL.BIT.BIT2
#define	OCR1A1		_OCR1AL.BIT.BIT1
#define	OCR1A0		_OCR1AL.BIT.BIT0

#define	ICR1H		_ICR1H.ALL
#define	ICR115		_ICR1H.BIT.BIT7
#define	ICR114		_ICR1H.BIT.BIT6
#define	ICR113		_ICR1H.BIT.BIT5
#define	ICR112		_ICR1H.BIT.BIT4
#define	ICR111		_ICR1H.BIT.BIT3
#define	ICR110		_ICR1H.BIT.BIT2
#define	ICR19		_ICR1H.BIT.BIT1
#define	ICR18		_ICR1H.BIT.BIT0

#define	ICR1L		_ICR1L.ALL
#define	ICR17		_ICR1L.BIT.BIT7
#define	ICR16		_ICR1L.BIT.BIT6
#define	ICR15		_ICR1L.BIT.BIT5
#define	ICR14		_ICR1L.BIT.BIT4
#define	ICR13		_ICR1L.BIT.BIT3
#define	ICR12		_ICR1L.BIT.BIT2
#define	ICR11		_ICR1L.BIT.BIT1
#define	ICR10		_ICR1L.BIT.BIT0

#define	TCNT1H		_TCNT1H.ALL
#define	TCNT115		_TCNT1H.BIT.BIT7
#define	TCNT114		_TCNT1H.BIT.BIT6
#define	TCNT113		_TCNT1H.BIT.BIT5
#define	TCNT112		_TCNT1H.BIT.BIT4
#define	TCNT111		_TCNT1H.BIT.BIT3
#define	TCNT110		_TCNT1H.BIT.BIT2
#define	TCNT19		_TCNT1H.BIT.BIT1
#define	TCNT18		_TCNT1H.BIT.BIT0

#define	TCNT1L		_TCNT1L.ALL
#define	TCNT17		_TCNT1L.BIT.BIT7
#define	TCNT16		_TCNT1L.BIT.BIT6
#define	TCNT15		_TCNT1L.BIT.BIT5
#define	TCNT14		_TCNT1L.BIT.BIT4
#define	TCNT13		_TCNT1L.BIT.BIT3
#define	TCNT12		_TCNT1L.BIT.BIT2
#define	TCNT11		_TCNT1L.BIT.BIT1
#define	TCNT10		_TCNT1L.BIT.BIT0

#define	TCCR1C		_TCCR1C.ALL
#define	FOC1A		_TCCR1C.BIT.BIT7
#define	FOC1B		_TCCR1C.BIT.BIT6
#define	FOC1C		_TCCR1C.BIT.BIT5

#define	TCCR1B		_TCCR1B.ALL
#define	ICNC1		_TCCR1B.BIT.BIT7
#define	ICES1		_TCCR1B.BIT.BIT6
#define	WGM13		_TCCR1B.BIT.BIT4
#define	WGM12		_TCCR1B.BIT.BIT3
#define	CS12		_TCCR1B.BIT.BIT2
#define	CS11		_TCCR1B.BIT.BIT1
#define	CS10		_TCCR1B.BIT.BIT0

#define	TCCR1A		_TCCR1A.ALL
#define	COM1A1		_TCCR1A.BIT.BIT7
#define	COM1A0		_TCCR1A.BIT.BIT6
#define	COM1B1		_TCCR1A.BIT.BIT5
#define	COM1B0		_TCCR1A.BIT.BIT4
#define	COM1C1		_TCCR1A.BIT.BIT3
#define	COM1C0		_TCCR1A.BIT.BIT2
#define	WGM11		_TCCR1A.BIT.BIT1
#define	WGM10		_TCCR1A.BIT.BIT0

#define	DIDR1		_DIDR1.ALL
#define	AIN1D		_DIDR1.BIT.BIT1
#define	AIN0D		_DIDR1.BIT.BIT0

#define	DIDR0		_DIDR0.ALL
#define	ADC7D		_DIDR0.BIT.BIT7
#define	ADC6D		_DIDR0.BIT.BIT6
#define	ADC5D		_DIDR0.BIT.BIT5
#define	ADC4D		_DIDR0.BIT.BIT4
#define	ADC3D		_DIDR0.BIT.BIT3
#define	ADC2D		_DIDR0.BIT.BIT2
#define	ADC1D		_DIDR0.BIT.BIT1
#define	ADC0D		_DIDR0.BIT.BIT0

#define	ADMUX		_ADMUX.ALL
#define	REFS1		_ADMUX.BIT.BIT7
#define	REFS0		_ADMUX.BIT.BIT6
#define	ADLAR		_ADMUX.BIT.BIT5
#define	MUX4		_ADMUX.BIT.BIT4
#define	MUX3		_ADMUX.BIT.BIT3
#define	MUX2		_ADMUX.BIT.BIT2
#define	MUX1		_ADMUX.BIT.BIT1
#define	MUX0		_ADMUX.BIT.BIT0

#define	ADCSRB		_ADCSRB.ALL
#define	ACME		_ADCSRB.BIT.BIT6
#define	ADTS2		_ADCSRB.BIT.BIT2
#define	ADTS1		_ADCSRB.BIT.BIT1
#define	ADTS0		_ADCSRB.BIT.BIT0

#define	ADCSRA		_ADCSRA.ALL
#define	ADEN		_ADCSRA.BIT.BIT7
#define	ADSC		_ADCSRA.BIT.BIT6
#define	ADATE		_ADCSRA.BIT.BIT5
#define	ADIF		_ADCSRA.BIT.BIT4
#define	ADIE		_ADCSRA.BIT.BIT3
#define	ADPS2		_ADCSRA.BIT.BIT2
#define	ADPS1		_ADCSRA.BIT.BIT1
#define	ADPS0		_ADCSRA.BIT.BIT0

#define	ADCH		_ADCH.ALL

#define	ADCL		_ADCL.ALL

#define	XMCRB		_XMCRB.ALL
#define	XMBK		_XMCRB.BIT.BIT7
#define	XMM2		_XMCRB.BIT.BIT2
#define	XMM1		_XMCRB.BIT.BIT1
#define	XMM0		_XMCRB.BIT.BIT0

#define	XMCRA		_XMCRA.ALL
#define	SRE			_XMCRA.BIT.BIT7
#define	SRL2		_XMCRA.BIT.BIT6
#define	SRL1		_XMCRA.BIT.BIT5
#define	SRL0		_XMCRA.BIT.BIT4
#define	SRW11		_XMCRA.BIT.BIT3
#define	SRW10		_XMCRA.BIT.BIT2
#define	SRW01		_XMCRA.BIT.BIT1
#define	SRW00		_XMCRA.BIT.BIT0

#define	TIMSK3		_TIMSK3.ALL
#define	ICIE3		_TIMSK3.BIT.BIT5
#define	OCIE3C		_TIMSK3.BIT.BIT3
#define	OCIE3B		_TIMSK3.BIT.BIT2
#define	OCIE3A		_TIMSK3.BIT.BIT1
#define	TOIE3		_TIMSK3.BIT.BIT0

#define	TIMSK2		_TIMSK2.ALL
#define	OCIE2A		_TIMSK2.BIT.BIT1
#define	TOIE2		_TIMSK2.BIT.BIT0

#define	TIMSK1		_TIMSK1.ALL
#define	ICIE1		_TIMSK1.BIT.BIT5
#define	OCIE1C		_TIMSK1.BIT.BIT3
#define	OCIE1B		_TIMSK1.BIT.BIT2
#define	OCIE1A		_TIMSK1.BIT.BIT1
#define	TOIE1		_TIMSK1.BIT.BIT0

#define	TIMSK0		_TIMSK0.ALL
#define	OCIE0A		_TIMSK0.BIT.BIT1
#define	TOIE0		_TIMSK0.BIT.BIT0

#define	EICRB		_EICRB.ALL
#define	ISC71		_EICRB.BIT.BIT7
#define	ISC70		_EICRB.BIT.BIT6
#define	ISC61		_EICRB.BIT.BIT5
#define	ISC60		_EICRB.BIT.BIT4
#define	ISC51		_EICRB.BIT.BIT3
#define	ISC50		_EICRB.BIT.BIT2
#define	ISC41		_EICRB.BIT.BIT1
#define	ISC40		_EICRB.BIT.BIT0

#define	EICRA		_EICRA.ALL
#define	ISC31		_EICRA.BIT.BIT7
#define	ISC30		_EICRA.BIT.BIT6
#define	ISC21		_EICRA.BIT.BIT5
#define	ISC20		_EICRA.BIT.BIT4
#define	ISC11		_EICRA.BIT.BIT3
#define	ISC10		_EICRA.BIT.BIT2
#define	ISC01		_EICRA.BIT.BIT1
#define	ISC00		_EICRA.BIT.BIT0

#define	OSCCAL		_OSCCAL.ALL
#define	CAL6		_OSCCAL.BIT.BIT6
#define	CAL5		_OSCCAL.BIT.BIT5
#define	CAL4		_OSCCAL.BIT.BIT4
#define	CAL3		_OSCCAL.BIT.BIT3
#define	CAL2		_OSCCAL.BIT.BIT2
#define	CAL1		_OSCCAL.BIT.BIT1
#define	CAL0		_OSCCAL.BIT.BIT0

#define	CLKPR		_CLKPR.ALL
#define	CLKPCE		_CLKPR.BIT.BIT7
#define	CLKPS3		_CLKPR.BIT.BIT3
#define	CLKPS2		_CLKPR.BIT.BIT2
#define	CLKPS1		_CLKPR.BIT.BIT1
#define	CLKPS0		_CLKPR.BIT.BIT0

#define	WDTCR		_WDTCR.ALL
#define	WDCE		_WDTCR.BIT.BIT4
#define	WDE			_WDTCR.BIT.BIT3
#define	WDP2		_WDTCR.BIT.BIT2
#define	WDP1		_WDTCR.BIT.BIT1
#define	WDP0		_WDTCR.BIT.BIT0

#define	SREG		_SREG.ALL
#define	I			_SREG.BIT.BIT7
#define	T			_SREG.BIT.BIT6
#define	H			_SREG.BIT.BIT5
#define	S			_SREG.BIT.BIT4
#define	V			_SREG.BIT.BIT3
#define	N			_SREG.BIT.BIT2
#define	Z			_SREG.BIT.BIT1
#define	C			_SREG.BIT.BIT0

#define	SPH			_SPH.ALL
#define	SP15		_SPH.BIT.BIT7
#define	SP14		_SPH.BIT.BIT6
#define	SP13		_SPH.BIT.BIT5
#define	SP12		_SPH.BIT.BIT4
#define	SP11		_SPH.BIT.BIT3
#define	SP10		_SPH.BIT.BIT2
#define	SP9			_SPH.BIT.BIT1
#define	SP8			_SPH.BIT.BIT0

#define	SPL			_SPL.ALL
#define	SP7			_SPL.BIT.BIT7
#define	SP6			_SPL.BIT.BIT6
#define	SP5			_SPL.BIT.BIT5
#define	SP4			_SPL.BIT.BIT4
#define	SP3			_SPL.BIT.BIT3
#define	SP2			_SPL.BIT.BIT2
#define	SP1			_SPL.BIT.BIT1
#define	SP0			_SPL.BIT.BIT0

#define	RAMPZ		_RAMPZ.ALL
#define	RAMPZ0		_RAMPZ.BIT.BIT0

#define	SPMCSR		_SPMCSR.ALL
#define	SPMIE		_SPMCSR.BIT.BIT7
#define	RWWSB		_SPMCSR.BIT.BIT6
#define	RWWSRE		_SPMCSR.BIT.BIT4
#define	BLBSET		_SPMCSR.BIT.BIT3
#define	PGWRT		_SPMCSR.BIT.BIT2
#define	PGERS		_SPMCSR.BIT.BIT1
#define	SPMEN		_SPMCSR.BIT.BIT0

#define	MCUCR		_MCUCR.ALL
#define	JTD			_MCUCR.BIT.BIT7
#define	PUD			_MCUCR.BIT.BIT4
#define	IVSEL		_MCUCR.BIT.BIT1
#define	IVCE		_MCUCR.BIT.BIT0

#define	MCUSR		_MCUSR.ALL
#define	JTRF		_MCUSR.BIT.BIT4
#define	WDRF		_MCUSR.BIT.BIT3
#define	BORF		_MCUSR.BIT.BIT2
#define	EXTRF		_MCUSR.BIT.BIT1
#define	PORF		_MCUSR.BIT.BIT0

#define	SMCR		_SMCR.ALL
#define	SM2			_SMCR.BIT.BIT3
#define	SM1			_SMCR.BIT.BIT2
#define	SM0			_SMCR.BIT.BIT1
#define	SE			_SMCR.BIT.BIT0

#define	OCDR		_OCDR.ALL
#define	IDRD_OCDR7	_OCDR.BIT.BIT7
#define	OCDR6		_OCDR.BIT.BIT6
#define	OCDR5		_OCDR.BIT.BIT5
#define	OCDR4		_OCDR.BIT.BIT4
#define	OCDR3		_OCDR.BIT.BIT3
#define	OCDR2		_OCDR.BIT.BIT2
#define	OCDR1		_OCDR.BIT.BIT1
#define	OCDR0		_OCDR.BIT.BIT0

#define	ACSR		_ACSR.ALL
#define	ACD			_ACSR.BIT.BIT7
#define	ACBG		_ACSR.BIT.BIT6
#define	ACO			_ACSR.BIT.BIT5
#define	ACI			_ACSR.BIT.BIT4
#define	ACIE		_ACSR.BIT.BIT3
#define	ACIC		_ACSR.BIT.BIT2
#define	ACIS1		_ACSR.BIT.BIT1
#define	ACIS0		_ACSR.BIT.BIT0

#define	SPDR		_SPDR.ALL
#define	SPD7		_SPDR.BIT.BIT7
#define	SPD6		_SPDR.BIT.BIT6
#define	SPD5		_SPDR.BIT.BIT5
#define	SPD4		_SPDR.BIT.BIT4
#define	SPD3		_SPDR.BIT.BIT3
#define	SPD2		_SPDR.BIT.BIT2
#define	SPD1		_SPDR.BIT.BIT1
#define	SPD0		_SPDR.BIT.BIT0

#define	SPSR		_SPSR.ALL
#define	SPIF		_SPSR.BIT.BIT7
#define	WCOL		_SPSR.BIT.BIT6
#define	SPI2X		_SPSR.BIT.BIT0

#define	SPCR		_SPCR.ALL
#define	SPIE		_SPCR.BIT.BIT7
#define	SPE			_SPCR.BIT.BIT6
#define	DORD		_SPCR.BIT.BIT5
#define	MSTR		_SPCR.BIT.BIT4
#define	CPOL		_SPCR.BIT.BIT3
#define	CPHA		_SPCR.BIT.BIT2
#define	SPR1		_SPCR.BIT.BIT1
#define	SPR0		_SPCR.BIT.BIT0

#define	GPIOR2		_GPIOR2.ALL
#define	GPIOR27		_GPIOR2.BIT.BIT7
#define	GPIOR26		_GPIOR2.BIT.BIT6
#define	GPIOR25		_GPIOR2.BIT.BIT5
#define	GPIOR24		_GPIOR2.BIT.BIT4
#define	GPIOR23		_GPIOR2.BIT.BIT3
#define	GPIOR22		_GPIOR2.BIT.BIT2
#define	GPIOR21		_GPIOR2.BIT.BIT1
#define	GPIOR20		_GPIOR2.BIT.BIT0

#define	GPIOR1		_GPIOR1.ALL
#define	GPIOR17		_GPIOR1.BIT.BIT7
#define	GPIOR16		_GPIOR1.BIT.BIT6
#define	GPIOR15		_GPIOR1.BIT.BIT5
#define	GPIOR14		_GPIOR1.BIT.BIT4
#define	GPIOR13		_GPIOR1.BIT.BIT3
#define	GPIOR12		_GPIOR1.BIT.BIT2
#define	GPIOR11		_GPIOR1.BIT.BIT1
#define	GPIOR10		_GPIOR1.BIT.BIT0

#define	OCR0A		_OCR0A.ALL
#define	OCR0A7		_OCR0A.BIT.BIT7
#define	OCR0A6		_OCR0A.BIT.BIT6
#define	OCR0A5		_OCR0A.BIT.BIT5
#define	OCR0A4		_OCR0A.BIT.BIT4
#define	OCR0A3		_OCR0A.BIT.BIT3
#define	OCR0A2		_OCR0A.BIT.BIT2
#define	OCR0A1		_OCR0A.BIT.BIT1
#define	OCR0A0		_OCR0A.BIT.BIT0

#define	TCNT0		_TCNT0.ALL
#define	TCNT07		_TCNT0.BIT.BIT7
#define	TCNT06		_TCNT0.BIT.BIT6
#define	TCNT05		_TCNT0.BIT.BIT5
#define	TCNT04		_TCNT0.BIT.BIT4
#define	TCNT03		_TCNT0.BIT.BIT3
#define	TCNT02		_TCNT0.BIT.BIT2
#define	TCNT01		_TCNT0.BIT.BIT1
#define	TCNT00		_TCNT0.BIT.BIT0

#define	TCCR0A		_TCCR0A.ALL
#define	FOC0A		_TCCR0A.BIT.BIT7
#define	WGM00		_TCCR0A.BIT.BIT6
#define	COM0A1		_TCCR0A.BIT.BIT5
#define	COM0A0		_TCCR0A.BIT.BIT4
#define	WGM01		_TCCR0A.BIT.BIT3
#define	CS02		_TCCR0A.BIT.BIT2
#define	CS01		_TCCR0A.BIT.BIT1
#define	CS00		_TCCR0A.BIT.BIT0

#define	GTCCR		_GTCCR.ALL
#define	TSM			_GTCCR.BIT.BIT7
#define	PSR2		_GTCCR.BIT.BIT1
#define	PSR310		_GTCCR.BIT.BIT0

#define	EEARH		_EEARH.ALL
#define	EEAR11		_EEARH.BIT.BIT3
#define	EEAR10		_EEARH.BIT.BIT2
#define	EEAR9		_EEARH.BIT.BIT1
#define	EEAR8		_EEARH.BIT.BIT0

#define	EEARL		_EEARL.ALL
#define	EEAR7		_EEARL.BIT.BIT7
#define	EEAR6		_EEARL.BIT.BIT6
#define	EEAR5		_EEARL.BIT.BIT5
#define	EEAR4		_EEARL.BIT.BIT4
#define	EEAR3		_EEARL.BIT.BIT3
#define	EEAR2		_EEARL.BIT.BIT2
#define	EEAR1		_EEARL.BIT.BIT1
#define	EEAR0		_EEARL.BIT.BIT0

#define	EEDR		_EEDR.ALL
#define	EEDR7		_EEDR.BIT.BIT7
#define	EEDR6		_EEDR.BIT.BIT6
#define	EEDR5		_EEDR.BIT.BIT5
#define	EEDR4		_EEDR.BIT.BIT4
#define	EEDR3		_EEDR.BIT.BIT3
#define	EEDR2		_EEDR.BIT.BIT2
#define	EEDR1		_EEDR.BIT.BIT1
#define	EEDR0		_EEDR.BIT.BIT0

#define	EECR		_EECR.ALL
#define	EERIE		_EECR.BIT.BIT3
#define	EEMWE		_EECR.BIT.BIT2
#define	EEWE		_EECR.BIT.BIT1
#define	EERE		_EECR.BIT.BIT0

#define	GPIOR0		_GPIOR0.ALL
#define	GPIOR07		_GPIOR0.BIT.BIT7
#define	GPIOR06		_GPIOR0.BIT.BIT6
#define	GPIOR05		_GPIOR0.BIT.BIT5
#define	GPIOR04		_GPIOR0.BIT.BIT4
#define	GPIOR03		_GPIOR0.BIT.BIT3
#define	GPIOR02		_GPIOR0.BIT.BIT2
#define	GPIOR01		_GPIOR0.BIT.BIT1
#define	GPIOR00		_GPIOR0.BIT.BIT0

#define	EIMSK		_EIMSK.ALL
#define	INT7		_EIMSK.BIT.BIT7
#define	INT6		_EIMSK.BIT.BIT6
#define	INT5		_EIMSK.BIT.BIT5
#define	INT4		_EIMSK.BIT.BIT4
#define	INT3		_EIMSK.BIT.BIT3
#define	INT2		_EIMSK.BIT.BIT2
#define	INT1		_EIMSK.BIT.BIT1
#define	INT0		_EIMSK.BIT.BIT0

#define	EIFR		_EIFR.ALL
#define	INTF7		_EIFR.BIT.BIT7
#define	INTF6		_EIFR.BIT.BIT6
#define	INTF5		_EIFR.BIT.BIT5
#define	INTF4		_EIFR.BIT.BIT4
#define	INTF3		_EIFR.BIT.BIT3
#define	INTF2		_EIFR.BIT.BIT2
#define	INTF1		_EIFR.BIT.BIT1
#define	INTF0		_EIFR.BIT.BIT0

#define	TIFR3		_TIFR3.ALL
#define	ICF3		_TIFR3.BIT.BIT5
#define	OCF3C		_TIFR3.BIT.BIT3
#define	OCF3B		_TIFR3.BIT.BIT2
#define	OCF3A		_TIFR3.BIT.BIT1
#define	TOV3		_TIFR3.BIT.BIT0

#define	TIFR2		_TIFR2.ALL
#define	OCF2A		_TIFR2.BIT.BIT1
#define	TOV2		_TIFR2.BIT.BIT0

#define	TIFR1		_TIFR1.ALL
#define	ICF1		_TIFR1.BIT.BIT5
#define	OCF1C		_TIFR1.BIT.BIT3
#define	OCF1B		_TIFR1.BIT.BIT2
#define	OCF1A		_TIFR1.BIT.BIT1
#define	TOV1		_TIFR1.BIT.BIT0

#define	TIFR0		_TIFR0.ALL
#define	OCF0A		_TIFR0.BIT.BIT1
#define	TOV0		_TIFR0.BIT.BIT0

#define	PORTG		_PORTG.ALL
#define	PORTG4		_PORTG.BIT.BIT4
#define	PORTG3		_PORTG.BIT.BIT3
#define	PORTG2		_PORTG.BIT.BIT2
#define	PORTG1		_PORTG.BIT.BIT1
#define	PORTG0		_PORTG.BIT.BIT0

#define	DDRG		_DDRG.ALL
#define	DDG4		_DDRG.BIT.BIT4
#define	DDG3		_DDRG.BIT.BIT3
#define	DDG2		_DDRG.BIT.BIT2
#define	DDG1		_DDRG.BIT.BIT1
#define	DDG0		_DDRG.BIT.BIT0

#define	PING		_PING.ALL
#define	PING4		_PING.BIT.BIT4
#define	PING3		_PING.BIT.BIT3
#define	PING2		_PING.BIT.BIT2
#define	PING1		_PING.BIT.BIT1
#define	PING0		_PING.BIT.BIT0

#define	PORTF		_PORTF.ALL
#define	PORTF7		_PORTF.BIT.BIT7
#define	PORTF6		_PORTF.BIT.BIT6
#define	PORTF5		_PORTF.BIT.BIT5
#define	PORTF4		_PORTF.BIT.BIT4
#define	PORTF3		_PORTF.BIT.BIT3
#define	PORTF2		_PORTF.BIT.BIT2
#define	PORTF1		_PORTF.BIT.BIT1
#define	PORTF0		_PORTF.BIT.BIT0

#define	DDRF		_DDRF.ALL
#define	DDF7		_DDRF.BIT.BIT7
#define	DDF6		_DDRF.BIT.BIT6
#define	DDF5		_DDRF.BIT.BIT5
#define	DDF4		_DDRF.BIT.BIT4
#define	DDF3		_DDRF.BIT.BIT3
#define	DDF2		_DDRF.BIT.BIT2
#define	DDF1		_DDRF.BIT.BIT1
#define	DDF0		_DDRF.BIT.BIT0

#define	PINF		_PINF.ALL
#define	PINF7		_PINF.BIT.BIT7
#define	PINF6		_PINF.BIT.BIT6
#define	PINF5		_PINF.BIT.BIT5
#define	PINF4		_PINF.BIT.BIT4
#define	PINF3		_PINF.BIT.BIT3
#define	PINF2		_PINF.BIT.BIT2
#define	PINF1		_PINF.BIT.BIT1
#define	PINF0		_PINF.BIT.BIT0

#define	PORTE		_PORTE.ALL
#define	PORTE7		_PORTE.BIT.BIT7
#define	PORTE6		_PORTE.BIT.BIT6
#define	PORTE5		_PORTE.BIT.BIT5
#define	PORTE4		_PORTE.BIT.BIT4
#define	PORTE3		_PORTE.BIT.BIT3
#define	PORTE2		_PORTE.BIT.BIT2
#define	PORTE1		_PORTE.BIT.BIT1
#define	PORTE0		_PORTE.BIT.BIT0

#define	DDRE		_DDRE.ALL
#define	DDE7		_DDRE.BIT.BIT7
#define	DDE6		_DDRE.BIT.BIT6
#define	DDE5		_DDRE.BIT.BIT5
#define	DDE4		_DDRE.BIT.BIT4
#define	DDE3		_DDRE.BIT.BIT3
#define	DDE2		_DDRE.BIT.BIT2
#define	DDE1		_DDRE.BIT.BIT1
#define	DDE0		_DDRE.BIT.BIT0

#define	PINE		_PINE.ALL
#define	PINE7		_PINE.BIT.BIT7
#define	PINE6		_PINE.BIT.BIT6
#define	PINE5		_PINE.BIT.BIT5
#define	PINE4		_PINE.BIT.BIT4
#define	PINE3		_PINE.BIT.BIT3
#define	PINE2		_PINE.BIT.BIT2
#define	PINE1		_PINE.BIT.BIT1
#define	PINE0		_PINE.BIT.BIT0

#define	PORTD		_PORTD.ALL
#define	PORTD7		_PORTD.BIT.BIT7
#define	PORTD6		_PORTD.BIT.BIT6
#define	PORTD5		_PORTD.BIT.BIT5
#define	PORTD4		_PORTD.BIT.BIT4
#define	PORTD3		_PORTD.BIT.BIT3
#define	PORTD2		_PORTD.BIT.BIT2
#define	PORTD1		_PORTD.BIT.BIT1
#define	PORTD0		_PORTD.BIT.BIT0

#define	DDRD		_DDRD.ALL
#define	DDD7		_DDRD.BIT.BIT7
#define	DDD6		_DDRD.BIT.BIT6
#define	DDD5		_DDRD.BIT.BIT5
#define	DDD4		_DDRD.BIT.BIT4
#define	DDD3		_DDRD.BIT.BIT3
#define	DDD2		_DDRD.BIT.BIT2
#define	DDD1		_DDRD.BIT.BIT1
#define	DDD0		_DDRD.BIT.BIT0

#define	PIND		_PIND.ALL
#define	PIND7		_PIND.BIT.BIT7
#define	PIND6		_PIND.BIT.BIT6
#define	PIND5		_PIND.BIT.BIT5
#define	PIND4		_PIND.BIT.BIT4
#define	PIND3		_PIND.BIT.BIT3
#define	PIND2		_PIND.BIT.BIT2
#define	PIND1		_PIND.BIT.BIT1
#define	PIND0		_PIND.BIT.BIT0

#define	PORTC		_PORTC.ALL
#define	PORTC7		_PORTC.BIT.BIT7
#define	PORTC6		_PORTC.BIT.BIT6
#define	PORTC5		_PORTC.BIT.BIT5
#define	PORTC4		_PORTC.BIT.BIT4
#define	PORTC3		_PORTC.BIT.BIT3
#define	PORTC2		_PORTC.BIT.BIT2
#define	PORTC1		_PORTC.BIT.BIT1
#define	PORTC0		_PORTC.BIT.BIT0

#define	DDRC		_DDRC.ALL
#define	DDC7		_DDRC.BIT.BIT7
#define	DDC6		_DDRC.BIT.BIT6
#define	DDC5		_DDRC.BIT.BIT5
#define	DDC4		_DDRC.BIT.BIT4
#define	DDC3		_DDRC.BIT.BIT3
#define	DDC2		_DDRC.BIT.BIT2
#define	DDC1		_DDRC.BIT.BIT1
#define	DDC0		_DDRC.BIT.BIT0

#define	PINC		_PINC.ALL
#define	PINC7		_PINC.BIT.BIT7
#define	PINC6		_PINC.BIT.BIT6
#define	PINC5		_PINC.BIT.BIT5
#define	PINC4		_PINC.BIT.BIT4
#define	PINC3		_PINC.BIT.BIT3
#define	PINC2		_PINC.BIT.BIT2
#define	PINC1		_PINC.BIT.BIT1
#define	PINC0		_PINC.BIT.BIT0

#define	PORTB		_PORTB.ALL
#define	PORTB7		_PORTB.BIT.BIT7
#define	PORTB6		_PORTB.BIT.BIT6
#define	PORTB5		_PORTB.BIT.BIT5
#define	PORTB4		_PORTB.BIT.BIT4
#define	PORTB3		_PORTB.BIT.BIT3
#define	PORTB2		_PORTB.BIT.BIT2
#define	PORTB1		_PORTB.BIT.BIT1
#define	PORTB0		_PORTB.BIT.BIT0

#define	DDRB		_DDRB.ALL
#define	DDB7		_DDRB.BIT.BIT7
#define	DDB6		_DDRB.BIT.BIT6
#define	DDB5		_DDRB.BIT.BIT5
#define	DDB4		_DDRB.BIT.BIT4
#define	DDB3		_DDRB.BIT.BIT3
#define	DDB2		_DDRB.BIT.BIT2
#define	DDB1		_DDRB.BIT.BIT1
#define	DDB0		_DDRB.BIT.BIT0

#define	PINB		_PINB.ALL
#define	PINB7		_PINB.BIT.BIT7
#define	PINB6		_PINB.BIT.BIT6
#define	PINB5		_PINB.BIT.BIT5
#define	PINB4		_PINB.BIT.BIT4
#define	PINB3		_PINB.BIT.BIT3
#define	PINB2		_PINB.BIT.BIT2
#define	PINB1		_PINB.BIT.BIT1
#define	PINB0		_PINB.BIT.BIT0

#define	PORTA		_PORTA.ALL
#define	PORTA7		_PORTA.BIT.BIT7
#define	PORTA6		_PORTA.BIT.BIT6
#define	PORTA5		_PORTA.BIT.BIT5
#define	PORTA4		_PORTA.BIT.BIT4
#define	PORTA3		_PORTA.BIT.BIT3
#define	PORTA2		_PORTA.BIT.BIT2
#define	PORTA1		_PORTA.BIT.BIT1
#define	PORTA0		_PORTA.BIT.BIT0

#define	DDRA		_DDRA.ALL
#define	DDA7		_DDRA.BIT.BIT7
#define	DDA6		_DDRA.BIT.BIT6
#define	DDA5		_DDRA.BIT.BIT5
#define	DDA4		_DDRA.BIT.BIT4
#define	DDA3		_DDRA.BIT.BIT3
#define	DDA2		_DDRA.BIT.BIT2
#define	DDA1		_DDRA.BIT.BIT1
#define	DDA0		_DDRA.BIT.BIT0

#define	PINA		_PINA.ALL
#define	PINA7		_PINA.BIT.BIT7
#define	PINA6		_PINA.BIT.BIT6
#define	PINA5		_PINA.BIT.BIT5
#define	PINA4		_PINA.BIT.BIT4
#define	PINA3		_PINA.BIT.BIT3
#define	PINA2		_PINA.BIT.BIT2
#define	PINA1		_PINA.BIT.BIT1
#define	PINA0		_PINA.BIT.BIT0



//========  Interrupt Vector Definitions =====================


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

/* Timer/Counter1 Compare Match C */
#define TIMER1_COMPC_vect		_VECTOR(14)
#define SIG_OUTPUT_COMPARE1C		_VECTOR(14)

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			_VECTOR(15)
#define SIG_OVERFLOW1			_VECTOR(15)

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect		_VECTOR(16)
#define SIG_OUTPUT_COMPARE0		_VECTOR(16)

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect			_VECTOR(17)
#define SIG_OVERFLOW0			_VECTOR(17)

/* CAN Transfer Complete or Error */
#define CANIT_vect			_VECTOR(18)
#define SIG_CAN_INTERRUPT1		_VECTOR(18)

/* CAN Timer Overrun */
#define OVRIT_vect			_VECTOR(19)
#define SIG_CAN_OVERFLOW1		_VECTOR(19)

/* SPI Serial Transfer Complete */
#define SPI_STC_vect			_VECTOR(20)
#define SIG_SPI				_VECTOR(20)

/* USART0, Rx Complete */
#define USART0_RX_vect			_VECTOR(21)
#define SIG_UART0_RECV			_VECTOR(21)
#define SIG_USART0_RECV			_VECTOR(21)

/* USART0 Data Register Empty */
#define USART0_UDRE_vect		_VECTOR(22)
#define SIG_UART0_DATA			_VECTOR(22)
#define SIG_USART0_DATA			_VECTOR(22)

/* USART0, Tx Complete */
#define USART0_TX_vect			_VECTOR(23)
#define SIG_UART0_TRANS			_VECTOR(23)
#define SIG_USART0_TRANS		_VECTOR(23)

/* Analog Comparator */
#define ANALOG_COMP_vect		_VECTOR(24)
#define SIG_COMPARATOR			_VECTOR(24)

/* ADC Conversion Complete */
#define ADC_vect			_VECTOR(25)
#define SIG_ADC				_VECTOR(25)

/* EEPROM Ready */
#define EE_READY_vect			_VECTOR(26)
#define SIG_EEPROM_READY		_VECTOR(26)

/* Timer/Counter3 Capture Event */
#define TIMER3_CAPT_vect		_VECTOR(27)
#define SIG_INPUT_CAPTURE3		_VECTOR(27)

/* Timer/Counter3 Compare Match A */
#define TIMER3_COMPA_vect		_VECTOR(28)
#define SIG_OUTPUT_COMPARE3A		_VECTOR(28)

/* Timer/Counter3 Compare Match B */
#define TIMER3_COMPB_vect		_VECTOR(29)
#define SIG_OUTPUT_COMPARE3B		_VECTOR(29)

/* Timer/Counter3 Compare Match C */
#define TIMER3_COMPC_vect		_VECTOR(30)
#define SIG_OUTPUT_COMPARE3C		_VECTOR(30)

/* Timer/Counter3 Overflow */
#define TIMER3_OVF_vect			_VECTOR(31)
#define SIG_OVERFLOW3			_VECTOR(31)

/* USART1, Rx Complete */
#define USART1_RX_vect			_VECTOR(32)
#define SIG_UART1_RECV			_VECTOR(32)
#define SIG_USART1_RECV			_VECTOR(32)

/* USART1, Data Register Empty */
#define USART1_UDRE_vect		_VECTOR(33)
#define SIG_UART1_DATA			_VECTOR(33)
#define SIG_USART1_DATA			_VECTOR(33)

/* USART1, Tx Complete */
#define USART1_TX_vect			_VECTOR(34)
#define SIG_UART1_TRANS			_VECTOR(34)
#define SIG_USART1_TRANS		_VECTOR(34)

/* 2-wire Serial Interface */
#define TWI_vect			_VECTOR(35)
#define SIG_2WIRE_SERIAL		_VECTOR(35)

/* Store Program Memory Read */
#define SPM_READY_vect			_VECTOR(36)
#define SIG_SPM_READY			_VECTOR(36)

#define _VECTORS_SIZE 148




#endif
