#include "Type.h"
#include "event.h"
#include "gps.h"
#include "Uart.h"
#include "lcd.h"
#include "rtc.h"

#include <string.h>
#include <stdlib.h>

typedef struct{
//GPGGA(Global Positioning System Fix Data)
/*
-----------------------------------------------------------------------------
Name     Example  Unit Description
-----------------------------------------------------------------------------
Message ID    $GPGGA  GGA  protocol header
UTC Time    161229.487   hhmmss.sss
Latitude    3723.2475   ddmm.mmmm
N/S Indicator   N     N=north or S=south
Longitude    12158.3416   dddmm.mmmm
E/W Indicator   W     E=east or W=west
Position Fix Indicator 1     See Table 1-4
Satellites Used   07     Range 0 to 12
HDOP     1.0     Horizontal Dilution of Precision
MSL Altitude   9.0   meters 
Units     M   meters 
Geoid Separation     meters 
Units     M   meters 
Age of Diff. Corr     second Null fields when DGPS is not used
Diff. Ref. Station ID 0000  
Checksum    *18  
<CR><LF>         End of message termination
-----------------------------------------------------------------------------
[$GPGGA] $GPGGA,084816.000,3728.6289,N,12652.8449,E,1,09,0.9,89.4,M,19.3,M,,0000*69
-----------------------------------------------------------------------------
*/
 uint8_t Hour;    // UTC Time 
 uint8_t Minute;
 uint8_t Second;
 double Latitude;  // ����
 uint8_t N_S;    // N : ����, S : ����
 
 double Longitude;  // �浵 
 uint8_t E_W;   // E : ����, W : ����
 
 uint8_t GPSQualtity;  // 0 : �߸��� ������ , 1 : �⺻ GPS���� ����, 2 : DGPS ��� 
 uint8_t NumOfSats;  // ����ϰ� �ִ� ������ ���� 
 double HDOP;   // ���� 
 double Altitude;  // �ؼ��� ���� �� 


/* GPRMC */
 double SpeedOfGound;
 uint16_t Year;
 uint8_t Month;
 uint8_t Day;
}ST_NMEA;


static void GPS_UARTCallback(Event_t Event, uint16_t Arg);
static void GPS_Parsing(char *Data);


static void GPS_ParsingGPGGA(char *Data);
static void GPS_ParsingGPGSV(char *Data);
static void GPS_ParsingGPRMC(char *Data);


static void GPS_SeperateField(char *Data, char **Fields);
static void GPS_Display(void);



char GPS_Buffer[80];
char * pNMEA_Field[20];   // NMEA�� �������� ������ �ʵ��� ù��° �ּ� 


ST_NMEA NMEA_Data;


void GPS_App(void)
{
	Event_RegisterCallBack(EVENT_UART,0,GPS_UARTCallback);
}

static void GPS_UARTCallback(Event_t Event, uint16_t Arg)
{
	static uint8_t State = 0;   // 0 : '$' ��ٸ��� ����,  1 : '*' ��ٸ��� ����,   2 : CheckSum ��ٸ��� ����
 	static uint8_t Checksum_Cal = 0;
 	static uint8_t Checksum_Data;
 
 	static uint8_t Count;
 
	 switch(State)
	 {
		  case 0 :
		   if(Arg == '$')
		   {
			    State = 1;
			    Count = 0;
			    Checksum_Cal = 0;
		   }
		   break;
		  case 1 :
		   if(Arg == '*')
		   {
			    // ���߿� ���ڿ� ���������� ���� '\0' �� �־��� 
			    GPS_Buffer[Count] = 0; 
			    Checksum_Data = 0;
			    State = 2;
		   // Count = 0;
		    break;
		   }
			   // GPS �����͸� ���ۿ� ���� 
			   GPS_Buffer[Count] = Arg;
			   Count++;
			   // Checksum�� ���� �����͸� Exclusive OR ����. 
			   Checksum_Cal ^=Arg;
		   break;
		  case 2 :
		   // <CR> �� �˻��Ѵ�. 
		   if(Arg == '\r')
		   {
			    // äũ�� �˻� 
			    if(Checksum_Data == Checksum_Cal) 
			    {
			   //  UART_PutHexa(Checksum_Cal);
			     GPS_Parsing(GPS_Buffer);
			    }
			    State = 0;
		   }
		   else 
		   {
			    // Checksum�� ���� 
			    Checksum_Data <<= 4;
			    Checksum_Data += ((Arg - '0') < 10) ? (Arg - '0') : (Arg - 'A' + 10);
		   }
		   break;
		  default :


		   break;

 }
}

