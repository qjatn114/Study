
;CodeVisionAVR C Compiler V2.05.0 Professional
;(C) Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
;http://www.hpinfotech.com

;Chip type                : ATmega128
;Program type             : Application
;Clock frequency          : 4.000000 MHz
;Memory model             : Small
;Optimize for             : Size
;(s)printf features       : int, width
;(s)scanf features        : int, width
;External RAM size        : 0
;Data Stack size          : 1024 byte(s)
;Heap size                : 0 byte(s)
;Promote 'char' to 'int'  : No
;'char' is unsigned       : Yes
;8 bit enums              : Yes
;global 'const' stored in FLASH: Yes
;Enhanced core instructions    : On
;Smart register allocation     : On
;Automatic register allocation : On

	#pragma AVRPART ADMIN PART_NAME ATmega128
	#pragma AVRPART MEMORY PROG_FLASH 131072
	#pragma AVRPART MEMORY EEPROM 4096
	#pragma AVRPART MEMORY INT_SRAM SIZE 4351
	#pragma AVRPART MEMORY INT_SRAM START_ADDR 0x100

	#define CALL_SUPPORTED 1

	.LISTMAC
	.EQU UDRE=0x5
	.EQU RXC=0x7
	.EQU USR=0xB
	.EQU UDR=0xC
	.EQU SPSR=0xE
	.EQU SPDR=0xF
	.EQU EERE=0x0
	.EQU EEWE=0x1
	.EQU EEMWE=0x2
	.EQU EECR=0x1C
	.EQU EEDR=0x1D
	.EQU EEARL=0x1E
	.EQU EEARH=0x1F
	.EQU WDTCR=0x21
	.EQU MCUCR=0x35
	.EQU RAMPZ=0x3B
	.EQU SPL=0x3D
	.EQU SPH=0x3E
	.EQU SREG=0x3F
	.EQU XMCRA=0x6D
	.EQU XMCRB=0x6C

	.DEF R0X0=R0
	.DEF R0X1=R1
	.DEF R0X2=R2
	.DEF R0X3=R3
	.DEF R0X4=R4
	.DEF R0X5=R5
	.DEF R0X6=R6
	.DEF R0X7=R7
	.DEF R0X8=R8
	.DEF R0X9=R9
	.DEF R0XA=R10
	.DEF R0XB=R11
	.DEF R0XC=R12
	.DEF R0XD=R13
	.DEF R0XE=R14
	.DEF R0XF=R15
	.DEF R0X10=R16
	.DEF R0X11=R17
	.DEF R0X12=R18
	.DEF R0X13=R19
	.DEF R0X14=R20
	.DEF R0X15=R21
	.DEF R0X16=R22
	.DEF R0X17=R23
	.DEF R0X18=R24
	.DEF R0X19=R25
	.DEF R0X1A=R26
	.DEF R0X1B=R27
	.DEF R0X1C=R28
	.DEF R0X1D=R29
	.DEF R0X1E=R30
	.DEF R0X1F=R31

	.EQU __SRAM_START=0x0100
	.EQU __SRAM_END=0x10FF
	.EQU __DSTACK_SIZE=0x0400
	.EQU __HEAP_SIZE=0x0000
	.EQU __CLEAR_SRAM_SIZE=__SRAM_END-__SRAM_START+1

	.MACRO __CPD1N
	CPI  R30,LOW(@0)
	LDI  R26,HIGH(@0)
	CPC  R31,R26
	LDI  R26,BYTE3(@0)
	CPC  R22,R26
	LDI  R26,BYTE4(@0)
	CPC  R23,R26
	.ENDM

	.MACRO __CPD2N
	CPI  R26,LOW(@0)
	LDI  R30,HIGH(@0)
	CPC  R27,R30
	LDI  R30,BYTE3(@0)
	CPC  R24,R30
	LDI  R30,BYTE4(@0)
	CPC  R25,R30
	.ENDM

	.MACRO __CPWRR
	CP   R@0,R@2
	CPC  R@1,R@3
	.ENDM

	.MACRO __CPWRN
	CPI  R@0,LOW(@2)
	LDI  R30,HIGH(@2)
	CPC  R@1,R30
	.ENDM

	.MACRO __ADDB1MN
	SUBI R30,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDB2MN
	SUBI R26,LOW(-@0-(@1))
	.ENDM

	.MACRO __ADDW1MN
	SUBI R30,LOW(-@0-(@1))
	SBCI R31,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW2MN
	SUBI R26,LOW(-@0-(@1))
	SBCI R27,HIGH(-@0-(@1))
	.ENDM

	.MACRO __ADDW1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1FN
	SUBI R30,LOW(-2*@0-(@1))
	SBCI R31,HIGH(-2*@0-(@1))
	SBCI R22,BYTE3(-2*@0-(@1))
	.ENDM

	.MACRO __ADDD1N
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	SBCI R22,BYTE3(-@0)
	SBCI R23,BYTE4(-@0)
	.ENDM

	.MACRO __ADDD2N
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	SBCI R24,BYTE3(-@0)
	SBCI R25,BYTE4(-@0)
	.ENDM

	.MACRO __SUBD1N
	SUBI R30,LOW(@0)
	SBCI R31,HIGH(@0)
	SBCI R22,BYTE3(@0)
	SBCI R23,BYTE4(@0)
	.ENDM

	.MACRO __SUBD2N
	SUBI R26,LOW(@0)
	SBCI R27,HIGH(@0)
	SBCI R24,BYTE3(@0)
	SBCI R25,BYTE4(@0)
	.ENDM

	.MACRO __ANDBMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ANDWMNN
	LDS  R30,@0+(@1)
	ANDI R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ANDI R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ANDD1N
	ANDI R30,LOW(@0)
	ANDI R31,HIGH(@0)
	ANDI R22,BYTE3(@0)
	ANDI R23,BYTE4(@0)
	.ENDM

	.MACRO __ANDD2N
	ANDI R26,LOW(@0)
	ANDI R27,HIGH(@0)
	ANDI R24,BYTE3(@0)
	ANDI R25,BYTE4(@0)
	.ENDM

	.MACRO __ORBMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	.ENDM

	.MACRO __ORWMNN
	LDS  R30,@0+(@1)
	ORI  R30,LOW(@2)
	STS  @0+(@1),R30
	LDS  R30,@0+(@1)+1
	ORI  R30,HIGH(@2)
	STS  @0+(@1)+1,R30
	.ENDM

	.MACRO __ORD1N
	ORI  R30,LOW(@0)
	ORI  R31,HIGH(@0)
	ORI  R22,BYTE3(@0)
	ORI  R23,BYTE4(@0)
	.ENDM

	.MACRO __ORD2N
	ORI  R26,LOW(@0)
	ORI  R27,HIGH(@0)
	ORI  R24,BYTE3(@0)
	ORI  R25,BYTE4(@0)
	.ENDM

	.MACRO __DELAY_USB
	LDI  R24,LOW(@0)
