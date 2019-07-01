#include <asm/sysreg.h>
#include <asm/thread_ingo.h>
#include <asm/virt.h>

#include "efi-header.S"

#define __PHYS_OFFSET	(KERNEL_START - TEXT_OFFSET)

#if (TEXT_OFFSET & 0xFFF) != 0
#error TEXT_OFFSET must be at least 4KB aligned
#elif (PAGE_OFFSET & 0x1FFFFF) != 0
#error PAGE_OFFSET must be at least 2MB aligned
#elif TEXT_OFFSET > 0x1FFFFF
#error TEXT_OFFSET must be less than 2MB
#endif

/*
	MMU = off, D-cache = off, I-cache = on or off,
	x0 = physical address to the FDT blob.
	
	이 코드는 대부분 독립적인 위치이므로
	당신은 __pa(PAGE_OFFSET + TEXT_OFFSET)에서 호출해야 한다.
	PA:물리메모리 VA:가상메모리
	ARM 32bit에서는 __pa가 압축 해제된 커널의 위치라 한다.
	ARM 64bit도 여기? (참고로 64bit는 부트로더에서 압축해제)
	arch/arm64/Makefile에서 TEXT_OFFSET := 0x00080000
	TEXT_OFFSET := &(shell awk "BEGIN {srand(); printf \"0x%06xn\",
	\ int(2 * 1024 * 1024 / (2 ^ $(CONFIG_ARM64_PAGE_SHIFT))* \
	rand()) * (2 ^ $(CONFIG_ARM64_PAGE_SHIFT))}")

	CONFIG_ARM64_PAGE_SHIFT = 12
	
	결국 TEXT_OFFSET = 2MB??


	32bit 기준
	PAGE_OFFSET(VA)은 첫 번째 RAM뱅크의 시작주소. 커널 이미지의 시작주소
	arch/arm64/Kconfig에서 가상메모리 split(user/kernel 영역) 크기에 의해
	결정된다. 

	TEXT_OFFSET은 커널 영역의 시작에서 실행코드까지 offset 크기.
	ARM 32bit에서는 하위18bit를 clear시킨다.

	Kconfig: make manuconfig, make xconfig 같은 명령으로 커널옵션을 설정 할	때 사용되는 소스파일이다. 
	arch/arm64/Kconfig이나 arm~에 해당 architecture와 machine에 따른 설정 내용이 있다.

	makefile: make 명령에 의해 빌드에 필요한 의존 파일과 수행할 명령을 담고 있다. 
	각 디렉토리마다 하나씩 들어 있어 해당 디렉토리의 파일을 빌드하는 방법을 명시하는 구조이다. 
	
	vmlinux.lds:링커에게 재배치 정보 등을 알려주기 위한 ld script파일이다.
	 주로 Makefile에 의해 vmlinux.lds.S나 vmlinux.lds.in으로 부터 생성되므로 컴파일 후 확인해보거나 입력 파일을 직접 확인하면 된다.

	최상위 Makefile부터 따라 들어가면 어떤 파일부터 시작해야 할지 찾을 수 있다. 
	
	PAGE_OFFSET :linear map시작의 가상 주소
	KIMAGE_VADDR : 커널 이미지 시작의 가상주소
	VA_BITS : 가상주소의 최대 비트 수
	VA_START : 첫 번째 커널 가상주소

#define VA_BITS			CONFIG_ARM64_VA_BITS(48)
#define VA_START		UL(0xFFFF FFFF FFFF FFFF) - (UL(1) << VA_BITS) +1
#define PAGE_OFFSET		UL(0xFFFF FFFF FFFF FFFF) - (UL(1) << (VA_BITS-1)) +1
#define KIMAGE_VADDR	MODULE_END
#define MODULE_END		MODULE_VADDR + MODULE_VSIZE
#define MODULE_VADDR	BPF_JIT_REGION_START + BPF_JIT_REGION_SIZE
#define MODULE_START	PAGE_OFFSEt - VMEMMAP_SIZE

#define	KERNEL_START	_text(static unsigned long long)
#define KERNEL_END		_end

	ARM 32bit에서 PAGE_OFFSET은 전형적으로 0xC0000000 즉 3GB이다.
	이것은 커널 물리메모리를 보는 offset이다. 즉 커널의 관점
	PAGE_OFFSET은 물리주소 0부터 매핑한다. 쭉 이어지는 물리 페이지들을
	차례로 PAGE_OFFSET에서부터 위로 매핑한다.
	ARM 64bit에서는 PAGE_OFFSET이 0xFFFFFF80 00000000인듯?

	ARM 32bit에서#define KERNEL_RAM_VADDR (PAGE_OFFSET + TEXT_OFFSET)이다
	즉 커널의 가상 주소 시작은 0xC000 8000이다.

	ARM 64bit에서는 __pa가 32bit의 KERNEL_RAM_VADDR과 같다?
	ARM 64bit에서 커널의 가상 주소 시작은 0xFFFF FF80 0008 0000 ??
	그럼 물리주소는 512KB만 쓰는건가?

<32bit>
	.globl	swapper_pg_dir
	.equ	swapper_pg_dir, KERNEL_RAM_VADDR-0x4000
	
<64bit>

	.equ	swapper_pg_dir, TEXTADDR - 0x4000

	swapper_pg_dir은 페이지 테이블의 시작 가상주소를 가진다.
	즉, 0xC000 4000이다.

The swapper_pg_dir contains only kernel (global) mappings while the user pgd contains only user (non-global) mappings.

The swapper_pg_dir address is written to TTBR1 and never written to TTBR0.



32bit에서 _end는 bss영역을 포함하는 zImage의 마지막 위치이다.
라벨의 위치를 빼고 페이지 테이블 크기 16KB를 더하고, 최대 DTB(device tree block) 크기인 1MB를 더한 값이다.
_end - restart + 16384 + 1024*1024 이 계산값은 압축된 커널 zImage크기이다.
zImage크기 - restart라벨위치 + PTE크기 + DTB최대크기

이 값을 r0에 저장하고 r0에 현재 pc값을 더해서 decompressed 커널의 시작 위치 주소인 r4와 비교한다.
이러한 비교과정을 거치는 것은 cache를 활성화 하는 것은 PTE테이블을 만든 것이고 PTE테이블이 현재 실행 중인 head.o를 포함한 zImage와 겹쳐서 코드가 깨지면 안되니 아싸리 PTE보다 위에 위치하던가 아니면 한참 더 밑에 위치해서 둘이 겹치지 않도록 한 후에 cache를 활성화 하기 위함이다.

그래서 압축된 커널 이미지의 끝부분에 해당하는 r0가 압축 풀린 커널이 위치할 r4보다 작으면 cache를 활성화. 아니면 1을 OR하여 cache가 아직 활성화 되지 않았다는 것을 표기해두고 캐시활성화 부분을 skip한다.

이러한 행위는 decompressed 커널 위치보다 PTE위치가 아래에 있다는 약속이기 떄문이다.
만약 현재 코드가 실행되는 zImage의 위치가 decompressed 커널의 위치보다 위에 존대하면 페이지테이블 값들과 겹칠일 없으니 cache를 활성화시키고 
그보다 아래에 존재하면 zImage + DTB + PTE가 가질 수 있는 최대 사이즈를 계산하여 이 사이즈보다 훨씬 더 밑에 있으면 그 때도 PTE와 충돌나지 않으니 cache를 활성화한다.
PTE영역과 충돌할 가능이 있으면 아직 cache를 활성화하지 않았다는 bit를 표시한 후 cache를 비활성화한 상태로 다음 단계로 skip한다.


*/
