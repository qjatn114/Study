/**
* @file		lcd.c
* @brief		LCD  드라이버  
* @author		강이석/솔루션 공과 전자 학원 	
* @remarks
* @par 수정이력 
*	@li	2012.11.06 : 초기  함수 작성  
*/

#include <atmega128.h>
#include <type.h>
#include <lcd.h>
#include <avr/pgmspace.h>
#include "msk2844.h"
#include "engfont.h"
#include "korfont.h"
//#include "icon.h"

#include <stdlib.h>

//#define LCD_DUBUG			// LCD 디버깅 메시지 출력 

/* RESET : PD5 */
#define LCD_RESET_ACTIVE		DDD5=1
#define LCD_RESET_ENABLE		PORTD5=0
#define LCD_RESET_DISABLE		PORTD5=1

/* CS : PG1 */
#define LCD_CS_ACTIVE			DDG1=1
#define LCD_CS_ENABLE			PORTG1=0
#define LCD_CS_DISABLE			PORTG1=1

/* RS : PG0 */
#define LCD_RS_ACTIVE			DDG0=1
#define LCD_RS_INSTRUCTION		PORTG0=0
#define LCD_RS_DATA				PORTG0=1

/* WR : PD7 */
#define LCD_WR_ACTIVE			DDD7=1
#define LCD_WR_ENABLE			PORTD7=0
#define LCD_WR_DISABLE			PORTD7=1

/* RD : PD6 */
#define LCD_RD_ACTIVE			DDD6=1
#define LCD_RD_ENABLE			PORTD6=0
#define LCD_RD_DISABLE			PORTD6=1

/* DB0 ~ 7 : PA0 ~ 7, DB8 ~ 15 : PC0 ~ 7 */
#define LCD_DATA_SET_OUT		DDRA=0xFF;DDRC=0xFF
#define LCD_DATA_SET_IN			DDRA=0x00;DDRC=0x00
#define LCD_DATA_OUT(n)			PORTC=n >>8;PORTA=n
#define LCD_DATA_IN				PINA

/* LCD Backlight PE3 */
#define LCD_BL_ACTIVE			DDE3=1
#define LCD_BL_ON				PORTE3=1
#define LCD_BL_OFF				PORTE3=0



#define LCD_WIDTH	240
#define LCD_HEIGHT	320

#define LCD_FONT_ENG_COLUMN                8
#define LCD_FONT_ENG_ROW                   16
#define LCD_FONT_ENG_SIZE                  16      // 영어 폰트의 차지하는 메모리 크기(바이트)
#define LCD_FONT_KOR_COLUMN                16
#define LCD_FONT_KOR_ROW                   16
#define LCD_FONT_KOR_SIZE                  32      // 한글 폰트의 차지하는 메모리 크기(바이트)



typedef struct{
	unsigned short bfType;				//BM(0x42, 0x4D) 이라고 써있으면 bmp
	unsigned long bfSize;				// 파일 크기(바이트 단위)
	unsigned short bfReserved1;			// 예약 
	unsigned short bfReserved2;
	unsigned long bfOffBits;			//이미지 데이터가 있는 곳의 포인터(오프셋)  	
}ST_BITMAP_FILE_HEADER;

typedef struct{
	unsigned long biSize;				// 현 구조체의 크기((일반적 0x40)
	unsigned long biWidth;				// 이미지 가로 크기
	unsigned long biHeight;				// 이미지 세로 크기
	unsigned short biPlanes;			// 플레인 수
	unsigned short biBitCount;			// number of bits per pixel (1, 4, 8, or 24)
	unsigned long biCompression;		// compression type (0=none, 1=RLE-8, 2=RLE-4)
	unsigned long biSizeImage;			// size of image data in bytes (including padding)	
	unsigned long biXPixelsPerMeter;	// horizontal resolution in pixels per meter (unreliable)
	unsigned long biYPixelsPerMeter;	// vertical resolution in pixels per meter (unreliable)
	unsigned long biColorUsed;			// number of colors in image, or zero	
	unsigned long biColorImportant;		// number of important colors, or zero
}ST_BITMAP_INFO_HEADER;

typedef struct{
	ST_BITMAP_FILE_HEADER FileHeader;	
	ST_BITMAP_INFO_HEADER FileInfo;
}ST_BITMAP_HEADER;

typedef enum{
	BMP_LEFT_BTN,
	BMP_RIGHT_BTN,
	BMP_STATUS_BAR,
	BMP_PROGRESS_BG_BAR,
	BMP_PROGRESS_FG_BAR,
}BMP_ITEM;



