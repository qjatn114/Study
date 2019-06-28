/* CAN Transmit Example
** 
**
** Ported to the Digilent Basys MX3 and PmodCAN
** Richard W. Wall
** July 8, 2017
** 
** Based on example code and CAN library functions
** Posted at https://github.com/Seeed-Studio/CAN_BUS_Shield/tree/master/examples
**
**  Based on code published at:
**  https://github.com/Seeed-Studio/CAN_BUS_Shield
*/

#include <arduino.h>
#include "hardware.h"     // Basys MX3 common hardware pin assignments
#include "LCDBBlib.h"     // Bit banged LCD library
#include "led7.h"         // 4 digit 7 segment LED library
#include "swDelay.h"      // Software delays
#include "MCP_CAN.h"      // MCP25625 library
#include "MCP_CAN_DFS.h"  // MCP25625 definitions
#include "spiJA.h"        // SPI2 library

#define CAN0_INT 35       // Set INT to pin 35 (RC3)
MCP_CAN CAN0(10);         // Set CS to pin 10

static int msg_cntr = 0;  // Message number 
byte data[8] = {0x00, 0x00, 0x00, 0x00, 'W', 'a', 'l', 'l'};  // CAN message buffer

extern int16_t led_value; // 4 digit 7 segment dispaly value
extern int16_t led_flag;  // 4 digit 7 segment dispaly on-off contro

void setup()
{
  Serial.begin(38400);
  lcdInit();
  lcdPuts("CAN Tx Demo");
  seg7Init();               // Turn on 7 segment displays

  // Initialize MCP25625 running at 20MHz with a baudrate of 250kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_20MHZ) == CAN_OK) 
    Serial.println("MCP25625 Initialized Successfully!");
  else 
    Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted

  led_flag = 1;                 // Turn on 4 digit 7 segment display
  led_value = 0;                // Set LED display value to zero
}

void loop()
{
char lcdStr[33];    // LCD text buffer

  // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
  byte sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
  if(sndStat == CAN_OK){/
    Serial.print("Message Sent Successfully! Message count =");
  } else {
    Serial.println("Error Sending Message...");
  }

  led_value = msg_cntr % 9999; // 4 digit display

   // Show message count on LCD
  lcdGoto(16);                      // Set LCD cursor to 2nd line
  lcdPuts("                ");      // Clear LCD 2nd line
  lcdGoto(16);                      // Set LCD cursor to 2nd line
  sprintf(lcdStr,"Sending: %d", msg_cntr);  // format string
  lcdPuts(lcdStr);                  // Display count on LCD

  sprintf(lcdStr, " %d", led_value); // Add message count to serial UART string
  Serial.print(lcdStr);
  Serial.println();
  can_counter();
  delay(250);   // send data rate
}

void can_counter(void)
{
  msg_cntr++;
  data[0] = msg_cntr & 0xFF;
  data[1] = (msg_cntr >> 8) & 0xFF;
  data[2] = (msg_cntr >> 16) & 0xFF;
  data[3] = (msg_cntr >> 24) & 0xFF;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