__DELAY_USB_LOOP:
	DEC  R24
	BRNE __DELAY_USB_LOOP
	.ENDM

	.MACRO __DELAY_USW
	LDI  R24,LOW(@0)
	LDI  R25,HIGH(@0)
__DELAY_USW_LOOP:
	SBIW R24,1
	BRNE __DELAY_USW_LOOP
	.ENDM

	.MACRO __GETD1S
	LDD  R30,Y+@0
	LDD  R31,Y+@0+1
	LDD  R22,Y+@0+2
	LDD  R23,Y+@0+3
	.ENDM

	.MACRO __GETD2S
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	LDD  R24,Y+@0+2
	LDD  R25,Y+@0+3
	.ENDM

	.MACRO __PUTD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R31
	STD  Y+@0+2,R22
	STD  Y+@0+3,R23
	.ENDM

	.MACRO __PUTD2S
	STD  Y+@0,R26
	STD  Y+@0+1,R27
	STD  Y+@0+2,R24
	STD  Y+@0+3,R25
	.ENDM

	.MACRO __PUTDZ2
	STD  Z+@0,R26
	STD  Z+@0+1,R27
	STD  Z+@0+2,R24
	STD  Z+@0+3,R25
	.ENDM

	.MACRO __CLRD1S
	STD  Y+@0,R30
	STD  Y+@0+1,R30
	STD  Y+@0+2,R30
	STD  Y+@0+3,R30
	.ENDM

	.MACRO __POINTB1MN
	LDI  R30,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW1MN
	LDI  R30,LOW(@0+(@1))
	LDI  R31,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTD1M
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __POINTW1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	.ENDM

	.MACRO __POINTD1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	LDI  R22,BYTE3(2*@0+(@1))
	LDI  R23,BYTE4(2*@0+(@1))
	.ENDM

	.MACRO __POINTB2MN
	LDI  R26,LOW(@0+(@1))
	.ENDM

	.MACRO __POINTW2MN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	.ENDM

	.MACRO __POINTBRM
	LDI  R@0,LOW(@1)
	.ENDM

	.MACRO __POINTWRM
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __POINTBRMN
	LDI  R@0,LOW(@1+(@2))
	.ENDM

	.MACRO __POINTWRMN
	LDI  R@0,LOW(@2+(@3))
	LDI  R@1,HIGH(@2+(@3))
	.ENDM

	.MACRO __POINTWRFN
	LDI  R@0,LOW(@2*2+(@3))
	LDI  R@1,HIGH(@2*2+(@3))
	.ENDM

	.MACRO __GETD1N
	LDI  R30,LOW(@0)
	LDI  R31,HIGH(@0)
	LDI  R22,BYTE3(@0)
	LDI  R23,BYTE4(@0)
	.ENDM

	.MACRO __GETD2N
	LDI  R26,LOW(@0)
	LDI  R27,HIGH(@0)
	LDI  R24,BYTE3(@0)
	LDI  R25,BYTE4(@0)
	.ENDM

	.MACRO __GETB1MN
	LDS  R30,@0+(@1)
	.ENDM

	.MACRO __GETB1HMN
	LDS  R31,@0+(@1)
	.ENDM

	.MACRO __GETW1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	.ENDM

	.MACRO __GETD1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	LDS  R22,@0+(@1)+2
	LDS  R23,@0+(@1)+3
	.ENDM

	.MACRO __GETBRMN
	LDS  R@0,@1+(@2)
	.ENDM

	.MACRO __GETWRMN
	LDS  R@0,@2+(@3)
	LDS  R@1,@2+(@3)+1
	.ENDM

	.MACRO __GETWRZ
	LDD  R@0,Z+@2
	LDD  R@1,Z+@2+1
	.ENDM

	.MACRO __GETD2Z
	LDD  R26,Z+@0
	LDD  R27,Z+@0+1
	LDD  R24,Z+@0+2
	LDD  R25,Z+@0+3
	.ENDM

	.MACRO __GETB2MN
	LDS  R26,@0+(@1)
	.ENDM

	.MACRO __GETW2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	.ENDM

	.MACRO __GETD2MN
	LDS  R26,@0+(@1)
	LDS  R27,@0+(@1)+1
	LDS  R24,@0+(@1)+2
	LDS  R25,@0+(@1)+3
	.ENDM

	.MACRO __PUTB1MN
	STS  @0+(@1),R30
	.ENDM

	.MACRO __PUTW1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	.ENDM

	.MACRO __PUTD1MN
	STS  @0+(@1),R30
	STS  @0+(@1)+1,R31
	STS  @0+(@1)+2,R22
	STS  @0+(@1)+3,R23
	.ENDM

	.MACRO __PUTB1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRB
	.ENDM

	.MACRO __PUTW1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRW
	.ENDM

	.MACRO __PUTD1EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMWRD
	.ENDM

	.MACRO __PUTBR0MN
	STS  @0+(@1),R0
	.ENDM

	.MACRO __PUTBMRN
	STS  @0+(@1),R@2
	.ENDM

	.MACRO __PUTWMRN
	STS  @0+(@1),R@2
	STS  @0+(@1)+1,R@3
	.ENDM

	.MACRO __PUTBZR
	STD  Z+@1,R@0
	.ENDM

	.MACRO __PUTWZR
	STD  Z+@2,R@0
	STD  Z+@2+1,R@1
	.ENDM

	.MACRO __GETW1R
	MOV  R30,R@0
	MOV  R31,R@1
	.ENDM

	.MACRO __GETW2R
	MOV  R26,R@0
	MOV  R27,R@1
	.ENDM

	.MACRO __GETWRN
	LDI  R@0,LOW(@2)
	LDI  R@1,HIGH(@2)
	.ENDM

	.MACRO __PUTW1R
	MOV  R@0,R30
	MOV  R@1,R31
	.ENDM

	.MACRO __PUTW2R
	MOV  R@0,R26
	MOV  R@1,R27
	.ENDM

	.MACRO __ADDWRN
	SUBI R@0,LOW(-@2)
	SBCI R@1,HIGH(-@2)
	.ENDM

	.MACRO __ADDWRR
	ADD  R@0,R@2
	ADC  R@1,R@3
	.ENDM

	.MACRO __SUBWRN
	SUBI R@0,LOW(@2)
	SBCI R@1,HIGH(@2)
	.ENDM

	.MACRO __SUBWRR
	SUB  R@0,R@2
	SBC  R@1,R@3
	.ENDM

	.MACRO __ANDWRN
	ANDI R@0,LOW(@2)
	ANDI R@1,HIGH(@2)
	.ENDM

	.MACRO __ANDWRR
	AND  R@0,R@2
	AND  R@1,R@3
	.ENDM

	.MACRO __ORWRN
	ORI  R@0,LOW(@2)
	ORI  R@1,HIGH(@2)
	.ENDM

	.MACRO __ORWRR
	OR   R@0,R@2
	OR   R@1,R@3
	.ENDM

	.MACRO __EORWRR
	EOR  R@0,R@2
	EOR  R@1,R@3
	.ENDM

	.MACRO __GETWRS
	LDD  R@0,Y+@2
	LDD  R@1,Y+@2+1
	.ENDM

	.MACRO __PUTBSR
	STD  Y+@1,R@0
	.ENDM

	.MACRO __PUTWSR
	STD  Y+@2,R@0
	STD  Y+@2+1,R@1
	.ENDM

	.MACRO __MOVEWRR
	MOV  R@0,R@2
	MOV  R@1,R@3
	.ENDM

	.MACRO __INWR
	IN   R@0,@2
	IN   R@1,@2+1
	.ENDM

	.MACRO __OUTWR
	OUT  @2+1,R@1
	OUT  @2,R@0
	.ENDM

	.MACRO __CALL1MN
	LDS  R30,@0+(@1)
	LDS  R31,@0+(@1)+1
	ICALL
	.ENDM

	.MACRO __CALL1FN
	LDI  R30,LOW(2*@0+(@1))
	LDI  R31,HIGH(2*@0+(@1))
	CALL __GETW1PF
	ICALL
	.ENDM

	.MACRO __CALL2EN
	LDI  R26,LOW(@0+(@1))
	LDI  R27,HIGH(@0+(@1))
	CALL __EEPROMRDW
	ICALL
	.ENDM

	.MACRO __GETW1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X
	.ENDM

	.MACRO __GETD1STACK
	IN   R26,SPL
	IN   R27,SPH
	ADIW R26,@0+1
	LD   R30,X+
	LD   R31,X+
	LD   R22,X
	.ENDM

	.MACRO __NBST
	BST  R@0,@1
	IN   R30,SREG
	LDI  R31,0x40
	EOR  R30,R31
	OUT  SREG,R30
	.ENDM


	.MACRO __PUTB1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SN
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNS
	LDD  R26,Y+@0
	LDD  R27,Y+@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMN
	LDS  R26,@0
	LDS  R27,@0+1
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1PMNS
	LDS  R26,@0
	LDS  R27,@0+1
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RN
	MOVW R26,R@0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RNS
	MOVW R26,R@0
	ADIW R26,@1
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RNS
	MOVW R26,R@0
	ADIW R26,@1
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RON
	MOV  R26,R@0
	MOV  R27,R@1
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	CALL __PUTDP1
	.ENDM

	.MACRO __PUTB1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X,R30
	.ENDM

	.MACRO __PUTW1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1RONS
	MOV  R26,R@0
	MOV  R27,R@1
	ADIW R26,@2
	CALL __PUTDP1
	.ENDM


	.MACRO __GETB1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R30,Z
	.ENDM

	.MACRO __GETB1HSX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	.ENDM

	.MACRO __GETW1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R31,Z
	MOV  R30,R0
	.ENDM

	.MACRO __GETD1SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R0,Z+
	LD   R1,Z+
	LD   R22,Z+
	LD   R23,Z
	MOVW R30,R0
	.ENDM

	.MACRO __GETB2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R26,X
	.ENDM

	.MACRO __GETW2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	.ENDM

	.MACRO __GETD2SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R1,X+
	LD   R24,X+
	LD   R25,X
	MOVW R26,R0
	.ENDM

	.MACRO __GETBRSX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	LD   R@0,Z
	.ENDM

	.MACRO __GETWRSX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	LD   R@0,Z+
	LD   R@1,Z
	.ENDM

	.MACRO __GETBRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	LD   R@0,X
	.ENDM

	.MACRO __GETWRSX2
	MOVW R26,R28
	SUBI R26,LOW(-@2)
	SBCI R27,HIGH(-@2)
	LD   R@0,X+
	LD   R@1,X
	.ENDM

	.MACRO __LSLW8SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	LD   R31,Z
	CLR  R30
	.ENDM

	.MACRO __PUTB1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __CLRW1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __CLRD1SX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	ST   X+,R30
	ST   X+,R30
	ST   X+,R30
	ST   X,R30
	.ENDM

	.MACRO __PUTB2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z,R26
	.ENDM

	.MACRO __PUTW2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z,R27
	.ENDM

	.MACRO __PUTD2SX
	MOVW R30,R28
	SUBI R30,LOW(-@0)
	SBCI R31,HIGH(-@0)
	ST   Z+,R26
	ST   Z+,R27
	ST   Z+,R24
	ST   Z,R25
	.ENDM

	.MACRO __PUTBSRX
	MOVW R30,R28
	SUBI R30,LOW(-@1)
	SBCI R31,HIGH(-@1)
	ST   Z,R@0
	.ENDM

	.MACRO __PUTWSRX
	MOVW R30,R28
	SUBI R30,LOW(-@2)
	SBCI R31,HIGH(-@2)
	ST   Z+,R@0
	ST   Z,R@1
	.ENDM

	.MACRO __PUTB1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X,R30
	.ENDM

	.MACRO __PUTW1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X,R31
	.ENDM

	.MACRO __PUTD1SNX
	MOVW R26,R28
	SUBI R26,LOW(-@0)
	SBCI R27,HIGH(-@0)
	LD   R0,X+
	LD   R27,X
	MOV  R26,R0
	SUBI R26,LOW(-@1)
	SBCI R27,HIGH(-@1)
	ST   X+,R30
	ST   X+,R31
	ST   X+,R22
	ST   X,R23
	.ENDM

	.MACRO __MULBRR
	MULS R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRRU
	MUL  R@0,R@1
	MOVW R30,R0
	.ENDM

	.MACRO __MULBRR0
	MULS R@0,R@1
	.ENDM

	.MACRO __MULBRRU0
	MUL  R@0,R@1
	.ENDM

	.MACRO __MULBNWRU
	LDI  R26,@2
	MUL  R26,R@0
	MOVW R30,R0
	MUL  R26,R@1
	ADD  R31,R0
	.ENDM

