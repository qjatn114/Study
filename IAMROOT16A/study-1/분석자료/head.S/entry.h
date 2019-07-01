#include <stdio.h>


/*
	ENTRY는 심볼을 링커에게 제공(.globl)하는 역할과 심볼을 정렬(align)하는 역할을 한다. 
*/
#ifndef _ENTRY_H_
#define _ENTRY_H_(name)	\
	.globl name ASM_NL	\
	ALIGN ASM_NL	\
	name:
#endif

#ifndef _END_H_
#define _END_H_(name)	\
	.size name, .-name
#endif

/*
	ENDPROC은 심볼이 함수임을 알려주고 심볼의 크기를 계산한다.
*/
#ifndef _ENDPROC_H_
#define _ENDPROC_H_
	.type name, @function ASM_NL	\
	_END_H_(name)
#endif