#define BMP_IMAGE_START_OFFSET		0x0A
#define BMP_IMAGE_WIDTH_OFFSET		0x12
#define BMP_IMAGE_HEIGHT_OFFSET		0x16




static uint16_t LCD_GetKFontIndex(uint16_t Code);
static void LCD_Reset(void);
inline static void LCD_WriteInstruction(uint16_t Data);
inline static void LCD_WriteData(uint16_t Data);
inline static void LCD_WriteDataRepeat(uint16_t Data, uint32_t Repeat);
/*
static void LCD_ReadStatus(void);
*/

static void LCD_SetAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
static void LCD_usDelay(uint16_t Delay);
static void LCD_msDelay(uint16_t Delay);
/*
static void LCD_DrawBMP(uint16_t SX, uint16_t SY, BMP_ITEM BMP);
*/
static int LCD_PutChar(char Data, FILE *Stream);
static FILE device = FDEV_SETUP_STREAM(LCD_PutChar, NULL, _FDEV_SETUP_WRITE);




static const uint8_t LCD_NumericString[] = "0123456789";

static uint16_t LCD_X = 0;
static uint16_t LCD_Y = 0;





/**
* @fn		void LCD_Init(void)
* @brief
*	- LCD 초기화 함수 
* @remarks
* @param	void
* @return	void			
*/
void LCD_Init(void)
{
	/* Backlight 를 켠다 */
	LCD_BL_ACTIVE;
	LCD_BL_ON;


	// 포트 초기화 
	LCD_CS_DISABLE;
	LCD_RS_INSTRUCTION;
	LCD_WR_DISABLE;
	LCD_RD_DISABLE;	
	
	LCD_CS_ACTIVE;
	LCD_RS_ACTIVE;
	LCD_WR_ACTIVE;
	LCD_RD_ACTIVE;
	
	LCD_DATA_SET_OUT;


	LCD_Reset();


//************* Start Initial Sequence **********//		
	LCD_WriteInstruction(0x00E5);	LCD_WriteData(0x78F0); 
	LCD_WriteInstruction(0x0001);	LCD_WriteData(0x0000); 		// Org : 0x0100,  0x0000 : 좌/우 방향 전환(SS)
	LCD_WriteInstruction(0x0002);	LCD_WriteData(0x0700); 
	LCD_WriteInstruction(0x0003);	LCD_WriteData(0x1030); 
	LCD_WriteInstruction(0x0004);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0008);	LCD_WriteData(0x0202);  
	LCD_WriteInstruction(0x0009);	LCD_WriteData(0x0000);
	LCD_WriteInstruction(0x000A);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x000C);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x000D);	LCD_WriteData(0x0000);
	LCD_WriteInstruction(0x000F);	LCD_WriteData(0x0000);
	//power on sequence VGHVGL
	LCD_WriteInstruction(0x0010);	LCD_WriteData(0x0000);   
	LCD_WriteInstruction(0x0011);	LCD_WriteData(0x0007);  
	LCD_WriteInstruction(0x0012);	LCD_WriteData(0x0000);  
	LCD_WriteInstruction(0x0013);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0007);	LCD_WriteData(0x0000); 
	//vgh 
	LCD_WriteInstruction(0x0010);	LCD_WriteData(0x1690);   
	LCD_WriteInstruction(0x0011);	LCD_WriteData(0x0227);
	//delay_ms(100);
	//vregiout 
	LCD_WriteInstruction(0x0012);	LCD_WriteData(0x009D); //0x001b
	//delay_ms(100); 
	//vom amplitude
	LCD_WriteInstruction(0x0013);	LCD_WriteData(0x1900);
	//delay_ms(100); 
	//vom H
	LCD_WriteInstruction(0x0029);	LCD_WriteData(0x0025); 
	LCD_WriteInstruction(0x002B);	LCD_WriteData(0x000D); 
	//gamma
	LCD_WriteInstruction(0x0030);	LCD_WriteData(0x0007);
	LCD_WriteInstruction(0x0031);	LCD_WriteData(0x0303);
	LCD_WriteInstruction(0x0032);	LCD_WriteData(0x0003);// 0006
	LCD_WriteInstruction(0x0035);	LCD_WriteData(0x0206);
	LCD_WriteInstruction(0x0036);	LCD_WriteData(0x0008);
	LCD_WriteInstruction(0x0037);	LCD_WriteData(0x0406); 
	LCD_WriteInstruction(0x0038);	LCD_WriteData(0x0304);//0200
	LCD_WriteInstruction(0x0039);	LCD_WriteData(0x0007); 
	LCD_WriteInstruction(0x003C);	LCD_WriteData(0x0602);// 0504
	LCD_WriteInstruction(0x003D);	LCD_WriteData(0x0008); 
	//ram
	LCD_WriteInstruction(0x0050);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0051);	LCD_WriteData(0x00EF);
	LCD_WriteInstruction(0x0052);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0053);	LCD_WriteData(0x013F);  
	LCD_WriteInstruction(0x0060);	LCD_WriteData(0x2700);		// Org : 0xA700,  0x2700 : 위/아래 방향 전환(GS)
	LCD_WriteInstruction(0x0061);	LCD_WriteData(0x0001); 
	LCD_WriteInstruction(0x006A);	LCD_WriteData(0x0000); 
	//
	LCD_WriteInstruction(0x0080);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0081);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0082);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0083);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0084);	LCD_WriteData(0x0000); 
	LCD_WriteInstruction(0x0085);	LCD_WriteData(0x0000); 
	//
	LCD_WriteInstruction(0x0090);	LCD_WriteData(0x0010); 
	LCD_WriteInstruction(0x0092);	LCD_WriteData(0x0600); 
	
	LCD_WriteInstruction(0x0007);	LCD_WriteData(0x0133);
	LCD_WriteInstruction(0x00);		LCD_WriteData(0x0022);//	


	// 화면 초기화
	LCD_ClearScreen(RED);

	stdout = &device;  	//  device 를 stdout으로 설정한다. 
}