;NAME DEFINITIONS FOR GLOBAL VARIABLES ALLOCATED TO REGISTERS
	.DEF _time_count=R5
	.DEF _tmp_index=R4
	.DEF _lcd_mode=R7
	.DEF _count=R6

	.CSEG
	.ORG 0x00

;START OF CODE MARKER
__START_OF_CODE:

;INTERRUPT VECTORS
	JMP  __RESET
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00
	JMP  0x00

_tbl10_G100:
	.DB  0x10,0x27,0xE8,0x3,0x64,0x0,0xA,0x0
	.DB  0x1,0x0
_tbl16_G100:
	.DB  0x0,0x10,0x0,0x1,0x10,0x0,0x1,0x0

;REGISTER BIT VARIABLES INITIALIZATION
__REG_BIT_VARS:
	.DW  0x0000

_0x3:
	.DB  0x4D,0x45,0x47,0x41,0x31,0x32,0x38,0x20
_0x4:
	.DB  0x57,0x45,0x4C,0x43,0x4F,0x4D,0x45,0x3A
_0x5:
	.DB  0x43,0x4E,0x54,0x2D,0x55,0x50,0x3A,0x20
_0x6:
	.DB  0x45,0x41
_0x7:
	.DB  0x20,0x20,0x20,0x20,0x20,0x20,0x20

