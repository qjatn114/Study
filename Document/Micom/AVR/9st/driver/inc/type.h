#ifndef _TYPE_H_
#define _TYPE_H_

#include <stdint.h>

/* stdint.h 에 이미 정의가 되어 있음 
typedef unsigned char		uint8_t;
typedef signed char			int8_t;
typedef unsigned short		uint16_t;
typedef signed short		int16_t;
typedef signed long			int32_t;
typedef unsigned long		uint32_t;
*/

#define NULL	(void *)0

typedef enum{TRUE = 1, FALSE = 0}TruthState_t;
typedef enum {ON = 1, OFF = 0}ActiveState_t;


#endif