/**
* @fn		void LCD_ClearScreen(COLOR Color)
* @brief
*	- LCD 화면을 지운다.   
* @remarks
* @param	COLOR Color	: 색상   
* @return	void			
*/
void LCD_ClearScreen(COLOR Color)
{	
	LCD_SetAddress(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
	LCD_WriteDataRepeat(Color, (uint32_t)LCD_WIDTH * LCD_HEIGHT);					// 화면 전체를 그린다. 	
}

/**
* @fn		void LCD_FillColor(uint16_t SX, uint16_t SY, uint16_t DX, uint16_t DY, COLOR Color)
* @brief
*	- 영어를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX		: X 시작 위치   
* @param	uint16_t SY		: Y 시작 위치
* @param	uint16_t LengthX	: X 끝 위치   
* @param	uint16_t LengthY	: Y 끝 위치
* @param	COLOR Color	: 색상   
* @return	void			
*/
void LCD_FillColor(uint16_t SX, uint16_t SY, uint16_t LengthX, uint16_t LengthY, COLOR Color)
{
	LCD_SetAddress(SX, SY, SX + LengthX - 1, SY + LengthY - 1);		/* 사용 영역 지정 */	
	LCD_WriteDataRepeat(Color, (uint32_t)LengthX * LengthY);		/* 화면 전체를 그린다. */	
}

/**
* @fn		void LCD_WriteEnglish(uint16_t SX, uint16_t SY,uint8_t Data, COLOR Color, COLOR BG_Color)
* @brief
*	- 영어를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX	: X 위치   
* @param	uint16_t SY	: Y 위치
* @param	uint8_t Data	: 글자
* @param	COLOR Color	: 글자 색상   
* @param	COLOR BG_Color	: 배경 색상   
* @return	void			
*/
void LCD_WriteEnglish(uint16_t SX, uint16_t SY, uint8_t Data, COLOR Color, COLOR BG_Color)
{
	uint8_t i,j, Font;
    uint16_t Index;

    // 글자의 인덱스 값을 찾는다.
	Index = pgm_read_byte(&EngFont_IndexTable[Data]);
    if(Index == 0xFF)		// 폰트의  Index가 없는 경우 
    {
		#ifdef 	LCD_DUBUG
        UART_WriteString("\r\n<Error> Can't find eng font index : ");
        UART_WriteHexa(Font);
		#endif
        return;
    }

	Index = Index * LCD_FONT_ENG_SIZE;

	LCD_SetAddress(SX, SY, SX + LCD_FONT_ENG_COLUMN - 1, SY + LCD_FONT_ENG_ROW - 1); 	/* 사용 영역 지정 */	

	for(j = 0; j < LCD_FONT_ENG_ROW; j++)
	{
		Font = pgm_read_byte(&EngFont[j + Index]);		/* 폰트 제이터를 읽어옴 */

		/* 픽셀 데이터 쓰기  */
		for(i = 0; i < LCD_FONT_ENG_COLUMN; i++)
		{
			(Font & (0x80 >> i))? LCD_WriteData(Color): LCD_WriteData(BG_Color);
		}
	}
}

/**
* @fn		void LCD_WriteKorean(uint16_t SX, uint16_t SY,uint16_t Data, COLOR Color, COLOR BG_Color)
* @brief
*	- 한글를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX	: X 위치   
* @param	uint16_t SY	: Y 위치
* @param	uint16_t Data	: 글자
* @param	COLOR Color	: 글자 색상   
* @param	COLOR BG_Color	: 배경 색상   
* @return	void			
*/
void LCD_WriteKorean(uint16_t SX, uint16_t SY, uint16_t Data, COLOR Color, COLOR BG_Color)
{
	uint8_t i,j;
	uint16_t Font, Index;

    // 글자의 인덱스 값을 찾는다.
    Index = LCD_GetKFontIndex(Data);
	
    if(Index == 0xFFFF)		// 폰트의  Index가 없는 경우 
    {
	#ifdef	LCD_DUBUG
        UART_WriteString("\r\n<Error> Can't find kor font index : ");
        UART_WriteHexa(Font);
	#endif
        return;
    }

	Index = Index * LCD_FONT_KOR_SIZE;	

	LCD_SetAddress(SX, SY, SX + LCD_FONT_KOR_COLUMN - 1, SY + LCD_FONT_KOR_ROW - 1); 	/* 사용 영역 지정 */		

	for(j = 0; j < LCD_FONT_KOR_ROW; j++)
	{
		/* Font 데이터를 가지고 온다.( 한글은 한 라인인이 16개로 되어 있으므로 2바이트를 가지고 온다) */
		Font = pgm_read_byte(&KorFont[j *2 + Index]);
		Font = (Font << 8) + pgm_read_byte(&KorFont[j *2 + 1 + Index]);
		
		/* 픽셀 데이터 쓰기  */
		for(i = 0; i < LCD_FONT_KOR_COLUMN; i++)
		{
			(Font & (0x8000 >> i))? LCD_WriteData(Color): LCD_WriteData(BG_Color);	
		}		
	}
}

/**
* @fn		void LCD_WriteString(uint16_t SX, uint16_t SY,const char *String, COLOR Color, COLOR BG_Color)
* @brief
*	- 문자열를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX	: X 위치   
* @param	uint16_t SY	: Y 위치
* @param	const char *String	: 문자열
* @param	COLOR Color		: 글자 색상   
* @param	COLOR BG_Color	: 배경 색상   
* @return	void			
*/
void LCD_WriteString(uint16_t SX, uint16_t SY,const char *String, COLOR Color, COLOR BG_Color)
{
    uint16_t Data;

    while(*(String) != 0)
    {
        // 영어인지 한글인지 구별( 한글은 0xB000 이상에 위치한다.)
        if(*String < 0x80)      // 영어
        {
            Data = *String;
            LCD_WriteEnglish(SX, SY, (unsigned char)Data, Color, BG_Color);
            String++;
            SX += 8;
        }
        else                    // 한글
        {
            Data = (*String << 8) + *(String + 1);
            LCD_WriteKorean(SX, SY, Data, Color, BG_Color);
            String += 2;
            SX += 16;
        }
    }
}

#if 0
void LCD_DrawIcon(uint16_t SX, uint16_t SY,ICON_ITEM Icon)
{
	unsigned long ImageStart, ImageWidth, ImageHeight;
	unsigned short i, j, Data;
	unsigned char  *pIcon;

	/* Icon 데이터 배열을 가지고 온다. */
	switch(Icon)
	{
		case ICON_LED :
			pIcon =(unsigned char *)LED_Icon;
			break;
		case ICON_CLOCK :
			pIcon =(unsigned char *)Clock_Icon;
			break;
		case ICON_ADC :
			pIcon =(unsigned char *)ADC_Icon;
			break;
		default :
			return;
	}

	/* 이미지 정보를 가지고 온다. */
	ImageStart = pgm_read_dword(&pIcon[BMP_IMAGE_START_OFFSET]);
	ImageWidth = pgm_read_dword(&pIcon[BMP_IMAGE_WIDTH_OFFSET]);
	ImageHeight = pgm_read_dword(&pIcon[BMP_IMAGE_HEIGHT_OFFSET]);
	pIcon = pIcon + ImageStart;		// 이미지 시작 위치 주소로 변경 
	

	LCD_SetAddress(SX, SY, SX + ImageWidth - 1, SY + ImageHeight - 1); 	/* 사용 영역 지정 */	


	/* 그림을 LCD 화면에 표시한다 */
	for(j = 0; j < ImageHeight; j++)
	{
		/* 좌표 이동 명령 */ 
//		LCD_WriteInstruction(MSK_IX_RAM_ADDR_SET1); LCD_WriteData(SX);		// X축 초기화  
//		LCD_WriteInstruction(MSK_IX_RAM_ADDR_SET2); LCD_WriteData(SY + j);	// Y축 이동 		
		/* 데이터 전송 명령 */ 
//		LCD_WriteInstruction(MSK_IX_RAM_DATA_RW);

		for(i = 0; i < ImageWidth; i++)
		{
			/* 픽셀 데이터를 가지고 온다. */
			/* 주의1 : 위치 계산은 int16_t 단위로 x2 필요 */
			/* BMP 파일의 데이터 저장은 그림의 아래에서 위로 올라 오면서 저장됨 */ 
			Data = pgm_read_word(&pIcon[(ImageHeight - j -1)*ImageWidth*2 + i*2]);  	
			/* LCD 에 데이터 전송 */
			LCD_WriteData(Data);	
		}		
	}	

}



/**
* @fn		void LCD_DrawStatusBar(uint16_t SX, uint16_t SY, const char *String, COLOR Color, COLOR BG_Color)
* @brief
*	- 문자열를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX	: X 위치   
* @param	uint16_t SY	: Y 위치
* @param	const char *String	: 문자열
* @param	COLOR Color		: 글자 색상   
* @param	COLOR BG_Color	: 배경 색상  
* @return	void			
*/
void LCD_DrawStatusBar(uint16_t SX, uint16_t SY, const char *String, COLOR Color, COLOR BG_Color)
{
	LCD_DrawBMP(SX, SY, BMP_LEFT_BTN);
	LCD_DrawBMP(SX + 40, SY, BMP_STATUS_BAR);
	LCD_DrawBMP(SX + 120, SY, BMP_RIGHT_BTN);	
	LCD_WriteString(SX + 50, SY + 9, String, Color, BG_Color);
}



/**
* @fn		void LCD_DrawProgressBar(uint16_t SX, uint16_t SY, uint8_t Location, const CHAR *String, COLOR Color, COLOR BG_Color, uint16_t Data)
* @brief
*	- 문자열를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX		: X 위치   
* @param	uint16_t SY		: Y 위치
* @param	uint8_t Location	: 커서의 위치 0 ~ 100사이의 값
* @param	CHAR *String		: 제목의 문자열 
* @param	COLOR Color		: 글자 색상   
* @param	COLOR BG_Color	: 배경 색상  
* @param	uint16_t Data		: 표시할 숫자값 
* @return	void			
*/
void LCD_DrawProgressBar(uint16_t SX, uint16_t SY, uint8_t Location, const char *String, COLOR Color, COLOR BG_Color, uint16_t Data)
{
	/* 진행바 배경 표시 */
	LCD_DrawBMP(SX, SY, BMP_PROGRESS_BG_BAR);
	/* 진행바의 위치 표시  */
	Location %= 101;		// 0 ~ 100 으로 제한 
	LCD_DrawBMP(SX + (uint16_t)Location * 124 /100, SY, BMP_PROGRESS_FG_BAR);

	/* 제목 표시 */
	LCD_WriteString(SX + 8, SY + 36, String, Color, BG_Color);
	/* 데이터값 표시  */
	LCD_WriteEnglish(SX + 100, SY + 36, LCD_NumericString[(Data /1000) % 10], YELLOW, BLACK);
	LCD_WriteEnglish(SX + 108, SY + 36, LCD_NumericString[(Data /100) % 10], YELLOW, BLACK);
	LCD_WriteEnglish(SX + 116, SY + 36, LCD_NumericString[(Data /10) % 10], YELLOW, BLACK);
	LCD_WriteEnglish(SX + 124, SY + 36, LCD_NumericString[Data % 10], YELLOW, BLACK);
}


#endif 

/**
* @fn		void LCD_DrawPixel(uint16_t SX, uint16_t SY, COLOR Color)
* @brief
*	- 점를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX		: X 위치   
* @param	uint16_t SY		: Y 위치
* @param	COLOR Color		: 색상   
* @return	void			
*/
void LCD_DrawPixel(uint16_t SX, uint16_t SY, COLOR Color)
{
	LCD_SetAddress(SX, SY, SX, SY); 	/* 사용 영역 지정 */	
	LCD_WriteData(Color);				/* 점을 찍는다.  */ 
}


void LCD_DrawLine(uint16_t SX, uint16_t SY,uint16_t DX, uint16_t DY, uint16_t Color)
{
	int32_t x, y, addx, addy, dx, dy;
	int32_t P;
	int32_t i;
	
	dx = abs((int32_t)(DX - SX));
	dy = abs((int32_t)(DY - SY));
	x = SX;
	y = SY;
	
	if(SX > DX)
	   addx = -1;
	else
	   addx = 1;
	if(SY > DY)
	   addy = -1;
	else
	   addy = 1;
	
	if(dx >= dy)
	{
	   P = 2*dy - dx;
	
	   for(i=0; i<=dx; ++i)
	   {
		  LCD_DrawPixel(x, y, Color);
	
		  if(P < 0)
		  {
			 P += 2*dy;
			 x += addx;
		  }
		  else
		  {
			 P += 2*dy - 2*dx;
			 x += addx;
			 y += addy;
		  }
	   }
	}
	else
	{
	   P = 2*dx - dy;
	
	   for(i=0; i<=dy; ++i)
	   {
		  LCD_DrawPixel(x, y, Color);
	
		  if(P < 0)
		  {
			 P += 2*dx;
			 y += addy;
		  }
		  else
		  {
			 P += 2*dx - 2*dy;
			 x += addx;
			 y += addy;
		  }
	   }
	}
}


void LCD_DrawCircle(uint16_t SX, uint16_t SY, uint16_t Radius,uint8_t Fill, uint16_t Color)
{

	uint16_t x,y;
	int16_t delta,tmp;
	x = 0;
	y = Radius;
	delta = 3 - (Radius << 1);

	while(y >= x)
	{
		if(Fill)
		{
			LCD_DrawLine(SX + x, SY + y, SX -x, SY + y, Color);
			LCD_DrawLine(SX + x, SY - y, SX -x, SY - y, Color);
			LCD_DrawLine(SX + y, SY + x, SX -y, SY + x, Color);
			LCD_DrawLine(SX + y, SY - x, SX -y, SY - x, Color);
		}
		else
		{
			LCD_DrawPixel(SX + x, SY + y, Color);
			LCD_DrawPixel(SX - x, SY + y, Color);
			LCD_DrawPixel(SX + x, SY - y, Color);
			LCD_DrawPixel(SX - x, SY - y, Color);
			LCD_DrawPixel(SX + y, SY + x, Color);
			LCD_DrawPixel(SX - y, SY + x, Color);
			LCD_DrawPixel(SX + y, SY - x, Color);
			LCD_DrawPixel(SX - y, SY - x, Color);
		}
		x++;
		if(delta >= 0)
		{
			y--;
			tmp = (x << 2);
			tmp -= (y << 2);
			delta += (tmp + 10);
		}
		else
		{
			delta += ((x << 2) + 6);
		}
	}
}


void LCD_DrawRect(uint16_t SX, uint16_t SY, uint16_t DX, uint16_t DY, uint8_t Fill, uint16_t Color)
{
	if(Fill)
	{
	   int16_t y, ymax; 						 //  y의 최대/최소를 찾는다. 
	   if(SY < DY)
	   {
		  y = SY;
		  ymax = DY;
	   }
	   else
	   {
		  y = DY;
		  ymax = SY;
	   }

	   for(; y<=ymax; ++y) 				   		// 삭각형을 채운다. 
		  LCD_DrawLine(SX, y, DX, y, Color);
	}
	else
	{
	   LCD_DrawLine(SX, SY, DX, SY, Color);	  	// 4개의 선을 그린다. 
	   LCD_DrawLine(SX, DY, DX, DY, Color);
	   LCD_DrawLine(SX, SY, SX, DY, Color);
	   LCD_DrawLine(DX, SY, DX, DY, Color);
	}
}



void LCD_SetLocation(uint16_t SX, uint16_t SY)
{
	/* 좌표 이동 */ 
	LCD_X = SX; 	// X축 이동  
	LCD_Y = SY;
}






/**
* @fn		static uint16_t LCD_GetKFontIndex(uint16_t Code)
* @brief
*	- 한글 폰트의 Index를 구한다.
* @remarks
* @param	uint16_t Code	: 한글 코드     
* @return	void			
*/
static uint16_t LCD_GetKFontIndex(uint16_t Code)
{
	uint16_t left = 0;
	uint16_t right = sizeof(KorFont_IndexTable)/sizeof(uint16_t);
	uint16_t mid;
	uint16_t tmp;

	while (left <= right) 
	{
		mid = (right + left) / 2;
		tmp = pgm_read_word(&KorFont_IndexTable[mid]);
		if (tmp == Code)
			return mid;

		if (Code < tmp)
			right = mid - 1;
		else
			left = mid + 1;
	}

	return 0xFFFF;	// not found, return the first character
}


/**
* @fn		static void LCD_Reset(void)
* @brief
*	- LCD를 리셋시킨다.
* @remarks
* @param	void
* @return	void			
*/
static void LCD_Reset(void)
{
	uint8_t IntFlag;
	
	// 인터럽트 중지 
	IntFlag = I;
	I = 0;
		
	LCD_RESET_DISABLE;
	LCD_RESET_ACTIVE;
	LCD_msDelay(5);
	LCD_RESET_ENABLE;
	LCD_msDelay(5);
	LCD_RESET_DISABLE;
	LCD_msDelay(5);

	// 인터럽트 복원 
	I = IntFlag;		
}

/**
* @fn		static void LCD_WriteInstruction(uint16_t Data)
* @brief
*	- LCD에 명령어를 쓴다. 
* @remarks
* @param	uint16_t Data	: LCD 명령어      
* @return	void			
*/
inline static void LCD_WriteInstruction(uint16_t Data)
{
	uint8_t IntFlag;
	
	// 인터럽트 중지 
	IntFlag = I;
	I = 0;
		
	LCD_RS_INSTRUCTION;
	LCD_CS_ENABLE;
	
	LCD_DATA_OUT(Data);

	LCD_WR_ENABLE;
	LCD_WR_DISABLE;

	LCD_CS_DISABLE;

	// 인터럽트 복원 
	I = IntFlag;		
}

/**
* @fn		static void LCD_WriteData(uint16_t Data)
* @brief
*	- LCD에 데이터를 쓴다. 
* @remarks
* @param	uint16_t Data	: LCD 데이터    
* @return	void			
*/
inline static void LCD_WriteData(uint16_t Data)
{
	uint8_t IntFlag;
	
	// 인터럽트 중지 
	IntFlag = I;
	I = 0;
		
	LCD_RS_DATA;
	LCD_CS_ENABLE;

	LCD_DATA_OUT(Data);

	LCD_WR_ENABLE;
	LCD_WR_DISABLE;

	LCD_CS_DISABLE;	

	// 인터럽트 복원 
	I = IntFlag;		
}

/**
* @fn		static void LCD_WriteDataRepeat(uint16_t Data, uint32_t Repeat)
* @brief
*	- LCD에 데이터를 반복해서 쓴다. 
* @remarks
* @param	uint16_t Data		: LCD 데이터   
* @param	uint32_t Repeat	: 반복횟수   
* @return	void			
*/
inline static void LCD_WriteDataRepeat(uint16_t Data, uint32_t Repeat)
{
	uint32_t i;
	uint8_t IntFlag;
	
	// 인터럽트 중지 
	IntFlag = I;
	I = 0;	

	LCD_RS_DATA;
	LCD_CS_ENABLE;	

	for(i = 0; i < Repeat; i++)
	{
		LCD_DATA_OUT(Data);
		LCD_WR_ENABLE;
		LCD_WR_DISABLE;				
	}	
	LCD_CS_DISABLE;	

	// 인터럽트 복원 
	I = IntFlag;	
}



#if 0

/**
* @fn		static void LCD_ReadStatus(void)
* @brief
*	- LCD의 상태를 읽는다
* @remarks
* @param	void  
* @return	void			
*/
static void LCD_ReadStatus(void)
{
	uint8_t *Addr;
	uint8_t Temp;
	uint8_t IntFlag;
	
	// 인터럽트 중지 
	IntFlag = I;
	I = 0;	

//	TFT_RS_INSTRUCTION;
//	TFT_CS_ENABLE;
	PORTD7 = 0;
	PORTC7 = 0;
	Addr =(uint8_t *)0x2000;
	Temp = *Addr;

	Temp = *Addr;
	
	PORTC7 = 1;

	// 인터럽트 복원 
	I = IntFlag;
}

#endif 

static void LCD_SetAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	LCD_WriteInstruction(0x0020); 	LCD_WriteData(X1);	   // Column address start1
	LCD_WriteInstruction(0x0021); 	LCD_WriteData(Y1);	   // Column address end1
	LCD_WriteInstruction(0x0050); 	LCD_WriteData(X1);	   // Row address start1
    LCD_WriteInstruction(0x0052); 	LCD_WriteData(Y1);	   // Row address end2
	LCD_WriteInstruction(0x0051); 	LCD_WriteData(X2);	   // Row address end1
	LCD_WriteInstruction(0x0053); 	LCD_WriteData(Y2);
    LCD_WriteInstruction(0x0022);		
}