__GLOBAL_INI_TBL:
	.DW  0x01
	.DW  0x02
	.DW  __REG_BIT_VARS*2

	.DW  0x08
	.DW  _str_mega128
	.DW  _0x3*2

	.DW  0x08
	.DW  _str_welcome
	.DW  _0x4*2

	.DW  0x08
	.DW  _str_countup
	.DW  _0x5*2

	.DW  0x02
	.DW  _str_ea
	.DW  _0x6*2

_0xFFFFFFFF:
	.DW  0

__RESET:
	CLI
	CLR  R30
	OUT  EECR,R30

;INTERRUPT VECTORS ARE PLACED
;AT THE START OF FLASH
	LDI  R31,1
	OUT  MCUCR,R31
	OUT  MCUCR,R30
	STS  XMCRB,R30

;DISABLE WATCHDOG
	LDI  R31,0x18
	OUT  WDTCR,R31
	OUT  WDTCR,R30

;CLEAR R2-R14
	LDI  R24,(14-2)+1
	LDI  R26,2
	CLR  R27
__CLEAR_REG:
	ST   X+,R30
	DEC  R24
	BRNE __CLEAR_REG

;CLEAR SRAM
	LDI  R24,LOW(__CLEAR_SRAM_SIZE)
	LDI  R25,HIGH(__CLEAR_SRAM_SIZE)
	LDI  R26,LOW(__SRAM_START)
	LDI  R27,HIGH(__SRAM_START)
__CLEAR_SRAM:
	ST   X+,R30
	SBIW R24,1
	BRNE __CLEAR_SRAM

;GLOBAL VARIABLES INITIALIZATION
	LDI  R30,LOW(__GLOBAL_INI_TBL*2)
	LDI  R31,HIGH(__GLOBAL_INI_TBL*2)
__GLOBAL_INI_NEXT:
	LPM  R24,Z+
	LPM  R25,Z+
	SBIW R24,0
	BREQ __GLOBAL_INI_END
	LPM  R26,Z+
	LPM  R27,Z+
	LPM  R0,Z+
	LPM  R1,Z+
	MOVW R22,R30
	MOVW R30,R0
__GLOBAL_INI_LOOP:
	LPM  R0,Z+
	ST   X+,R0
	SBIW R24,1
	BRNE __GLOBAL_INI_LOOP
	MOVW R30,R22
	RJMP __GLOBAL_INI_NEXT
__GLOBAL_INI_END:

	OUT  RAMPZ,R24

;HARDWARE STACK POINTER INITIALIZATION
	LDI  R30,LOW(__SRAM_END-__HEAP_SIZE)
	OUT  SPL,R30
	LDI  R30,HIGH(__SRAM_END-__HEAP_SIZE)
	OUT  SPH,R30

;DATA STACK POINTER INITIALIZATION
	LDI  R28,LOW(__SRAM_START+__DSTACK_SIZE)
	LDI  R29,HIGH(__SRAM_START+__DSTACK_SIZE)

	JMP  _main

	.ESEG
	.ORG 0

	.DSEG
	.ORG 0x500

	.CSEG
;#include <mega128.h>
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
;#include <stdio.h>
;#include <delay.h>
;#include "mydef.h"
;#include "lcd.h"
;
;void update_lcd(void);
;void set_led(u08 n);
;u08 time_count;
;bit time_flag;
;u16 tmp_buf[10];
;u08 tmp_index;
;
;eeprom u08 eep_model=1;
;eeprom u32 eep_average_fuel=0;
;
;volatile u08 buzzer_count;
;
;u08 lcd_mode;
;u08 count;
;
;u08 str_mega128[] = "MEGA128 ";

	.DSEG
