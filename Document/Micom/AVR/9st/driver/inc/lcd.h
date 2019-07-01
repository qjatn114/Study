#ifndef _LCD_H_
#define _LCD_H_

#include <type.h>
#include <stdio.h>


typedef enum{
	BLACK 	= 0x0000,
	WHITE 	= 0xFFFF,
	YELLOW 	= 0xFFE0,
	RED 	= 0xF800,
	GREEN 	= 0x07E0,
	BLUE 	= 0x001F,
	CYAN 	= 0x07FF,
	MAGENTA = 0xF81F,
}COLOR;


typedef enum{
	ICON_LED,
	ICON_CLOCK,
	ICON_ADC,
	ICON_MAX
}ICON_ITEM;

void LCD_Init(void);
void LCD_ClearScreen(COLOR Color);
void LCD_FillColor(uint16_t SX, uint16_t SY, uint16_t LengthX, uint16_t LengthY, COLOR Color);
void LCD_WriteEnglish(uint16_t SX, uint16_t SY,uint8_t Data, COLOR Color, COLOR BG_Color);
void LCD_WriteKorean(uint16_t SX, uint16_t SY,uint16_t Data, COLOR Color, COLOR BG_Color);
void LCD_WriteString(uint16_t SX, uint16_t SY,const char *String, COLOR Color, COLOR BG_Color);
/*
//void LCD_DrawIcon(uint16_t SX, uint16_t SY,ICON_ITEM Icon);
//void LCD_DrawStatusBar(uint16_t SX, uint16_t SY, const char *String, COLOR Color, COLOR BG_Color);
//void LCD_DrawProgressBar(uint16_t SX, uint16_t SY, uint8_t Location, const char *String, COLOR Color, COLOR BG_Color, uint16_t Data);
*/
void LCD_DrawPixel(uint16_t SX, uint16_t SY, COLOR Color);
void LCD_DrawLine(uint16_t SX, uint16_t SY,uint16_t DX, uint16_t DY, uint16_t Color);
void LCD_DrawRect(uint16_t SX, uint16_t SY, uint16_t DX, uint16_t DY, uint8_t Fill, uint16_t Color);
void LCD_DrawCircle(uint16_t SX, uint16_t SY, uint16_t Radius,uint8_t Fill, uint16_t Color);

void LCD_SetLocation(uint16_t SX, uint16_t SY);
#define LCD_Printf		printf



#endif