static void GPS_Parsing(char *Data)
{
	// NMEA ������� ���� �����͸� �Ľ��Ѵ�. 
	 if((Data[0] == 'G') && (Data[1] == 'P') && (Data[2] == 'G') && (Data[3] == 'G') && (Data[4] == 'A'))
	 {
	  	GPS_ParsingGPGGA(Data);
	 }
	 else if((Data[0] == 'G') && (Data[1] == 'P') && (Data[2] == 'G') && (Data[3] == 'S') && (Data[4] == 'V'))
	 {
	  	GPS_ParsingGPGSV(Data);
	 }
	 else if((Data[0] == 'G') && (Data[1] == 'P') && (Data[2] == 'R') && (Data[3] == 'M') && (Data[4] == 'C'))
	 {
	  	GPS_ParsingGPRMC(Data);
	 }
}


static void GPS_ParsingGPGGA(char *Data)
{
	
	/*
	 -----------------------------------------------------------------------------
	 Field Name 	Example  Unit Description
	 -----------------------------------------------------------------------------
	 0	Message ID	  $GPGGA  GGA  protocol header
	 1	UTC Time	161229.487	 hhmmss.sss
	 2	Latitude	3723.2475	ddmm.mmmm
	 3	N/S Indicator	N	  N=north or S=south
	 4	Longitude	 12158.3416   dddmm.mmmm
	 5	E/W Indicator	W	  E=east or W=west
	 6	Position Fix Indicator 1	 See Table 1-4
	 7	Satellites Used   07	 Range 0 to 12
	 8	HDOP	 1.0	 Horizontal Dilution of Precision
	 9	MSL Altitude   9.0	 meters 
	 10  Units	   M   meters 
	 11  Geoid Separation	  meters 
	 12  Units	   M   meters 
	 13  Age of Diff. Corr	   second Null fields when DGPS is not used
	 14  Diff. Ref. Station ID 0000  
	   Checksum    *18	
	   <CR><LF> 		End of message termination
	 -----------------------------------------------------------------------------
	 [$GPGGA] $GPGGA,084816.000,3728.6289,N,12652.8449,E,1,09,0.9,89.4,M,19.3,M,,0000*69
	 -----------------------------------------------------------------------------
	 */
	 char Buffer[5];
	 RTC_Time_t Time;
	
	
	 // NMEA �����͸� Field ���� ����� �� �ʵ��� ù��° ���ڿ� �ּҸ� Field�� �޾ƿ´�. 
	 GPS_SeperateField(Data, pNMEA_Field);
	
	
	 // �� ���
	 Buffer[0] = pNMEA_Field[1][0];
	 Buffer[1] = pNMEA_Field[1][1];
	 Buffer[2] = '\0'; 
	 NMEA_Data.Hour = atoi(Buffer);
	 // �� ���
	 Buffer[0] = pNMEA_Field[1][2];
	 Buffer[1] = pNMEA_Field[1][3];
	 Buffer[2] = '\0'; 
	 NMEA_Data.Minute = atoi(Buffer);
	 // �� ���
	 Buffer[0] = pNMEA_Field[1][4];
	 Buffer[1] = pNMEA_Field[1][5];
	 Buffer[2] = '\0'; 
	 NMEA_Data.Second = atoi(Buffer); 
	
	
	 Time.Hour = NMEA_Data.Hour;
	 Time.Minute = NMEA_Data.Minute;
	 Time.Second = NMEA_Data.Second;
	 
	 RTC_SetTime(Time);
	
	
	 // ���� ���
	 Buffer[0] = pNMEA_Field[2][0];  // �� ��� 
	 Buffer[1] = pNMEA_Field[2][1];
	 Buffer[2] = '\0'; 
	 NMEA_Data.Latitude = atof(Buffer); 
	 // ����  Degree ������ ��� 
	 NMEA_Data.Latitude += (atof(&pNMEA_Field[2][2]) / 60.0) ; 
	
	
	 // North / South
	 NMEA_Data.N_S = pNMEA_Field[3][0];
	
	
	 // �浵 ���
	 Buffer[0] = pNMEA_Field[4][0];  // �� ��� 
	 Buffer[1] = pNMEA_Field[4][1];
	 Buffer[2] = pNMEA_Field[4][2]; 
	 Buffer[3] = '\0'; 
	 NMEA_Data.Longitude = atof(Buffer); 
	 // ����  Degree ������ ��� 
	 NMEA_Data.Longitude += (atof(&pNMEA_Field[2][3]) / 60.0) ;  
	
	
	 // East / West
	 NMEA_Data.E_W = pNMEA_Field[5][0];
	  
	 NMEA_Data.Altitude = atof(pNMEA_Field[9]);
	
	
	
	
	 GPS_Display();
}