;u08 str_welcome[] = "WELCOME:";
;
;u08 str_countup[] = "CNT-UP: ";
;u08 str_ea[] = "EA";
;u08 str_blank[] = "       ";
;
;
;void set_led(u08 n) //ON, POSITION
; 0000 001F {

	.CSEG
_set_led:
; 0000 0020 	switch(n)
;	n -> Y+0
	LD   R30,Y
; 0000 0021 	{
; 0000 0022 	 case 0: PORTF = 0x00;  break;
	CPI  R30,0
	BRNE _0xB
	LDI  R30,LOW(0)
	STS  98,R30
	RJMP _0xA
; 0000 0023 	 case 1: PORTF = 0x01;  break;
_0xB:
	CPI  R30,LOW(0x1)
	BRNE _0xC
	LDI  R30,LOW(1)
	STS  98,R30
	RJMP _0xA
; 0000 0024 	 case 2: PORTF = 0x03;  break;
_0xC:
	CPI  R30,LOW(0x2)
	BRNE _0xD
	LDI  R30,LOW(3)
	STS  98,R30
	RJMP _0xA
; 0000 0025 	 case 3: PORTF = 0x07;  break;
_0xD:
	CPI  R30,LOW(0x3)
	BRNE _0xE
	LDI  R30,LOW(7)
	STS  98,R30
	RJMP _0xA
; 0000 0026 	 case 4: PORTF = 0x0F;	break;
_0xE:
	CPI  R30,LOW(0x4)
	BRNE _0xF
	LDI  R30,LOW(15)
	STS  98,R30
	RJMP _0xA
; 0000 0027 	 case 5: PORTF = 0x1F;	break;
_0xF:
	CPI  R30,LOW(0x5)
	BRNE _0x10
	LDI  R30,LOW(31)
	STS  98,R30
	RJMP _0xA
; 0000 0028 	 case 6: PORTF = 0x3F;  break;
_0x10:
	CPI  R30,LOW(0x6)
	BRNE _0x11
	LDI  R30,LOW(63)
	STS  98,R30
	RJMP _0xA
; 0000 0029 	 case 7: PORTF = 0x7F;  break;
_0x11:
	CPI  R30,LOW(0x7)
	BRNE _0x12
	LDI  R30,LOW(127)
	STS  98,R30
	RJMP _0xA
; 0000 002A 	 case 8: PORTF = 0xFF;  break;
_0x12:
	CPI  R30,LOW(0x8)
	BRNE _0x14
	LDI  R30,LOW(255)
	STS  98,R30
	RJMP _0xA
; 0000 002B 	 default: PORTD = 0x01; break;
_0x14:
	LDI  R30,LOW(1)
	OUT  0x12,R30
; 0000 002C 	}
_0xA:
; 0000 002D }
	RJMP _0x2060003
;void main(void)
; 0000 002F {
_main:
; 0000 0030 u08 i;
; 0000 0031 
; 0000 0032 	PORTA = 0x00;
;	i -> R17
	LDI  R30,LOW(0)
	OUT  0x1B,R30
; 0000 0033 	DDRA = 0x00;
	OUT  0x1A,R30
; 0000 0034 
; 0000 0035 	DDRB = 0x40; 		//INPUT MODE AND BUZZER = OUPUT
	LDI  R30,LOW(64)
	OUT  0x17,R30
; 0000 0036 	PORTB = 0x0F;           //PULL UP ON
	LDI  R30,LOW(15)
	OUT  0x18,R30
; 0000 0037 
; 0000 0038 	PORTC = 0x00;
	LDI  R30,LOW(0)
	OUT  0x15,R30
; 0000 0039 	DDRC = 0xFF;
	LDI  R30,LOW(255)
	OUT  0x14,R30
; 0000 003A 
; 0000 003B 	PORTD=0x00; //output all 0 ,PULL UP OFF
	LDI  R30,LOW(0)
	OUT  0x12,R30
; 0000 003C 	DDRD= (0x01<<7)|(0x01<<6)|(0x01<<5)|(0x01<<4)|(0x01<<3)|(0x01<<2)|(0x01<<1)|(0x01<<0); //all output set
	LDI  R30,LOW(255)
	OUT  0x11,R30
; 0000 003D 
; 0000 003E 	PORTE = 0x00 | (0x03 << 6);
	LDI  R30,LOW(192)
	OUT  0x3,R30
; 0000 003F 	DDRE = 0x00;
	LDI  R30,LOW(0)
	OUT  0x2,R30
; 0000 0040 
; 0000 0041 	PORTF = 0x00;
	STS  98,R30
; 0000 0042 	DDRF = 0xFF;
	LDI  R30,LOW(255)
	STS  97,R30
; 0000 0043 
; 0000 0044 	PORTG = 0x03;
	LDI  R30,LOW(3)
	STS  101,R30
; 0000 0045 	DDRG = 0x01;
	LDI  R30,LOW(1)
	STS  100,R30
; 0000 0046 //-----------------------------------------------
; 0000 0047     ASSR=0x00;
	LDI  R30,LOW(0)
	OUT  0x30,R30
; 0000 0048     TCCR0==0x00;
	IN   R30,0x33
	CALL SUBOPT_0x0
; 0000 0049     TCNT0=0x00;
	OUT  0x32,R30
; 0000 004A     OCR0=0x00;
	LDI  R30,LOW(0)
	OUT  0x31,R30
; 0000 004B 
; 0000 004C     TCCR1A==0x00;
	IN   R30,0x2F
	CALL SUBOPT_0x0
; 0000 004D     TCCR1B=0x00;
	OUT  0x2E,R30
; 0000 004E     TCNT1H=0x00;
	LDI  R30,LOW(0)
	OUT  0x2D,R30
; 0000 004F     TCNT1L=0x00;
	OUT  0x2C,R30
; 0000 0050     ICR1H=0x00;
	OUT  0x27,R30
; 0000 0051     ICR1L=0x00;
	OUT  0x26,R30
; 0000 0052     OCR1AH=0x00;
	OUT  0x2B,R30
; 0000 0053     OCR1AL=0x00;
	OUT  0x2A,R30
; 0000 0054     OCR1BH=0x00;
	OUT  0x29,R30
; 0000 0055     OCR1BL=0x00;
	OUT  0x28,R30
; 0000 0056     OCR1CH=0x00;
	STS  121,R30
; 0000 0057     OCR1CL=0x00;
	STS  120,R30
; 0000 0058 
; 0000 0059     TCCR2==0x00;
	IN   R30,0x25
	CALL SUBOPT_0x0
; 0000 005A     TCNT2=0x00;
	OUT  0x24,R30
; 0000 005B     OCR2=0x00;
	LDI  R30,LOW(0)
	OUT  0x23,R30
; 0000 005C 
; 0000 005D     TCCR3A==0x00;
	LDS  R26,139
	CALL __EQB12
; 0000 005E     TCCR3B=0x00;
	LDI  R30,LOW(0)
	STS  138,R30
; 0000 005F     TCNT3H=0x00;
	STS  137,R30
; 0000 0060     TCNT3L=0x00;
	STS  136,R30
; 0000 0061     ICR3H=0x00;
	STS  129,R30
; 0000 0062     ICR3L=0x00;
	STS  128,R30
; 0000 0063     OCR3AH=0x00;
	STS  135,R30
; 0000 0064     OCR3AL=0x00;
	STS  134,R30
; 0000 0065     OCR3BH=0x00;
	STS  133,R30
; 0000 0066     OCR3BL=0x00;
	STS  132,R30
; 0000 0067     OCR3CH=0x00;
	STS  131,R30
; 0000 0068     OCR3CL=0x00;
	STS  130,R30
; 0000 0069 
; 0000 006A     EICRA==0x00;
	LDS  R26,106
	CALL __EQB12
; 0000 006B     EICRB=0x00;
	LDI  R30,LOW(0)
	OUT  0x3A,R30
; 0000 006C     EIMSK==0x00;
	IN   R30,0x39
	LDI  R26,LOW(0)
	CALL __EQB12
; 0000 006D 
; 0000 006E 	EIFR = 0x00 | 0xc0;
	LDI  R30,LOW(192)
	OUT  0x38,R30
; 0000 006F 
; 0000 0070     TIMSK=0x00;
	LDI  R30,LOW(0)
	OUT  0x37,R30
; 0000 0071     ETIMSK=0x00;
	STS  125,R30
; 0000 0072 
; 0000 0073     UCSR0B=0x00;
	OUT  0xA,R30
; 0000 0074     UCSR1B==0x00;
	LDS  R26,154
	CALL __EQB12
; 0000 0075     ACSR=0x08;
	LDI  R30,LOW(8)
	OUT  0x8,R30
; 0000 0076     SFIOR==0x00;
	IN   R30,0x20
	LDI  R26,LOW(0)
	CALL __EQB12
; 0000 0077 
; 0000 0078     ADCSRA==0x00;
	IN   R30,0x6
	CALL __EQB12
; 0000 0079     SPCR==0x00;
	IN   R30,0xD
	CALL __EQB12
; 0000 007A 
; 0000 007B     TWCR==0x00;
	LDS  R26,116
	LDI  R30,LOW(0)
	CALL __EQB12
; 0000 007C //**********************************************
; 0000 007D 
; 0000 007E 	lcd_mode = 1;
	LDI  R30,LOW(1)
	MOV  R7,R30
; 0000 007F 
; 0000 0080 	lcd_init();
	RCALL _lcd_init
; 0000 0081     lcd_clear();
	RCALL _lcd_clear
; 0000 0082 	lcd_home();
	RCALL _lcd_home
; 0000 0083 
; 0000 0084     lcd_control_write(0x80);
	LDI  R30,LOW(128)
	ST   -Y,R30
	RCALL _lcd_control_write
; 0000 0085 	lcd_print_data(str_welcome,8);
	LDI  R30,LOW(_str_welcome)
	LDI  R31,HIGH(_str_welcome)
	CALL SUBOPT_0x1
; 0000 0086 
; 0000 0087     delay_ms(500);
	CALL SUBOPT_0x2
; 0000 0088 
; 0000 0089     lcd_control_write(0xC0);
	LDI  R30,LOW(192)
	ST   -Y,R30
	RCALL _lcd_control_write
; 0000 008A     lcd_print_data(str_mega128,8);
	LDI  R30,LOW(_str_mega128)
	LDI  R31,HIGH(_str_mega128)
	CALL SUBOPT_0x1
; 0000 008B 	delay_ms(3000);
	CALL SUBOPT_0x3
; 0000 008C 	delay_ms(3000);
	CALL SUBOPT_0x3
; 0000 008D 
; 0000 008E 	lcd_home();
	RCALL _lcd_home
; 0000 008F 	lcd_clear();
	RCALL _lcd_clear
; 0000 0090 
; 0000 0091     lcd_control_write(0x80);
	LDI  R30,LOW(128)
	ST   -Y,R30
	RCALL _lcd_control_write
; 0000 0092     lcd_print_data(str_countup,8);
	LDI  R30,LOW(_str_countup)
	LDI  R31,HIGH(_str_countup)
	CALL SUBOPT_0x1
; 0000 0093     lcd_control_write(0xC5);
	LDI  R30,LOW(197)
	ST   -Y,R30
	RCALL _lcd_control_write
; 0000 0094     lcd_print_data(str_ea,2);
	LDI  R30,LOW(_str_ea)
	LDI  R31,HIGH(_str_ea)
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(2)
	ST   -Y,R30
	RCALL _lcd_print_data
; 0000 0095 
; 0000 0096 //	#asm("sei")
; 0000 0097 
; 0000 0098     count = 0;
	CLR  R6
; 0000 0099 
; 0000 009A 	while (1)
_0x15:
; 0000 009B 	{
; 0000 009C 	    for(i=1;i<9;i++) {set_led(i);delay_ms(100);}
	LDI  R17,LOW(1)
_0x19:
	CPI  R17,9
	BRSH _0x1A
	CALL SUBOPT_0x4
	SUBI R17,-1
	RJMP _0x19
_0x1A:
; 0000 009D //	    BUZZER_ON;
; 0000 009E //	    delay_ms(200);
; 0000 009F //      BUZZER_OFF;
; 0000 00A0 
; 0000 00A1         for(i=8;i>0;i--) {set_led(i);delay_ms(100);}
	LDI  R17,LOW(8)
_0x1C:
	CPI  R17,1
	BRLO _0x1D
	CALL SUBOPT_0x4
	SUBI R17,1
	RJMP _0x1C
_0x1D:
; 0000 00A2     	BUZZER_ON;
	SBI  0x18,6
; 0000 00A3     	delay_ms(200);
	LDI  R30,LOW(200)
	LDI  R31,HIGH(200)
	CALL SUBOPT_0x5
; 0000 00A4         BUZZER_OFF;
	CBI  0x18,6
; 0000 00A5 
; 0000 00A6         count = count+1;
	INC  R6
; 0000 00A7         if (count>9) count = 0;
	LDI  R30,LOW(9)
	CP   R30,R6
	BRSH _0x22
	CLR  R6
; 0000 00A8 
; 0000 00A9         lcd_control_write(0xC1);
_0x22:
	LDI  R30,LOW(193)
	ST   -Y,R30
	RCALL _lcd_control_write
; 0000 00AA         lcd_data_write(0x30+count); //ASCII CODE
	MOV  R30,R6
	SUBI R30,-LOW(48)
	ST   -Y,R30
	RCALL _lcd_data_write
; 0000 00AB 	    delay_ms(500);
	CALL SUBOPT_0x2
; 0000 00AC 
; 0000 00AD 	};
	RJMP _0x15
; 0000 00AE }
_0x23:
	RJMP _0x23