/**
* @fn		static void LCD_usDelay(uint16_t Delay)
* @brief
*	- 딜레이 (us)
* @remarks
* @param	uint16_t Delay		: 딜레이 
* @return	void			
*/
static void LCD_usDelay(uint16_t Delay)
{
	register uint16_t i;
	
	for(i = 0; i < Delay; i++) 		// 4Cycle+
	{

		asm volatile(" PUSH R0 "); 	// 2Cycle+
		asm volatile(" POP R0 "); 	// 2Cycle+ = 8Cycle = 1us
	}

}

/**
* @fn		static void LCD_msDelay(uint16_t Delay)
* @brief
*	- 딜레이 (ms)
* @remarks
* @param	uint16_t Delay		: 딜레이 
* @return	void			
*/
static void LCD_msDelay(uint16_t Delay)
{
	register uint16_t i;
	
	for(i = 0; i < Delay; i++) 
	{
		LCD_usDelay(250); // 250us+
		LCD_usDelay(250); // 250us+
		LCD_usDelay(250); // 250us+
		LCD_usDelay(250); // 250us * 4 = 1ms
	}

}

#if 0

/**
* @fn		static void LCD_DrawBMP(uint16_t SX, uint16_t SY, BMP_ITEM BMP)
* @brief
*	- 문자열를 LCD에 표시한다  
* @remarks
* @param	uint16_t SX		: X 위치   
* @param	uint16_t SY		: Y 위치
* @param	BMP_ITEM BMP	: BMP 아이템  
* @return	void			
*/
static void LCD_DrawBMP(uint16_t SX, uint16_t SY, BMP_ITEM BMP)
{
	unsigned long ImageStart, ImageWidth, ImageHeight;
	unsigned short i, j, Data;
	unsigned char  *pBMP;

	/* Icon 데이터 배열을 가지고 온다. */
	switch(BMP)
	{
		case BMP_LEFT_BTN :
			pBMP =(unsigned char *)LeftBtn;
			break;
		case BMP_RIGHT_BTN :
			pBMP =(unsigned char *)RightBtn;
			break;
		case BMP_STATUS_BAR :
			pBMP =(unsigned char *)StatusBar;
			break;
		case BMP_PROGRESS_BG_BAR :
			pBMP =(unsigned char *)ProgressBarBG;
			break;
		case BMP_PROGRESS_FG_BAR :
			pBMP =(unsigned char *)ProgressBarFG;
			break;			
		default :
			return;
	}

	/* 이미지 정보를 가지고 온다. */
	ImageStart = pgm_read_dword(&pBMP[BMP_IMAGE_START_OFFSET]);
	ImageWidth = pgm_read_dword(&pBMP[BMP_IMAGE_WIDTH_OFFSET]);
	ImageHeight = pgm_read_dword(&pBMP[BMP_IMAGE_HEIGHT_OFFSET]);
	pBMP = pBMP + ImageStart;		// 이미지 시작 위치 주소로 변경 
	

	LCD_SetAddress(SX, SY, SX + ImageWidth - 1, SY + ImageHeight - 1); 	/* 사용 영역 지정 */	


	/* 그림을 LCD 화면에 표시한다 */
	for(j = 0; j < ImageHeight; j++)
	{
		/* 좌표 이동 명령 */ 
//		LCD_WriteInstruction(MSK_IX_RAM_ADDR_SET1); LCD_WriteData(SX);		// X축 초기화  
//		LCD_WriteInstruction(MSK_IX_RAM_ADDR_SET2); LCD_WriteData(SY + j);	// Y축 이동 		
		/* 데이터 전송 명령 */ 
//		LCD_WriteInstruction(MSK_IX_RAM_DATA_RW);

		for(i = 0; i < ImageWidth; i++)
		{
			/* 픽셀 데이터를 가지고 온다. */
			/* 주의1 : 위치 계산은 int16_t 단위로 x2 필요 */
			/* BMP 파일의 데이터 저장은 그림의 아래에서 위로 올라 오면서 저장됨 */ 
			Data = pgm_read_word(&pBMP[(ImageHeight - j -1)*ImageWidth*2 + i*2]);  	
			/* LCD 에 데이터 전송 */
			LCD_WriteData(Data);	
		}		
	}	
}

#endif 

static int LCD_PutChar(char Data, FILE *Stream)
{
	uint8_t i,j, Font;
    uint16_t Index;
    // 글자의 인덱스 값을 찾는다.
	Index = pgm_read_byte(&EngFont_IndexTable[(uint8_t)Data]);
    if(Index == 0xFF)		// 폰트의  Index가 없는 경우 
    {
        return 0;
    }

	Index = Index * LCD_FONT_ENG_SIZE;

	LCD_SetAddress(LCD_X, LCD_Y, LCD_X + LCD_FONT_ENG_COLUMN - 1, LCD_Y + LCD_FONT_ENG_ROW - 1); 	/* 사용 영역 지정 */	


	for(j = 0; j < LCD_FONT_ENG_ROW; j++)
	{
		Font = pgm_read_byte(&EngFont[j + Index]);

		for(i = 0; i < LCD_FONT_ENG_COLUMN; i++)
		{
			(Font & (0x80 >> i))? LCD_WriteData(YELLOW): LCD_WriteData(BLACK);
		}
	}
	LCD_X += 8;
	return 0;
}