static void GPS_ParsingGPGSV(char *Data)
{
}
static void GPS_ParsingGPRMC(char *Data)
{
	
	/*
	-----------------------------------------------------------------------------
	Field  Name 	Example  Unit Description
	-----------------------------------------------------------------------------
	0  Message ID	 $GPGSA    RMC protocol header
	1  UTC Time    161229.487	hhmmss.sss
	2  Status A 		A=data valid or V=data not valid
	3  Latitude    3723.2475   ddmm.mmmm
	4  N/S Indicator   N	 N=north, S=south
	5  Longitude	12158.3416	 ddd mm.mmmm
	6  E/W Indicator   W	 E=east or W=west
	7  Speed Over Ground  0.13	knots 
	8  Course Over Ground  309.62  degrees true
	9  Date 	120598	  ddmmyy
	10	Magnetic Variation	   degrees E=east or W=west
	11	Mode	 A	   A=Autonomous, D=DGPS, E=DR
	  Checksum *10	
	  <CR><LF>		   End of message termination
	-----------------------------------------------------------------------------
	*/
	
	
	char Buffer[8];
	
	
	// NMEA �����͸� Field ���� ����� �� �ʵ��� ù��° ���ڿ� �ּҸ� Field�� �޾ƿ´�. 
	GPS_SeperateField(Data, pNMEA_Field);
	
	
	// �� ���
	Buffer[0] = pNMEA_Field[1][0];
	Buffer[1] = pNMEA_Field[1][1];
	Buffer[2] = '\0'; 
	NMEA_Data.Hour = atoi(Buffer);
	// �� ���
	Buffer[0] = pNMEA_Field[1][2];
	Buffer[1] = pNMEA_Field[1][3];
	Buffer[2] = '\0'; 
	NMEA_Data.Minute = atoi(Buffer);
	// �� ���
	Buffer[0] = pNMEA_Field[1][4];
	Buffer[1] = pNMEA_Field[1][5];
	Buffer[2] = '\0'; 
	NMEA_Data.Second = atoi(Buffer); 
	
	
	// ���� ���
	Buffer[0] = pNMEA_Field[3][0];	// �� ��� 
	Buffer[1] = pNMEA_Field[3][1];
	Buffer[2] = '\0'; 
	NMEA_Data.Latitude = atof(Buffer); 
	// ����  Degree ������ ��� 
	NMEA_Data.Latitude += (atof(&pNMEA_Field[3][2]) / 60.0) ; 
	
	
	// North / South
	NMEA_Data.N_S = pNMEA_Field[4][0];
	
	
	// �浵 ���
	Buffer[0] = pNMEA_Field[5][0];	// �� ��� 
	Buffer[1] = pNMEA_Field[5][1];
	Buffer[2] = pNMEA_Field[5][2]; 
	Buffer[3] = '\0'; 
	NMEA_Data.Longitude = atof(Buffer); 
	// ����  Degree ������ ��� 
	NMEA_Data.Longitude += (atof(&pNMEA_Field[5][3]) / 60.0) ;	
	
	
	// East / West
	NMEA_Data.E_W = pNMEA_Field[6][0];
	
	
	// �ӵ�  
	NMEA_Data.SpeedOfGound = atof(pNMEA_Field[7]);
	
	
	// ��¥(��) 
	Buffer[0] = pNMEA_Field[9][0];
	Buffer[1] = pNMEA_Field[9][1];
	Buffer[2] = '\0';  
	NMEA_Data.Day = atoi(Buffer);
	UART_PutChar(Buffer[0]);
	UART_PutChar(Buffer[1]);
	UART_PutChar(Buffer[2]);
	UART_PutChar(Buffer[3]);
	
	// ��¥(��) 
	Buffer[0] = pNMEA_Field[9][2];
	Buffer[1] = pNMEA_Field[9][3];
	Buffer[2] = '\0';  
	NMEA_Data.Month= atoi(Buffer);
	// ��¥(��) 
	Buffer[0] = '2';
	Buffer[1] = '0'; 
	Buffer[2] = pNMEA_Field[9][4];
	Buffer[3] = pNMEA_Field[9][5];
	Buffer[4] = '\0';  
	NMEA_Data.Year = atoi(Buffer);
	
	
	GPS_Display();
}