;
;
;
;/*************************************************************/
;/*                 LCD CONTROL  ROUTINE                      */
;/*************************************************************/
;#include <mega128.h>
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
;#include "mydef.h"
;#include "lcd.h"
;
;void lcd_init_HW(void)
; 0001 0009 {

	.CSEG
; 0001 000A 	// initialize LCD control lines
; 0001 000B 	LCD_RS_0;
; 0001 000C 	LCD_RW_0;
; 0001 000D 	LCD_E_0;
; 0001 000E 	// initialize LCD control lines to output
; 0001 000F 	LCD_RS_1;
; 0001 0010 	LCD_RW_1;
; 0001 0011 	LCD_E_1;
; 0001 0012 	// initialize LCD data port to input
; 0001 0013 	// initialize LCD data lines to pull-up
; 0001 0014 	LCD_DATA_POUT = 0xFF;
; 0001 0015 	LCD_DATA_DDR = 0x00;
; 0001 0016 }
;
;void lcd_busy_wait(void)
; 0001 0019 {
_lcd_busy_wait:
; 0001 001A 	LCD_RS_0;                // set RS to "control"
	CBI  0x15,7
; 0001 001B 	LCD_DATA_DDR = 0x00;     // set data I/O lines to input (8bit)
	LDI  R30,LOW(0)
	OUT  0x1A,R30
; 0001 001C 	LCD_DATA_POUT = 0xFF;    // set pull-ups to on (8bit)
	LDI  R30,LOW(255)
	OUT  0x1B,R30
; 0001 001D 	LCD_RW_1;                // set R/W to "read"
	SBI  0x15,5
; 0001 001E 	LCD_E_1;                 // set "E" line
	SBI  0x15,6
; 0001 001F 	LCD_DELAY;               // wait
	__DELAY_USB 3
; 0001 0020 
; 0001 0021 	while(LCD_DATA_PIN & (1 << LCD_BUSY))
_0x20015:
	SBIS 0x19,7
	RJMP _0x20017
; 0001 0022 	{
; 0001 0023 		LCD_E_0;     // clear "E" line
	CBI  0x15,6
; 0001 0024 		LCD_DELAY;   // wait
	CALL SUBOPT_0x6
; 0001 0025 		LCD_DELAY;   // wait
; 0001 0026 		LCD_E_1;     // set "E" line
	SBI  0x15,6
; 0001 0027 		LCD_DELAY;   // wait
	CALL SUBOPT_0x6
; 0001 0028 		LCD_DELAY;   // wait
; 0001 0029 	}
	RJMP _0x20015
_0x20017:
; 0001 002A 	LCD_E_0;         // clear "E" line
	CBI  0x15,6
; 0001 002B }
	RET
;
;void lcd_control_write(u08 data)
; 0001 002E {
_lcd_control_write:
; 0001 002F 	lcd_busy_wait();     // wait until LCD not busy
;	data -> Y+0
	RCALL _lcd_busy_wait
; 0001 0030 	LCD_RS_0;            // set RS to "control"
	CBI  0x15,7
; 0001 0031 	LCD_RW_0;            // set R/W to "write"
	RJMP _0x2060002
; 0001 0032 	LCD_E_1;             // set "E" line
; 0001 0033 	LCD_DATA_DDR = 0xFF; // set data I/O lines to output (8bit)
; 0001 0034 	LCD_DATA_POUT = data;// output data, 8bits
; 0001 0035 	LCD_DELAY;           // wait
; 0001 0036 	LCD_DELAY;           // wait
; 0001 0037 	LCD_E_0;             // clear "E" line
; 0001 0038 	LCD_DATA_DDR = 0x00; // set data I/O lines to input (8bit)
; 0001 0039 	LCD_DATA_POUT = 0xFF;// set pull-ups to on (8bit)
; 0001 003A }
;
;u08 lcd_control_read(void)
; 0001 003D {
; 0001 003E u08 data;
; 0001 003F 	lcd_busy_wait();      // wait until LCD not busy
;	data -> R17
; 0001 0040 	LCD_DATA_DDR = 0x00;  // set data I/O lines to input (8bit)
; 0001 0041 	LCD_DATA_POUT = 0xFF; // set pull-ups to on (8bit)
; 0001 0042 	LCD_RS_0;             // set RS to "control"
; 0001 0043 	LCD_RW_1;             // set R/W to "read"
; 0001 0044 	LCD_E_1;              // set "E" line
; 0001 0045 	LCD_DELAY;            // wait
; 0001 0046 	LCD_DELAY;            // wait
; 0001 0047 	data = LCD_DATA_PIN;  // input data, 8bits
; 0001 0048 	LCD_E_0;              // clear "E" line
; 0001 0049 	return data;
; 0001 004A }
;
;void lcd_data_write(u08 data)
; 0001 004D {
_lcd_data_write:
; 0001 004E 	lcd_busy_wait();            // wait until LCD not busy
;	data -> Y+0
	RCALL _lcd_busy_wait
; 0001 004F 	LCD_RS_1;                   // set RS to "data"
	SBI  0x15,7
; 0001 0050 	LCD_RW_0;                   // set R/W to "write"
_0x2060002:
	CBI  0x15,5
; 0001 0051 	LCD_E_1;                    // set "E" line
	SBI  0x15,6
; 0001 0052 	LCD_DATA_DDR = 0xFF;        // set data I/O lines to output (8bit)
	LDI  R30,LOW(255)
	OUT  0x1A,R30
; 0001 0053 	LCD_DATA_POUT = data;       // output data, 8bits
	LD   R30,Y
	OUT  0x1B,R30
; 0001 0054 	LCD_DELAY;                  // wait
	CALL SUBOPT_0x6
; 0001 0055 	LCD_DELAY;                  // wait
; 0001 0056 	LCD_E_0;                    // clear "E" line
	CBI  0x15,6
; 0001 0057 	LCD_DATA_DDR = 0x00;        // set data I/O lines to input (8bit)
	LDI  R30,LOW(0)
	OUT  0x1A,R30
; 0001 0058 	LCD_DATA_POUT = 0xFF;       // set pull-ups to on (8bit)
	LDI  R30,LOW(255)
	OUT  0x1B,R30
; 0001 0059 }
_0x2060003:
	ADIW R28,1
	RET
;
;/*************************************************************/
;/********************* PUBLIC FUNCTIONS **********************/
;/*************************************************************/
;
;void lcd_init(void)
; 0001 0060 {
_lcd_init:
; 0001 0061 //    lcd_init_HW();
; 0001 0062     delay_ms(100);
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	CALL SUBOPT_0x5
; 0001 0063 
; 0001 0064     // LCD function set
; 0001 0065     lcd_control_write(0x3A);
	LDI  R30,LOW(58)
	CALL SUBOPT_0x7
; 0001 0066     delay_ms(60);
; 0001 0067 
; 0001 0068     // clear LCD
; 0001 0069     lcd_control_write(0x01);
	LDI  R30,LOW(1)
	CALL SUBOPT_0x7
; 0001 006A     delay_ms(60);   // wait 60ms
; 0001 006B 
; 0001 006C     // set entry mode
; 0001 006D     lcd_control_write(0x0C);
	LDI  R30,LOW(12)
	CALL SUBOPT_0x8
; 0001 006E     delay_ms(20);
; 0001 006F 
; 0001 0070     // move cursor to home
; 0001 0071     lcd_control_write(0x02);
	LDI  R30,LOW(2)
	CALL SUBOPT_0x8
; 0001 0072     delay_ms(20);
; 0001 0073 
; 0001 0074     // set data address to 0
; 0001 0075     lcd_control_write(0x00);
	LDI  R30,LOW(0)
	RJMP _0x2060001
; 0001 0076 
; 0001 0077 }
;
;void lcd_home(void)
; 0001 007A {
_lcd_home:
; 0001 007B     // move cursor to home
; 0001 007C     lcd_control_write(0x02);
	LDI  R30,LOW(2)
	RJMP _0x2060001
; 0001 007D }
;
;void lcd_clear(void)
; 0001 0080 {
_lcd_clear:
; 0001 0081     // clear LCD
; 0001 0082     lcd_control_write(0x01);
	LDI  R30,LOW(1)
_0x2060001:
	ST   -Y,R30
	RCALL _lcd_control_write
; 0001 0083 }
	RET
;
;
;void lcd_print_data(u08* data, u08 n_bytes)
; 0001 0087 {
_lcd_print_data:
; 0001 0088 u08 i;
; 0001 0089 	// print data
; 0001 008A 	for(i=0; i < n_bytes; i++)
	ST   -Y,R17
;	*data -> Y+2
;	n_bytes -> Y+1
;	i -> R17
	LDI  R17,LOW(0)
_0x20037:
	LDD  R30,Y+1
	CP   R17,R30
	BRSH _0x20038
; 0001 008B 	{
; 0001 008C 		lcd_data_write(data[i]);
	LDD  R26,Y+2
	LDD  R27,Y+2+1
	CLR  R30
	ADD  R26,R17
	ADC  R27,R30
	LD   R30,X
	ST   -Y,R30
	RCALL _lcd_data_write
; 0001 008D 	}
	SUBI R17,-1
	RJMP _0x20037
_0x20038:
; 0001 008E }
	LDD  R17,Y+0
	ADIW R28,4
	RET
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

	.CSEG

	.CSEG

	.CSEG

	.DSEG
_str_mega128:
	.BYTE 0x9
_str_welcome:
	.BYTE 0x9
_str_countup:
	.BYTE 0x9
_str_ea:
	.BYTE 0x3

	.CSEG
;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x0:
	LDI  R26,LOW(0)
	CALL __EQB12
	LDI  R30,LOW(0)
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x1:
	ST   -Y,R31
	ST   -Y,R30
	LDI  R30,LOW(8)
	ST   -Y,R30
	JMP  _lcd_print_data

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x2:
	LDI  R30,LOW(500)
	LDI  R31,HIGH(500)
	ST   -Y,R31
	ST   -Y,R30
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:1 WORDS
SUBOPT_0x3:
	LDI  R30,LOW(3000)
	LDI  R31,HIGH(3000)
	ST   -Y,R31
	ST   -Y,R30
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:4 WORDS
SUBOPT_0x4:
	ST   -Y,R17
	CALL _set_led
	LDI  R30,LOW(100)
	LDI  R31,HIGH(100)
	ST   -Y,R31
	ST   -Y,R30
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 6 TIMES, CODE SIZE REDUCTION:7 WORDS
SUBOPT_0x5:
	ST   -Y,R31
	ST   -Y,R30
	JMP  _delay_ms

;OPTIMIZER ADDED SUBROUTINE, CALLED 3 TIMES, CODE SIZE REDUCTION:5 WORDS
SUBOPT_0x6:
	__DELAY_USB 3
	__DELAY_USB 3
	RET

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:2 WORDS
SUBOPT_0x7:
	ST   -Y,R30
	CALL _lcd_control_write
	LDI  R30,LOW(60)
	LDI  R31,HIGH(60)
	RJMP SUBOPT_0x5

;OPTIMIZER ADDED SUBROUTINE, CALLED 2 TIMES, CODE SIZE REDUCTION:2 WORDS
SUBOPT_0x8:
	ST   -Y,R30
	CALL _lcd_control_write
	LDI  R30,LOW(20)
	LDI  R31,HIGH(20)
	RJMP SUBOPT_0x5


	.CSEG
_delay_ms:
	ld   r30,y+
	ld   r31,y+
	adiw r30,0
	breq __delay_ms1
__delay_ms0:
	__DELAY_USW 0x3E8
	wdr
	sbiw r30,1
	brne __delay_ms0
__delay_ms1:
	ret

__EQB12:
	CP   R30,R26
	LDI  R30,1
	BREQ __EQB12T
	CLR  R30
__EQB12T:
	RET

;END OF CODE MARKER
__END_OF_CODE:
