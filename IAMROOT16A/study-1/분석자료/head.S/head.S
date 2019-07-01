/*
 *  linux/arch/arm/boot/compressed/head.S
 *
 *  Copyright (C) 1996-2002 Russell King
 *  Copyright (C) 2004 Hyok S. Choi (MPU support)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/linkage.h>

/*
 * Debugging stuff
 *
 * Note that these macros must not contain any code which is not
 * 100% relocatable.  Any attempt to do so will result in a crash.
 * Please select one of the following when turning on debugging.
 */
#ifdef DEBUG

#if defined(CONFIG_DEBUG_ICEDCC)

#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K) || defined(CONFIG_CPU_V7)
		.macro	loadsp, rb, tmp
		.endm
		.macro	writeb, ch, rb
		mcr	p14, 0, \ch, c0, c5, 0
		.endm
#elif defined(CONFIG_CPU_XSCALE)
		.macro	loadsp, rb, tmp
		.endm
		.macro	writeb, ch, rb
		mcr	p14, 0, \ch, c8, c0, 0
		.endm
#else
		.macro	loadsp, rb, tmp
		.endm
		.macro	writeb, ch, rb
		mcr	p14, 0, \ch, c1, c0, 0
		.endm
#endif

#else

#include <mach/debug-macro.S>

		(.macro	writeb,	ch, rb
		senduart \ch, \rb
		.endm

#if defined(CONFIG_ARCH_SA1100)
		.macro	loadsp, rb, tmp
		mov	\rb, #0x80000000	@ physical base address
#ifdef CONFIG_DEBUG_LL_SER3
		add	\rb, \rb, #0x00050000	@ Ser3
#else
		add	\rb, \rb, #0x00010000	@ Ser1
#endif
		.endm
#elif defined(CONFIG_ARCH_S3C2410)
		.macro loadsp, rb, tmp
		mov	\rb, #0x50000000
		add	\rb, \rb, #0x4000 * CONFIG_S3C_LOWLEVEL_UART_PORT
		.endm
#else
		.macro	loadsp,	rb, tmp
		addruart \rb, \tmp
		.endm
#endif
#endif
#endif

		.macro	kputc,val
		mov	r0, \val
		bl	putc
		.endm

		.macro	kphex,val,len
		mov	r0, \val
		mov	r1, #\len
		bl	phex
		.endm

		.macro	debug_reloc_start
#ifdef DEBUG
		kputc	#'\n'
		kphex	r6, 8		/* processor id */
		kputc	#':'
		kphex	r7, 8		/* architecture id */
#ifdef CONFIG_CPU_CP15
		kputc	#':'
		mrc	p15, 0, r0, c1, c0
		kphex	r0, 8		/* control reg */
#endif
		kputc	#'\n'
		kphex	r5, 8		/* decompressed kernel start */
		kputc	#'-'
		kphex	r9, 8		/* decompressed kernel end  */
		kputc	#'>'
		kphex	r4, 8		/* kernel execution address */
		kputc	#'\n'
#endif
		.endm

		.macro	debug_reloc_end
#ifdef DEBUG
		kphex	r5, 8		/* end of kernel */
		kputc	#'\n'
		mov	r0, r4
		bl	memdump		/* dump 256 bytes at start of kernel */
#endif
		.endm
//debug end

		.section ".start", #alloc, #execinstr			@ .section -> vmlinuz.lds파일안의  .start 섹션 연결(배치)
														@ 속성 alloc -> the section is allocatable
														@ 			 -> 램주소 어느 부분에 올라가도 동작 가능하다
														@ 속성 execinstr -> thes section is executable

/*
 * sort out different calling conventions
 */
		.align											@ 주소 32bit align , byte 단위로 padding
		.arm				@ Always enter in ARM state	@ thum mode인지 arm mode인지 구분
start:
		.type	start,#function							@ start 타입은 함수다??
		.rept	7										@ .rept 에서 .endr 까지 7번 반복
		mov	r0, r0										@ pipeline 단계를 초기화 하기 위해서 사용,i-cache도 초기화
														@ 예전에는 nop명령어 없어서 mov 명령어 사용
		.endr									
   ARM(		mov	r0, r0		)							@ ARM mode일 때 실행되는 코드
   ARM(		b	1f		)								@ branch foward 1: 밑에있는 첫번째로 1: jump
 THUMB(		adr	r12, BSYM(1f)	)						@ Thumb mode일 때 실행되는 코드
 THUMB(		bx	r12		)

		.word	0x016f2818		@ Magic numbers to help the loader
		.word	start			@ absolute load/run zImage address
		.word	_edata			@ zImage end address
 THUMB(		.thumb			)
1:		mov	r7, r1			@ save architecture ID		@ boot loader에서 받은 r1값을 r7으로 이동
		mov	r8, r2			@ save atags pointer		@ boot loader에서 받은 r2값(board 정보??)을 r8으로 이동

#ifndef __ARM_ARCH_2__
		/*
		 * Booting from Angel(부트로더 이름) - need to enter SVC mode and disable
		 * FIQs/IRQs (numeric definitions from angel arm.h source).
		 * We only do this if we were in user mode on entry.
		 */
		mrs	r2, cpsr		@ get current mode
		tst	r2, #3			@ not user?					@ test(&연산) 유저모드가 아닌가? (하위 2bit가 00이 아닌가?)
		bne	not_angel									@ 유저모드가 아니면 (privileged모드이면) not_anagel: 로분기
		mov	r0, #0x17		@ angel_SWIreason_EnterSVC	@ r0에 abort신호값 넣어줌(핸들러에서 사용하기위해)
 ARM(		swi	0x123456	)	@ angel_SWI_ARM			@ 소프트웨어 인터럽트 -> SVC 모드로 전환
 THUMB(		svc	0xab		)	@ angel_SWI_THUMB
not_angel:
		mrs	r2, cpsr		@ turn off interrupts to	@ cpsr값을 r2에 저장, IRQ,FIQ disable
		orr	r2, r2, #0xc0		@ prevent angel from running
		msr	cpsr_c, r2
#else
		teqp	pc, #0x0c000003		@ turn off interrupts
#endif

		/*
		 * Note that some cache flushing and other stuff may
		 * be needed here - is there an Angel SWI call for this?
		 */

		/*
		 * some architecture specific code can be inserted
		 * by the linker here, but it should preserve r7, r8, and r9.
		 */

		.text														@ .text 섹션 정의

#ifdef CONFIG_AUTO_ZRELADDR
		@ determine final kernel image address
		mov	r4, pc
		and	r4, r4, #0xf8000000
		add	r4, r4, #TEXT_OFFSET
#else
		ldr	r4, =zreladdr											@ 커널 올릴 주소 (base 주소)
																	@ ex) arch/arm/[soc]/makefile.boot