static void GPS_SeperateField(char *Data, char **Fields)
{
	uint8_t i, FieldCount = 0;


	Fields[FieldCount++] = Data;
	 
	for(i = 0; Data[i];i++)
	{
		if(Data[i] == ',')
		{
			Data[i] = '\0';  // ���ڿ� ����� ���� 0�� �ִ´�. 
			Fields[FieldCount++] = &Data[i + 1];
		}
	}
}
static void GPS_Display(void)
{
	LCD_WriteString(56, 8, "< GPS ���� �׽�Ʈ >", YELLOW, BLACK);


 // GPGGA
 LCD_WriteString(32, 40, "[GPGGA ������] ", YELLOW, BLACK);
 LCD_WriteString(8, 56, " - UTC �ð� :", YELLOW, BLACK);
 LCD_WriteEnglish(120, 56, NMEA_Data.Hour / 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(128, 56, NMEA_Data.Hour % 10 + '0', YELLOW, BLACK);
 LCD_WriteString(136, 56, "��", YELLOW, BLACK);
 LCD_WriteEnglish(160, 56, NMEA_Data.Minute/ 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(168, 56, NMEA_Data.Minute % 10 + '0', YELLOW, BLACK);
 LCD_WriteString(176, 56, "��", YELLOW, BLACK);
 LCD_WriteEnglish(200, 56, NMEA_Data.Second/ 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(208, 56, NMEA_Data.Second % 10 + '0', YELLOW, BLACK);
 LCD_WriteString(216, 56, "��", YELLOW, BLACK);
 
 LCD_WriteString(8, 72, " - ���� :", YELLOW, BLACK);
 LCD_SetLocation(120 , 72);
 LCD_Printf("%.2f %c",NMEA_Data.Latitude, NMEA_Data.N_S);
 
 LCD_WriteString(8, 88, " - �浵 :", YELLOW, BLACK);
 LCD_SetLocation(120 , 88);
 LCD_Printf("%.2f %c",NMEA_Data.Longitude, NMEA_Data.E_W);
 
 LCD_WriteString(8, 104, " - �� :", YELLOW, BLACK);
 LCD_SetLocation(120 , 104);
 LCD_Printf("%.2f M     ",NMEA_Data.Altitude); 


 
 // GPRMC
 LCD_WriteString(32, 136, "[GPRMC ������] ", YELLOW, BLACK); 
 LCD_WriteString(8, 152, " - �ӵ� :", YELLOW, BLACK);
 LCD_SetLocation(120 , 152);
 LCD_Printf("%.1f knots",NMEA_Data.SpeedOfGound);
 
 LCD_WriteString(8, 168, " - ��¥ :", YELLOW, BLACK);
 LCD_WriteEnglish(120, 168, NMEA_Data.Year / 1000 % 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(128, 168, NMEA_Data.Year / 100 % 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(136, 168, NMEA_Data.Year / 10 % 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(144, 168, NMEA_Data.Year % 10 + '0', YELLOW, BLACK);
 LCD_WriteString(152, 168, "��", YELLOW, BLACK);
 LCD_WriteEnglish(168, 168, NMEA_Data.Month / 10 % 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(176, 168, NMEA_Data.Month % 10 + '0', YELLOW, BLACK);
 LCD_WriteString(184, 168, "��", YELLOW, BLACK);
 LCD_WriteEnglish(200, 168, NMEA_Data.Day / 10 % 10 + '0', YELLOW, BLACK);
 LCD_WriteEnglish(208, 168, NMEA_Data.Day % 10 + '0', YELLOW, BLACK);
 LCD_WriteString(216, 168, "��", YELLOW, BLACK);
}