#endif

		bl	cache_on												@ cache_on으로 분기

@ __armv7_mmu_cache_on: 수행 후 리턴됨
restart:	adr	r0, LC0 				@ LC0 레이블의 주소 값을 r0에 저장한다.
		@ r1 : LC0
		@ r2 : __bss_start
		@ r3 : _end
		@ r6 : _edata : data 영역에 마지막 부분
		@ r10 : input_data_end - 4 : 
		@ r11 : _got_start
		@ r12(ip) : _got_end
		ldmia	r0, {r1, r2, r3, r6, r10, r11, r12} 	@ LC0 레이블에 있는 값을 읽어서 r1 ~ r12까지의 레지스터에 저장한다.
		ldr	sp, [r0, #28] 				@ r0 + 28(.L_user_stack_end)한 주소 값을 sp에 저장한다.

		/*
		 * We might be running at a different address.  We need
		 * to fix up various pointers.
		 */
		sub	r0, r0, r1		@ calculate the delta offset 		@ 다른 주소에서 실행될 경우에 대비해 offset을 계산한다.
		add	r6, r6, r0		@ _edata				@ 계산된 offset 만큼 더해준다.
		@ inflated???? 알아보기
		add	r10, r10, r0		@ inflated kernel size location		@ 계산된 offset 만큼 더해준다.

		/*
		 * The kernel build system appends the size of the
		 * decompressed kernel at the end of the compressed data
		 * in little-endian form.
		 */
		@ 참고 url : stackoverflow.com/questions/4286671/endianness-conversion-in-arm
		@ 0x78563412 (리틀 엔디안 예시 값) (빅엔디안 값은 0x12345678)
		@ (확인 요망 : 메모리의 있는 값을 레지스터로 로드하는데 레지스터는 엔디안이랑 상관 없다.)
		@ (확인 요망 : ldrb는 armv6 이상의 버전에서는 빅엔디안이던 리틀 엔디안이던 상관없이 동일한 값을 가져온다. )
		@ (위에서 빅엔디안의 0x78을 가져오면 리틀 엔디안에서도 0x78을 가져 온다.)
		@ (ldr하고 ldrb의 처리하는 것이 차이가 있고, ARM 버전 별로 다르다.)

		@ r9의 압축이 풀린 사이즈의 값을 저장한다.

		ldrb	r9, [r10, #0]		@ r10(input_data_end - 4)의 주소값에 저장되어 있는 1바이트(마지막 바이트) 값을 r9에 로드한다. (예로 위의 값의 0x78만 로드 된다.)
		ldrb	lr, [r10, #1]		@ lr = 0x56가 로드됨
		orr	r9, r9, lr, lsl #8	@ 엔디안 변환 0x5678
		ldrb	lr, [r10, #2]		@ lr = 0x34
		ldrb	r10, [r10, #3]		@ r10 = 0x12
		orr	r9, r9, lr, lsl #16	@ r9 = 0x345678
		orr	r9, r9, r10, lsl #24	@ r9 = 0x12345678

#ifndef CONFIG_ZBOOT_ROM  @ 여기로 들어온다.
		/* malloc space is above the relocated stack (64k max) */
		add	sp, sp, r0		@ sp에 .L_user_stack_end + offset을 넣는다.
		add	r10, sp, #0x10000	@ r10 = sp + 0x10000
#else
		/*
		 * With ZBOOT_ROM the bss/stack is non relocatable,
		 * but someone could still run this code from RAM,
		 * in which case our reference is _edata.
		 */
		mov	r10, r6
#endif

/*
 * Check to see if we will overwrite ourselves.
 *   r4  = final kernel address
 *   r9  = size of decompressed image
 *   r10 = end of this image, including  bss/stack/malloc space if non XIP
 * We basically want:
 *   r4 - 16k page directory >= r10 -> OK
 *   r4 + image length <= current position (pc) -> OK
 */
		@ r4 : 커널을 올릴 주소
		@ r10 : 압축 풀기 이전에 이미지의 마지막 주소
		@ r4 - 16k > r10 : 이미지가 커널 올릴 주소 앞에 있기 때문에, 겹치지 않는다.
		@ 이경우 bhs wont_overwrite 수행
		
		add	r10, r10, #16384	@ r10 = r10 + 0x4000(0x4000 = 16384)
		cmp	r4, r10			@ r4 = zrealloc address, 커널을 올릴 주소
		bhs	wont_overwrite		@ r4 - 16k page directory >= r10 -> branch

		add	r10, r4, r9
		@ r10 : 커널이 압축이 풀린 후의 마지막 주소
		@ pc : 현재 코드의 주소(압축 풀리기 이전의 이미지)
		@ r10 > pc : 압축이 풀린 마지막 주소보다 현재 pc가 뒤에 있기 때문에 겹치지 않는다.
		@ 이경우 bhs wont_overwrite 수행
   ARM(		cmp	r10, pc		)
 THUMB(		mov	lr, pc		)
 THUMB(		cmp	r10, lr		)
		bls	wont_overwrite		@ r10 <= pc -> branch

/*
 * Relocate ourselves past the end of the decompressed kernel.
 *   r6  = _edata
 *   r10 = end of the decompressed kernel
 * Because we always copy ahead, we need to do it from the end and go
 * backward in case the source and destination overlap.
 */
		/*
		 * Bump to the next 256-byte boundary with the size of
		 * the relocation code added. This avoids overwriting
		 * ourself when the offset is small.
		 */
		add	r10, r10, #((reloc_code_end - restart + 256) & ~255)
		bic	r10, r10, #255

		/* Get start of code we want to copy and align it down. */
		adr	r5, restart
		bic	r5, r5, #31

		sub	r9, r6, r5		@ size to copy
		add	r9, r9, #31		@ rounded up to a multiple
		bic	r9, r9, #31		@ ... of 32 bytes
		add	r6, r9, r5
		add	r9, r9, r10

1:		ldmdb	r6!, {r0 - r3, r10 - r12, lr}
		cmp	r6, r5
		stmdb	r9!, {r0 - r3, r10 - r12, lr}
		bhi	1b

		/* Preserve offset to relocated code. */
		sub	r6, r9, r6

#ifndef CONFIG_ZBOOT_ROM
		/* cache_clean_flush may use the stack, so relocate it */
		add	sp, sp, r6
#endif

		bl	cache_clean_flush

		adr	r0, BSYM(restart)
		add	r0, r0, r6
		mov	pc, r0

wont_overwrite:
/*
 * If delta is zero, we are running at the address we were linked at.
 *   r0  = delta
 *   r2  = BSS start
 *   r3  = BSS end
 *   r4  = kernel execution address
 *   r7  = architecture ID
 *   r8  = atags pointer
 *   r11 = GOT start
 *   r12 = GOT end
 *   sp  = stack pointer
 */
		teq	r0, #0
		beq	not_relocated 		@ r0(offset)의 값이 0이면 branch
		add	r11, r11, r0
		add	r12, r12, r0

#ifndef CONFIG_ZBOOT_ROM
		/*
		 * If we're running fully PIC === CONFIG_ZBOOT_ROM = n,
		 * we need to fix up pointers into the BSS region.
		 * Note that the stack pointer has already been fixed up.
		 */
		add	r2, r2, r0
		add	r3, r3, r0

		/*
		 * Relocate all entries in the GOT table.
		 */
1:		ldr	r1, [r11, #0]		@ relocate entries in the GOT
		add	r1, r1, r0		@ table.  This fixes up the
		str	r1, [r11], #4		@ C references.
		cmp	r11, r12
		blo	1b
#else

		/*
		 * Relocate entries in the GOT table.  We only relocate
		 * the entries that are outside the (relocated) BSS region.
		 */
1:		ldr	r1, [r11, #0]		@ relocate entries in the GOT
		cmp	r1, r2			@ entry < bss_start ||
		cmphs	r3, r1			@ _end < entry
		addlo	r1, r1, r0		@ table.  This fixes up the
		str	r1, [r11], #4		@ C references.
		cmp	r11, r12
		blo	1b
#endif

not_relocated:	mov	r0, #0
		@ bss 영역을 0으로 클리어
1:		str	r0, [r2], #4		@ clear bss
		str	r0, [r2], #4
		str	r0, [r2], #4
		str	r0, [r2], #4
		cmp	r2, r3			@ r2(bss_start)부터 r3(bss_end)까지 루프를 돌며 초기화 
		blo	1b

/*
 * The C runtime environment should now be setup sufficiently.
 * Set up some pointers, and start decompressing.
 *   r4  = kernel execution address
 *   r7  = architecture ID
 *   r8  = atags pointer
 */
		@ 함수의 인자값으로 넣어주기위해 r0, r1, r2, r3로 값을 옮겨 준다.
		mov	r0, r4							@ r0 = r4(커널이 풀리는 주소)
		mov	r1, sp			@ malloc space above stack	@ r1 = sp(.L_user_stack_end + offset)
		add	r2, sp, #0x10000	@ 64k max			@ r2 = sp + 0x10000(64k)
		mov	r3, r7							@ r3 = r7(부트로더로부터 받은 아키텍쳐 아이디)
		bl	decompress_kernel					@ 커널 압축 해제
		bl	cache_clean_flush
		bl	cache_off						@ __armv7_mmu_cache_off로 branch
		mov	r0, #0			@ must be zero
		mov	r1, r7			@ restore architecture number
		mov	r2, r8			@ restore atags pointer
		mov	pc, r4			@ call kernel

		.align	2			@ arch에 따라 다르다. 2^2로 align된다.(4로 align되는 것)
		.type	LC0, #object
		@ LC : Location Counter
LC0:		.word	LC0			@ r1
		.word	__bss_start		@ r2
		.word	_end			@ r3
		.word	_edata			@ r6
		.word	input_data_end - 4	@ r10 (inflated size location)
		.word	_got_start		@ r11
		.word	_got_end		@ ip
		.word	.L_user_stack_end	@ sp 
		.size	LC0, . - LC0

#ifdef CONFIG_ARCH_RPC
		.globl	params
params:		ldr	r0, =0x10000100		@ params_phys for RPC
		mov	pc, lr

		.ltorg
		.align
#endif

/*
 * Turn on the cache.  We need to setup some page tables so that we
 * can have both the I and D caches on.
 *
 * We place the page tables 16k down from the kernel execution address,
 * and we hope that nothing else is using it.  If we're using it, we
 * will go pop!
 *
 * On entry,
 *  r4 = kernel execution address
 *  r7 = architecture number
 *  r8 = atags pointer
 * On exit,
 *  r0, r1, r2, r3, r9, r10, r12 corrupted
 * This routine must preserve:
 *  r4, r7, r8
 */
		.align	5
cache_on:	mov	r3, #8			@ cache_on function	/ 만약 #12 이면 cache_off fuction 수행/ #16 이면 cache_flush function 수행
		b	call_cache_fn

/*
 * Initialize the highest priority protection region, PR7
 * to cover all 32bit address and cacheable and bufferable.
 */
__armv4_mpu_cache_on:
		mov	r0, #0x3f		@ 4G, the whole
		mcr	p15, 0, r0, c6, c7, 0	@ PR7 Area Setting
		mcr 	p15, 0, r0, c6, c7, 1

		mov	r0, #0x80		@ PR7
		mcr	p15, 0, r0, c2, c0, 0	@ D-cache on
		mcr	p15, 0, r0, c2, c0, 1	@ I-cache on
		mcr	p15, 0, r0, c3, c0, 0	@ write-buffer on

		mov	r0, #0xc000
		mcr	p15, 0, r0, c5, c0, 1	@ I-access permission
		mcr	p15, 0, r0, c5, c0, 0	@ D-access permission

		mov	r0, #0
		mcr	p15, 0, r0, c7, c10, 4	@ drain write buffer
		mcr	p15, 0, r0, c7, c5, 0	@ flush(inval) I-Cache
		mcr	p15, 0, r0, c7, c6, 0	@ flush(inval) D-Cache
		mrc	p15, 0, r0, c1, c0, 0	@ read control reg
						@ ...I .... ..D. WC.M
		orr	r0, r0, #0x002d		@ .... .... ..1. 11.1
		orr	r0, r0, #0x1000		@ ...1 .... .... ....

		mcr	p15, 0, r0, c1, c0, 0	@ write control reg

		mov	r0, #0
		mcr	p15, 0, r0, c7, c5, 0	@ flush(inval) I-Cache
		mcr	p15, 0, r0, c7, c6, 0	@ flush(inval) D-Cache
		mov	pc, lr

__armv3_mpu_cache_on:
		mov	r0, #0x3f		@ 4G, the whole
		mcr	p15, 0, r0, c6, c7, 0	@ PR7 Area Setting

		mov	r0, #0x80		@ PR7
		mcr	p15, 0, r0, c2, c0, 0	@ cache on
		mcr	p15, 0, r0, c3, c0, 0	@ write-buffer on

		mov	r0, #0xc000
		mcr	p15, 0, r0, c5, c0, 0	@ access permission

		mov	r0, #0
		mcr	p15, 0, r0, c7, c0, 0	@ invalidate whole cache v3
		/*
		 * ?? ARMv3 MMU does not allow reading the control register,
		 * does this really work on ARMv3 MPU?
		 */
		mrc	p15, 0, r0, c1, c0, 0	@ read control reg
						@ .... .... .... WC.M
		orr	r0, r0, #0x000d		@ .... .... .... 11.1
		/* ?? this overwrites the value constructed above? */
		mov	r0, #0
		mcr	p15, 0, r0, c1, c0, 0	@ write control reg

		/* ?? invalidate for the second time? */
		mcr	p15, 0, r0, c7, c0, 0	@ invalidate whole cache v3
		mov	pc, lr

__setup_mmu:	sub	r3, r4, #16384		@ Page directory size		@ zreladdr 주소 값(kernel base주소)이 r4(0x30008000 - 삼성보드)
																	@ r3에 page directory 주소 설정
		bic	r3, r3, #0xff		@ Align the pointer					@ 상수 오퍼랜드는 12bit 제약이 있다.
		bic	r3, r3, #0x3f00											@ 최대 12bit까지 bit clear 할 수 있어서 2번 나누어 수행한다.
																	@ 16kb(14bit) align 하기 위해서 2번 나누어 수행
/*
 * Initialise the page tables, turning on the cacheable and bufferable
 * bits for the RAM area only.
 */
		mov	r0, r3													@ r3(0x30004000)
		mov	r9, r0, lsr #18											@ r9(0x00000C00)
		mov	r9, r9, lsl #18		@ start of RAM						@ r9(0x30000000)
		add	r10, r9, #0x10000000	@ a reasonable RAM size			@ r10(0x40000000),  0x10000000(256MB)
		mov	r1, #0x12												
		orr	r1, r1, #3 << 10										@ r1 = 0xC12 (0b110000010010) (AP:11, 10: Section Entry)
		add	r2, r3, #16384											@ r2 = 0x30008000
1:		cmp	r1, r9			@ if virt > start of RAM				 
#ifdef CONFIG_CPU_DCACHE_WRITETHROUGH
		orrhs	r1, r1, #0x08		@ set cacheable
#else
		orrhs	r1, r1, #0x0c		@ set cacheable, bufferable		@ if(r1>=r9) set Cacheable, bufferable
#endif
		cmp	r1, r10			@ if virt > end of RAM
		bichs	r1, r1, #0x0c		@ clear cacheable, bufferable
		str	r1, [r0], #4		@ 1:1 mapping  						@ (r1=0xC12) r0 = r1 then r0=r0+4, r1은 page table entry값
		add	r1, r1, #1048576										@ r1 = r1 + 0x100000 
		teq	r0, r2
		bne	1b
/*
 * If ever we are running from Flash, then we surely want the cache
 * to be enabled also for our execution instance...  We map 2MB of it
 * so there is no map overlap problem for up to 1 MB compressed kernel.
 * If the execution is in RAM then we would only be duplicating the above.
 */
		mov	r1, #0x1e												
		orr	r1, r1, #3 << 10										@ r1 = 0xC1e (0b110000011110) Cacheable=1, bufferable=1
		mov	r2, pc													@ r2는 다음에 실행될 명령어의 주소
		mov	r2, r2, lsr #20										 	@ 의미있는 상위 12bit(virtual addr)를 알아내기 위해 r2(pc)>>20
		orr	r1, r1, r2, lsl #20										@ virtual addr과  page table attr or 연산
		add	r0, r3, r2, lsl #2										@ r2>>20은 page table index,  
																	@ page table entry의 주소 = r3(page table addr) + r2*4(오프셋)
																	@ r2는  page table index이다. 
																	@ r3는 page table start addr
		str	r1, [r0], #4											@ r0 = r1, then r0=r0+4
		add	r1, r1, #1048576										@ r1 = r1 + 0x100000
		str	r1, [r0]												@ r0 = r1
		mov	pc, lr													@ pc = lr
ENDPROC(__setup_mmu)

__arm926ejs_mmu_cache_on:
#ifdef CONFIG_CPU_DCACHE_WRITETHROUGH
		mov	r0, #4			@ put dcache in WT mode
		mcr	p15, 7, r0, c15, c0, 0
#endif

__armv4_mmu_cache_on:
		mov	r12, lr
#ifdef CONFIG_MMU
		bl	__setup_mmu
		mov	r0, #0			@
		mcr	p15, 0, r0, c7, c10, 4	@ drain write buffer
		mcr	p15, 0, r0, c8, c7, 0	@ flush I,D TLBs
		mrc	p15, 0, r0, c1, c0, 0	@ read control reg
		orr	r0, r0, #0x5000		@ I-cache enable, RR cache replacement
		orr	r0, r0, #0x0030
#ifdef CONFIG_CPU_ENDIAN_BE8
		orr	r0, r0, #1 << 25	@ big-endian page tables
#endif
		bl	__common_mmu_cache_on
		mov	r0, #0
		mcr	p15, 0, r0, c8, c7, 0	@ flush I,D TLBs
#endif
		mov	pc, r12

__armv7_mmu_cache_on:												@ return register 값은 restart: 주소값이다.
		mov	r12, lr													@ return register 값을 r12 register에 넣는다.
#ifdef CONFIG_MMU
		mrc	p15, 0, r11, c0, c1, 4	@ read ID_MMFR0					@ memory model feature registers
												@ 4 -> 모델 register  4개 중 첫번째(MMFR0) 읽어온다 
		tst	r11, #0xf		@ VMSA				@ virtual memory system architecture / 하위 4bit 와 & 연산
<<<<<<< .mine
		blne	__setup_mmu						@ 
		mov	r0, #0							@ 8/20 분석 시작
		mcr	p15, 0, r0, c7, c10, 4	@ drain write buffer
		tst	r11, #0xf		@ VMSA
		mcrne	p15, 0, r0, c8, c7, 0	@ flush I,D TLBs
=======
		blne	__setup_mmu						@ vmsa 지원 시, __setup_mmu 으로 분기
@ 2011. 8. 20
		mov	r0, #0												@ r0 <- 0
		mcr	p15, 0, r0, c7, c10, 4	@ drain write buffer		@ write buffer 내용을 메모리에 저장
																@ write buffer는 data cache와 main memory 간에
																@ write 동작이 발생할 경우 생기는 병목 현상을
																@ 줄이기 위해 중간에 만들어놓은 버퍼
																@ drain은 wb에서 main memory로의 writing 동작
		tst	r11, #0xf		@ VMSA								@ vmsa 지원 시, 아래의 xxxne 모두 실행
		mcrne	p15, 0, r0, c8, c7, 0	@ flush I,D TLBs		@ all TLB(I TLB, D TLB)를 flush (RD(r0) should be 0)
>>>>>>> .r4
#endif
		mrc	p15, 0, r0, c1, c0, 0	@ read control reg			@ r0 <- System Control Register (SCTLR) (P.1335 참조)
		orr	r0, r0, #0x5000		@ I-cache enable, RR cache replacement	@ RR(1), V(0), I(1)(RoundRobin, Vector, Intruction)
																@ RR: cache 교체 정책을 Round Robin으로
																@ I : Instruction caches enabled
		orr	r0, r0, #0x003c		@ write buffer					@ 111(static), C(1)(Data and unified caches enabled)
																@ data cache를 enable하면 write buffer가 enable된다
																@ (P.1245, P.1367 참조)
#ifdef CONFIG_MMU
#ifdef CONFIG_CPU_ENDIAN_BE8
		orr	r0, r0, #1 << 25	@ big-endian page table			@ 실행되지 않음
#endif
																@ vmsa 지원 시, 아래의 xxxne 모두 실행
		orrne	r0, r0, #1		@ MMU enabled					@ MMU enabled 함
		movne	r1, #-1											@ r1 <- 0xFFFFFFFF
		mcrne	p15, 0, r3, c2, c0, 0	@ load page table pointer		@ c2(TTBR0) <- r3(page table start addr)
																		@ TTBR0 (Translation Table Base Register 0)
		@ 0b11: Manager. Accesses are not checked against the permission bits in the translation tables.
		mcrne	p15, 0, r1, c3, c0, 0	@ load domain access control	@ c3(DACR) <- r1(0xFFFFFFFF)
																		@ DACR (Domain Access Control Register)
#endif
		mcr	p15, 0, r0, c1, c0, 0	@ load control register		@ SCTLR (System Control Register) <- r0 (P.1335 참조)
		mrc	p15, 0, r0, c1, c0, 0	@ and read it back			@ r0 <- System Control Register (SCTLR) (P.1335 참조)
		mov	r0, #0												@ r0 <- 0
		@ ISB 명령어는 기존 파이프라인에 올라간 명령어들이 완료될 때까지
		@ 시스템 컨트롤 레지스터(SCTLR) 이후 들어오는 명령어들을 파이프라인에 적재되지 않도록 보호 후,
		@ 이후 명령어들을 파이프라인에 fetch함
		mcr	p15, 0, r0, c7, c5, 4	@ ISB						@ ISB (Instruction Synchronization Barrier operation)  
																
		mov	pc, r12								@ bl	cache_on 이후로 리턴

__fa526_cache_on:
		mov	r12, lr
		bl	__setup_mmu
		mov	r0, #0
		mcr	p15, 0, r0, c7, c7, 0	@ Invalidate whole cache
		mcr	p15, 0, r0, c7, c10, 4	@ drain write buffer
		mcr	p15, 0, r0, c8, c7, 0	@ flush UTLB
		mrc	p15, 0, r0, c1, c0, 0	@ read control reg
		orr	r0, r0, #0x1000		@ I-cache enable
		bl	__common_mmu_cache_on
		mov	r0, #0
		mcr	p15, 0, r0, c8, c7, 0	@ flush UTLB
		mov	pc, r12

__arm6_mmu_cache_on:
		mov	r12, lr
		bl	__setup_mmu
		mov	r0, #0
		mcr	p15, 0, r0, c7, c0, 0	@ invalidate whole cache v3
		mcr	p15, 0, r0, c5, c0, 0	@ invalidate whole TLB v3
		mov	r0, #0x30
		bl	__common_mmu_cache_on
		mov	r0, #0
		mcr	p15, 0, r0, c5, c0, 0	@ invalidate whole TLB v3
		mov	pc, r12

__common_mmu_cache_on:
#ifndef CONFIG_THUMB2_KERNEL
#ifndef DEBUG
		orr	r0, r0, #0x000d		@ Write buffer, mmu
#endif
		mov	r1, #-1
		mcr	p15, 0, r3, c2, c0, 0	@ load page table pointer
		mcr	p15, 0, r1, c3, c0, 0	@ load domain access control
		b	1f
		.align	5			@ cache line aligned
1:		mcr	p15, 0, r0, c1, c0, 0	@ load control register
		mrc	p15, 0, r0, c1, c0, 0	@ and read it back to
		sub	pc, lr, r0, lsr #32	@ properly flush pipeline
#endif

#define PROC_ENTRY_SIZE (4*5)

/*
 * Here follow the relocatable cache support functions for the
 * various processors.  This is a generic hook for locating an
 * entry and jumping to an instruction at the specified offset
 * from the start of the block.  Please note this is all position
 * independent code.
 *
 *  r1  = corrupted
 *  r2  = corrupted
 *  r3  = block offset
 *  r9  = corrupted
 *  r12 = corrupted
 */

/*
	cp15에서 프로세서ID를 r9로 가져와서 ARM6/610 value값과 일치하는 값을 검색하여 찾은 후,
	proc_types+8 으로 점프한다.

*/

call_cache_fn:	adr	r12, proc_types													@ r12 = proc_types + pc
#ifdef CONFIG_CPU_CP15
		mrc	p15, 0, r9, c0, c0	@ get processor ID 							@ cp15:c0:c0, r9->값을 가져올 장소
#else
		ldr	r9, =CONFIG_PROCESSOR_ID									
#endif
1:		ldr	r1, [r12, #0]		@ get value									@ proc_types + 0 값 가져옴
		ldr	r2, [r12, #4]		@ get mask									@ proc_types + 4 값 가져옴
		eor	r1, r1, r9		@ (real ^ match)								@ r1과 r9를 xor
		tst	r1, r2			@       & mask									@ r1과 r2 &연산
 ARM(		addeq	pc, r12, r3		) @ call cache function					@ 일치하면 proc_types + 8 로 분기
 THUMB(		addeq	r12, r3			)_t
 THUMB(		moveq	pc, r12			) @ call cache function
		add	r12, r12, #PROC_ENTRY_SIZE										@ proc_types = proc_types + proc_entry_size(20byte)
		b	1b																@ branch 1backward 위에서 첫번째 1:(629line) 으로 이동

/*
 * Table for cache operations.  This is basically:
 *   - CPU ID match
 *   - CPU ID mask
 *   - 'cache on' method instruction
 *   - 'cache off' method instruction
 *   - 'cache flush' method instruction
 *
 * We match an entry using: ((real_id ^ match) & mask) == 0
 *
 * Writethrough caches generally only need 'on' and 'off'
 * methods.  Writeback caches _must_ have the flush method
 * defined.
 */
		.align	2
		.type	proc_types,#object
proc_types:
		.word	0x41560600		@ ARM6/610
		.word	0xffffffe0
		W(b)	__arm6_mmu_cache_off	@ works, but slow
		W(b)	__arm6_mmu_cache_off
		mov	pc, lr
 THUMB(		nop				)
@		b	__arm6_mmu_cache_on		@ untested
@		b	__arm6_mmu_cache_off
@		b	__armv3_mmu_cache_flush

		.word	0x00000000		@ old ARM ID
		.word	0x0000f000
		mov	pc, lr
 THUMB(		nop				)
		mov	pc, lr
 THUMB(		nop				)
		mov	pc, lr
 THUMB(		nop				)

		.word	0x41007000		@ ARM7/710
		.word	0xfff8fe00
		W(b)	__arm7_mmu_cache_off
		W(b)	__arm7_mmu_cache_off
		mov	pc, lr
 THUMB(		nop				)

		.word	0x41807200		@ ARM720T (writethrough)
		.word	0xffffff00
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		mov	pc, lr
 THUMB(		nop				)

		.word	0x41007400		@ ARM74x
		.word	0xff00ff00
		W(b)	__armv3_mpu_cache_on
		W(b)	__armv3_mpu_cache_off
		W(b)	__armv3_mpu_cache_flush
		
		.word	0x41009400		@ ARM94x
		.word	0xff00ff00
		W(b)	__armv4_mpu_cache_on
		W(b)	__armv4_mpu_cache_off
		W(b)	__armv4_mpu_cache_flush

		.word	0x41069260		@ ARM926EJ-S (v5TEJ)
		.word	0xff0ffff0
		W(b)	__arm926ejs_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv5tej_mmu_cache_flush

		.word	0x00007000		@ ARM7 IDs
		.word	0x0000f000
		mov	pc, lr
 THUMB(		nop				)
		mov	pc, lr
 THUMB(		nop				)
		mov	pc, lr
 THUMB(		nop				)

		@ Everything from here on will be the new ID system.

		.word	0x4401a100		@ sa110 / sa1100
		.word	0xffffffe0
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv4_mmu_cache_flush

		.word	0x6901b110		@ sa1110
		.word	0xfffffff0
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv4_mmu_cache_flush

		.word	0x56056900
		.word	0xffffff00		@ PXA9xx
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv4_mmu_cache_flush

		.word	0x56158000		@ PXA168
		.word	0xfffff000
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv5tej_mmu_cache_flush

		.word	0x56050000		@ Feroceon
		.word	0xff0f0000
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv5tej_mmu_cache_flush

#ifdef CONFIG_CPU_FEROCEON_OLD_ID
		/* this conflicts with the standard ARMv5TE entry */
		.long	0x41009260		@ Old Feroceon
		.long	0xff00fff0
		b	__armv4_mmu_cache_on
		b	__armv4_mmu_cache_off
		b	__armv5tej_mmu_cache_flush
#endif

		.word	0x66015261		@ FA526
		.word	0xff01fff1
		W(b)	__fa526_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__fa526_cache_flush

		@ These match on the architecture ID

		.word	0x00020000		@ ARMv4T
		.word	0x000f0000
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv4_mmu_cache_flush

		.word	0x00050000		@ ARMv5TE
		.word	0x000f0000
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv4_mmu_cache_flush

		.word	0x00060000		@ ARMv5TEJ
		.word	0x000f0000
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv5tej_mmu_cache_flush

		.word	0x0007b000		@ ARMv6
		.word	0x000ff000
		W(b)	__armv4_mmu_cache_on
		W(b)	__armv4_mmu_cache_off
		W(b)	__armv6_mmu_cache_flush

		.word	0x000f0000		@ new CPU Id		 ARMv7
		.word	0x000f0000
		W(b)	__armv7_mmu_cache_on				@ W(b) , W-> word 의 약자, thumb 명령어라도 32비트 명령어로 바꾼다.
		W(b)	__armv7_mmu_cache_off				@ #define  W(INST)  INST.W
		W(b)	__armv7_mmu_cache_flush				@ b는 branch의 약자. 

		.word	0			@ unrecognised type
		.word	0
		mov	pc, lr
 THUMB(		nop				)
		mov	pc, lr
 THUMB(		nop				)
		mov	pc, lr
 THUMB(		nop				)

		.size	proc_types, . - proc_types

		/*
		 * If you get a "non-constant expression in ".if" statement"
		 * error from the assembler on this line, check that you have
		 * not accidentally written a "b" instruction where you should
		 * have written W(b).
		 */
		.if (. - proc_types) % PROC_ENTRY_SIZE != 0
		.error "The size of one or more proc_types entries is wrong."
		.endif

/*
 * Turn off the Cache and MMU.  ARMv3 does not support
 * reading the control register, but ARMv4 does.
 *
 * On exit,
 *  r0, r1, r2, r3, r9, r12 corrupted
 * This routine must preserve:
 *  r4, r7, r8
 */
		.align	5
cache_off:	mov	r3, #12			@ cache_off function	@ r3 <- 12
		b	call_cache_fn

__armv4_mpu_cache_off:
		mrc	p15, 0, r0, c1, c0
		bic	r0, r0, #0x000d
		mcr	p15, 0, r0, c1, c0	@ turn MPU and cache off
		mov	r0, #0
		mcr	p15, 0, r0, c7, c10, 4	@ drain write buffer
		mcr	p15, 0, r0, c7, c6, 0	@ flush D-Cache
		mcr	p15, 0, r0, c7, c5, 0	@ flush I-Cache
		mov	pc, lr

__armv3_mpu_cache_off:
		mrc	p15, 0, r0, c1, c0
		bic	r0, r0, #0x000d
		mcr	p15, 0, r0, c1, c0, 0	@ turn MPU and cache off
		mov	r0, #0
		mcr	p15, 0, r0, c7, c0, 0	@ invalidate whole cache v3
		mov	pc, lr

__armv4_mmu_cache_off:
#ifdef CONFIG_MMU
		mrc	p15, 0, r0, c1, c0
		bic	r0, r0, #0x000d
		mcr	p15, 0, r0, c1, c0	@ turn MMU and cache off
		mov	r0, #0
		mcr	p15, 0, r0, c7, c7	@ invalidate whole cache v4
		mcr	p15, 0, r0, c8, c7	@ invalidate whole TLB v4
#endif
		mov	pc, lr

		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		@ from cache_off
		@ CP15:C1:C0 : read system control register(SCTLR) -> r0 	
		@ 0xd : 0b1101 -> cache enable bit clear & MMU enable bit clear
		@ cache off(mcr) 후 리턴 addr(cache_off call) r12에 저장 
		@ cache 설정 변경후 MMFR1의 (read only) cache status value도 자동변경 
		@ 되었을 것으로 예상 ?? 
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
__armv7_mmu_cache_off:
		mrc	p15, 0, r0, c1, c0
#ifdef CONFIG_MMU
		bic	r0, r0, #0x000d
#else
		bic	r0, r0, #0x000c
#endif
		mcr	p15, 0, r0, c1, c0	@ turn MMU and cache off
		mov	r12, lr
		@ mmu_cache_flush call_
		bl	__armv7_mmu_cache_flush
		mov	r0, #0
#ifdef CONFIG_MMU
		mcr	p15, 0, r0, c8, c7, 0	@ invalidate whole TLB
#endif
		mcr	p15, 0, r0, c7, c5, 6	@ invalidate BTC
		mcr	p15, 0, r0, c7, c10, 4	@ DSB
		mcr	p15, 0, r0, c7, c5, 4	@ ISB
		mov	pc, r12

__arm6_mmu_cache_off:
		mov	r0, #0x00000030		@ ARM6 control reg.
		b	__armv3_mmu_cache_off

__arm7_mmu_cache_off:
		mov	r0, #0x00000070		@ ARM7 control reg.
		b	__armv3_mmu_cache_off

__armv3_mmu_cache_off:
		mcr	p15, 0, r0, c1, c0, 0	@ turn MMU and cache off
		mov	r0, #0
		mcr	p15, 0, r0, c7, c0, 0	@ invalidate whole cache v3
		mcr	p15, 0, r0, c5, c0, 0	@ invalidate whole TLB v3
		mov	pc, lr

/*
 * Clean and flush the cache to maintain consistency.
 *
 * On exit,
 *  r1, r2, r3, r9, r10, r11, r12 corrupted
 * This routine must preserve:
 *  r4, r6, r7, r8
 */
		.align	5
cache_clean_flush:
		mov	r3, #16 						@ r3 = 16
		b	call_cache_fn						@ __armv7_mmu_cache_flush 여기로 branch된다.

__armv4_mpu_cache_flush:
		mov	r2, #1
		mov	r3, #0
		mcr	p15, 0, ip, c7, c6, 0	@ invalidate D cache
		mov	r1, #7 << 5		@ 8 segments
1:		orr	r3, r1, #63 << 26	@ 64 entries
2:		mcr	p15, 0, r3, c7, c14, 2	@ clean & invalidate D index
		subs	r3, r3, #1 << 26
		bcs	2b			@ entries 63 to 0
		subs 	r1, r1, #1 << 5
		bcs	1b			@ segments 7 to 0

		teq	r2, #0
		mcrne	p15, 0, ip, c7, c5, 0	@ invalidate I cache
		mcr	p15, 0, ip, c7, c10, 4	@ drain WB
		mov	pc, lr
		
__fa526_cache_flush:
		mov	r1, #0
		mcr	p15, 0, r1, c7, c14, 0	@ clean and invalidate D cache
		mcr	p15, 0, r1, c7, c5, 0	@ flush I cache
		mcr	p15, 0, r1, c7, c10, 4	@ drain WB
		mov	pc, lr

__armv6_mmu_cache_flush:
		mov	r1, #0
		mcr	p15, 0, r1, c7, c14, 0	@ clean+invalidate D
		mcr	p15, 0, r1, c7, c5, 0	@ invalidate I+BTB
		mcr	p15, 0, r1, c7, c15, 0	@ clean+invalidate unified
		mcr	p15, 0, r1, c7, c10, 4	@ drain WB
		mov	pc, lr

__armv7_mmu_cache_flush:
                @ Memory model feathure register(MMFR) 
                @ L1 page table - L1 cache 
                @ Page 1486 참조 
		mrc	p15, 0, r10, c0, c1, 5	@ read ID_MMFR1			@ ID_MMFR1의 값을 r10으로 읽어 온다.
		tst	r10, #0xf << 16		@ hierarchical cache (ARMv7)	@ Harvard cache bit[19:16] 중에 전부 0이면 Z 플래그가 1이고, 하나라도 1이면 Z 플래그는 0 
		mov	r10, #0
		beq	hierarchical						@ Harvard cache bit가 전부 0일 때 branch z flag가 1이면 점프 
		mcr	p15, 0, r10, c7, c14, 0	@ clean+invalidate D            @? Data cache invalidate 후 0으로 초기화 
		b	iflush

		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		@
		@ Data Memory Barrier (DMB) : CP15:C7:C10:5 누가 언제 보호를 다시 푸는지 조사 ???
		@ CP15:C0:C0:1 : Cache level ID register(CLIDR) : r0 [26:24]:level of coherency 
		@ CP15:C0:C0:0 : Cache size selection register(CSSR) : R10
		@ Coherency : 메모리와 캐시 간의 일관성.
		@ LOC bit에 설정된 (r0) 캐시 레벨은 clean & invalidate를 할 필요가 없다.
		@ 이유 : 메모리와 캐시 간에 해당 레벨의 캐시는 데이터 일관성이 있기 때문에
		@ zero flag == 1 => finished  if(LOC == N) loop (1 ~ n-1) level cache; 
		@ reference page : 1329,
		@ CLZ : 최상위 비트에서 처음으로 1이 나온 비트사이에 0이 몇개나 있는가를 세는데 사용 

hierarchical:
		mcr	p15, 0, r10, c7, c10, 5	@ DMB
		stmfd	sp!, {r0-r7, r9-r11}	@				@ register list를 stack 에 쌓는다 sp는 descending (for back-up register list) 
		mrc	p15, 1, r0, c0, c0, 1	@ read clidr			@ r0 <- clidr 레지스터 
		ands	r3, r0, #0x7000000	@ extract loc from clidr	@ r3 <- LOC(Level of Coherency) bit of clidr
		mov	r3, r3, lsr #23		@ left align loc bit field	@ LOC bit를 align
		beq	finished		@ if loc is 0, then no need to clean	@ LOC가 0이면 finished로 branch
		@ LOC 가 0이 아니면 loop 진행
		mov	r10, #0			@ start clean at cache level 0
loop1:
		add	r2, r10, r10, lsr #1	@ work out 3x current cache level	@ r2 = r10>>1 + r10 
		mov	r1, r0, lsr r2		@ extract cache type bits from clidr	@ r1 = r0(CLIDR)>>r2
		and	r1, r1, #7		@ mask of the bits for current cache only	@r1 = r1 & 0b0111
		cmp	r1, #2			@ see what cache we have at this level		@ if(r1 < 2)
		blt	skip			@ skip if no cache, or just i-cache		@ branch to skip less than 2
		mcr	p15, 2, r10, c0, c0, 0	@ select current cache level in cssr		@ CSSR = r10 
		mcr	p15, 0, r10, c7, c5, 4	@ isb to sych the new cssr&csidr		@ ISB
		mrc	p15, 1, r1, c0, c0, 0	@ read the new csidr				@ R1 = CSIDR	
		and	r2, r1, #7		@ extract the length of the cache lines		@ r2= r1 & 0b0111(line size bit [0:2]) 
		add	r2, r2, #4		@ add 4 (line length offset)			@ r2 = r2 + 4
		ldr	r4, =0x3ff								@ r4 = 0x3ff(0b001111111111) 
		ands	r4, r4, r1, lsr #3	@ find maximum number on the way size		@ r4 = CSIDR[12:3]=r4 & r1>>3 : Associativity = n ways
		clz	r5, r4			@ find bit position of way size increment	@ r5 = r4의 최상위 비트에서 0의 갯수
		ldr	r7, =0x7fff								@ r7 = 0x7fff([14:0])
		ands	r7, r7, r1, lsr #13	@ extract max number of the index size		@ r7 = CSIDR[27:13] : number of sets in cache 
loop2:
		mov	r9, r4			@ create working copy of max way size		@ r9 = r4 = n ways	
loop3:
 ARM(		orr	r11, r10, r9, lsl r5	) @ factor way and cache number into r11	@ r11 = r10(0 index?)| (r9(n ways)<<r5) 
 ARM(		orr	r11, r11, r7, lsl r2	) @ factor index number into r11
 THUMB(		lsl	r6, r9, r5		)
 THUMB(		orr	r11, r10, r6		) @ factor way and cache number into r11
 THUMB(		lsl	r6, r7, r2		)
 THUMB(		orr	r11, r11, r6		) @ factor index number into r11
		mcr	p15, 0, r11, c7, c14, 2	@ clean & invalidate data cache line by set/way	@ refer to c7, Cache operation 
		subs	r9, r9, #1		@ decrement the way
		bge	loop3
		ubs	r7, r7, #1		@ decrement the index				@ r7 = maybe index 
		bge	loop2
skip:
		add	r10, r10, #2		@ increment cache number
		cmp	r3, r10
		bgt	loop1
finished:
		ldmfd	sp!, {r0-r7, r9-r11}
		mov	r10, #0			@ swith back to cache level 0
		mcr	p15, 2, r10, c0, c0, 0	@ select current cache level in cssr
iflush:
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		@ Data syncronizaition barrier (DSB)
		@ CP15:C7:C5:0 : flush instruction cache	
		@ i cache flush 설정전 memory barrier를 설정하여 보호한후 i cache invalidate를 한다
		@ 설정후 i cache 설정을 보장하기 위해 다시 DSB, ISB를 실행한다 
		@ cache_off call code jump (pc<-lr) 
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		mcr	p15, 0, r10, c7, c10, 4	@ DSB
		mcr	p15, 0, r10, c7, c5, 0	@ invalidate I+BTB
		mcr	p15, 0, r10, c7, c10, 4	@ DSB
		mcr	p15, 0, r10, c7, c5, 4	@ ISB
		mov	pc, lr

__armv5tej_mmu_cache_flush:
1:		mrc	p15, 0, r15, c7, c14, 3	@ test,clean,invalidate D cache
		bne	1b
		mcr	p15, 0, r0, c7, c5, 0	@ flush I cache
		mcr	p15, 0, r0, c7, c10, 4	@ drain WB
		mov	pc, lr

__armv4_mmu_cache_flush:
		mov	r2, #64*1024		@ default: 32K dcache size (*2)
		mov	r11, #32		@ default: 32 byte line size
		mrc	p15, 0, r3, c0, c0, 1	@ read cache type
		teq	r3, r9			@ cache ID register present?
		beq	no_cache_id
		mov	r1, r3, lsr #18
		and	r1, r1, #7
		mov	r2, #1024
		mov	r2, r2, lsl r1		@ base dcache size *2
		tst	r3, #1 << 14		@ test M bit
		addne	r2, r2, r2, lsr #1	@ +1/2 size if M == 1
		mov	r3, r3, lsr #12
		and	r3, r3, #3
		mov	r11, #8
		mov	r11, r11, lsl r3	@ cache line size in bytes
no_cache_id:
		mov	r1, pc
		bic	r1, r1, #63		@ align to longest cache line
		add	r2, r1, r2
1:
 ARM(		ldr	r3, [r1], r11		) @ s/w flush D cache
 THUMB(		ldr     r3, [r1]		) @ s/w flush D cache
 THUMB(		add     r1, r1, r11		)
		teq	r1, r2
		bne	1b

		mcr	p15, 0, r1, c7, c5, 0	@ flush I cache
		mcr	p15, 0, r1, c7, c6, 0	@ flush D cache
		mcr	p15, 0, r1, c7, c10, 4	@ drain WB
		mov	pc, lr

__armv3_mmu_cache_flush:
__armv3_mpu_cache_flush:
		mov	r1, #0
		mcr	p15, 0, r1, c7, c0, 0	@ invalidate whole cache v3
		mov	pc, lr

/*
 * Various debugging routines for printing hex characters and
 * memory, which again must be relocatable.
 */
#ifdef DEBUG
		.align	2
		.type	phexbuf,#object
phexbuf:	.space	12
		.size	phexbuf, . - phexbuf

@ phex corrupts {r0, r1, r2, r3}
phex:		adr	r3, phexbuf
		mov	r2, #0
		strb	r2, [r3, r1]
1:		subs	r1, r1, #1
		movmi	r0, r3
		bmi	puts
		and	r2, r0, #15
		mov	r0, r0, lsr #4
		cmp	r2, #10
		addge	r2, r2, #7
		add	r2, r2, #'0'
		strb	r2, [r3, r1]
		b	1b

@ puts corrupts {r0, r1, r2, r3}
puts:		loadsp	r3, r1
1:		ldrb	r2, [r0], #1
		teq	r2, #0
		moveq	pc, lr
2:		writeb	r2, r3
		mov	r1, #0x00020000
3:		subs	r1, r1, #1
		bne	3b
		teq	r2, #'\n'
		moveq	r2, #'\r'
		beq	2b
		teq	r0, #0
		bne	1b
		mov	pc, lr
@ putc corrupts {r0, r1, r2, r3}
putc:
		mov	r2, r0
		mov	r0, #0
		loadsp	r3, r1
		b	2b

@ memdump corrupts {r0, r1, r2, r3, r10, r11, r12, lr}
memdump:	mov	r12, r0
		mov	r10, lr
		mov	r11, #0
2:		mov	r0, r11, lsl #2
		add	r0, r0, r12
		mov	r1, #8
		bl	phex
		mov	r0, #':'
		bl	putc
1:		mov	r0, #' '
		bl	putc
		ldr	r0, [r12, r11, lsl #2]
		mov	r1, #8
		bl	phex
		and	r0, r11, #7
		teq	r0, #3
		moveq	r0, #' '
		bleq	putc
		and	r0, r11, #7
		add	r11, r11, #1
		teq	r0, #7
		bne	1b
		mov	r0, #'\n'
		bl	putc
		cmp	r11, #64
		blt	2b
		mov	pc, r10
#endif

		.ltorg
reloc_code_end:

		.align
		.section ".stack", "aw", %nobits
.L_user_stack:	.space	4096
.L_user_stack_end:
