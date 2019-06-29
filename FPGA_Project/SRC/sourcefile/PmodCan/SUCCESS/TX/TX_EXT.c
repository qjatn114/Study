#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/spi/spidev.h>

#define SPI_DEV "/dev/spidev1.0"

#define mcp25625_FAIL 	 0
#define mcp25625_SUCCESS 1

#define MCP_ALLTXBUSY	2
#define TIMEOUTVALUE	100

#define MCP_SIDH		0
#define MCP_SIDL		1
#define MCP_EID8		2
#define MCP_EID0		3

#define CAN_FAIL			0
#define CAN_OK				1
#define CAN_GETTXBFTIMEOUT	6
#define CAN_SENDMSGTIMEOUT	7

//CANCTRL register values
#define MCP_NORMAL		0x00
#define MCP_SLEEP		0x20
#define MCP_LOOPBACK	0x40
#define MCP_LISTENONLY	0x60
#define MCP_CONFIG		0x80
#define MCP_POWERUP		0xE0
#define MODE_MASK		0xE0

#define MCP_RXB_RX_ANY	0x60
#define MCP_RXB_RX_EXT	0x40
#define MCP_RXB_RX_STD	0x20
#define MCP_RXB_RX_STDEXT	0x00
#define MCP_RXB_RX_MASK	0x60
#define MCP_RXB_BUKT_MASK	(1<<2)

#define MCP_STDEXT	0
#define MCP_STD		1
#define MCP_EXT		2
#define MCP_ANY		3

//crystal
#define MCP_20MHZ	0
#define MCP_16MHZ	1
#define MCP_8MHZ	2

//bitrate
#define CAN_40KBPS	0
#define CAN_80KBPS	1
#define CAN_100KBPS	2
#define CAN_200KBPS	3
#define CAN_250KBPS 4
#define CAN_500KBPS	5

//MCP25625 register addresses
#define MCP_RXF0SIDH    0x00
#define MCP_RXF0SIDL    0x01
#define MCP_RXF0EID8    0x02
#define MCP_RXF0EID0    0x03
#define MCP_RXF1SIDH    0x04
#define MCP_RXF1SIDL    0x05
#define MCP_RXF1EID8    0x06
#define MCP_RXF1EID0    0x07
#define MCP_RXF2SIDH    0x08
#define MCP_RXF2SIDL    0x09
#define MCP_RXF2EID8    0x0A
#define MCP_RXF2EID0    0x0B
#define MCP_CANSTAT     0x0E
#define MCP_CANCTRL     0x0F
#define MCP_RXF3SIDH    0x10
#define MCP_RXF3SIDL    0x11
#define MCP_RXF3EID8    0x12
#define MCP_RXF3EID0    0x13
#define MCP_RXF4SIDH    0x14
#define MCP_RXF4SIDL    0x15
#define MCP_RXF4EID8    0x16
#define MCP_RXF4EID0    0x17
#define MCP_RXF5SIDH    0x18
#define MCP_RXF5SIDL    0x19
#define MCP_RXF5EID8    0x1A
#define MCP_RXF5EID0    0x1B
#define MCP_TEC            0x1C
#define MCP_REC            0x1D
#define MCP_RXM0SIDH    0x20
#define MCP_RXM0SIDL    0x21
#define MCP_RXM0EID8    0x22
#define MCP_RXM0EID0    0x23
#define MCP_RXM1SIDH    0x24
#define MCP_RXM1SIDL    0x25
#define MCP_RXM1EID8    0x26
#define MCP_RXM1EID0    0x27
#define MCP_CNF3        0x28
#define MCP_CNF2        0x29
#define MCP_CNF1        0x2A
#define MCP_CANINTE        0x2B
#define MCP_CANINTF        0x2C
#define MCP_EFLG        0x2D
#define MCP_TXB0CTRL    0x30
#define MCP_TXB0SIDH	0x31
#define MCP_TXB0D0	0x36
#define MCP_TXB1CTRL    0x40
#define MCP_TXB1SIDH	0x41
#define MCP_TXB1D0	0x46
#define MCP_TXB2CTRL    0x50
#define MCP_TXB2SIDH	0x51
#define MCP_TXB2D0	0x56
#define MCP_RXB0CTRL    0x60
#define MCP_RXB0SIDH    0x61
#define MCP_RXB1CTRL    0x70
#define MCP_RXB1SIDH    0x71

#define MCP_TX_INT          0x1C       
#define MCP_TX01_INT        0x0C       
#define MCP_RX_INT          0x03       
#define MCP_NO_INT          0x00       
#define MCP_TX01_MASK       0x14
#define MCP_TX_MASK        0x54

#define MCP_TXB_TXREQ_M		0x08
#define MCP_RTR_MASK		0x40
#define MCP_N_TXBUFFERS		3

//SPI instruction set
#define MCP_RESET	0xC0
#define MCP_READ	0x03
#define MCP_WRITE	0x02
#define MCP_LD_TXBUF	0x40
#define MCP_RD_STATUS	0xA0
#define MCP_RX_STATUS	0xB0
#define MCP_BITMOD	0x05

//speed 8M
#define MCP_8MHz_500kBPS_CFG1 (0x00)
#define MCP_8MHz_500kBPS_CFG2 (0x90)
#define MCP_8MHz_500kBPS_CFG3 (0x82)

#define MCP_8MHz_250kBPS_CFG1 (0x00)
#define MCP_8MHz_250kBPS_CFG2 (0xB1)
#define MCP_8MHz_250kBPS_CFG3 (0x85)

#define MCP_8MHz_200kBPS_CFG1 (0x00)
#define MCP_8MHz_200kBPS_CFG2 (0xB4)
#define MCP_8MHz_200kBPS_CFG3 (0x86)

#define MCP_8MHz_100kBPS_CFG1 (0x01)
#define MCP_8MHz_100kBPS_CFG2 (0xB4)
#define MCP_8MHz_100kBPS_CFG3 (0x86)

#define MCP_8MHz_80kBPS_CFG1 (0x01)
#define MCP_8MHz_80kBPS_CFG2 (0xBF)
#define MCP_8MHz_80kBPS_CFG3 (0x87)

#define MCP_8MHz_40kBPS_CFG1 (0x03)
#define MCP_8MHz_40kBPS_CFG2 (0xBF)
#define MCP_8MHz_40kBPS_CFG3 (0x87)

// speed 16M
#define MCP_16MHz_500kBPS_CFG1 (0x00)
#define MCP_16MHz_500kBPS_CFG2 (0xF0)
#define MCP_16MHz_500kBPS_CFG3 (0x86)

#define MCP_16MHz_250kBPS_CFG1 (0x41)
#define MCP_16MHz_250kBPS_CFG2 (0xF1)
#define MCP_16MHz_250kBPS_CFG3 (0x85)

#define MCP_16MHz_200kBPS_CFG1 (0x01)
#define MCP_16MHz_200kBPS_CFG2 (0xFA)
#define MCP_16MHz_200kBPS_CFG3 (0x87)

#define MCP_16MHz_100kBPS_CFG1 (0x03)
#define MCP_16MHz_100kBPS_CFG2 (0xFA)
#define MCP_16MHz_100kBPS_CFG3 (0x87)

#define MCP_16MHz_80kBPS_CFG1 (0x03)
#define MCP_16MHz_80kBPS_CFG2 (0xFF)
#define MCP_16MHz_80kBPS_CFG3 (0x87)

#define MCP_16MHz_40kBPS_CFG1 (0x07)
#define MCP_16MHz_40kBPS_CFG2 (0xFF)
#define MCP_16MHz_40kBPS_CFG3 (0x87)

//  speed 20M
#define MCP_20MHz_500kBPS_CFG1 (0x00)
#define MCP_20MHz_500kBPS_CFG2 (0xFA)
#define MCP_20MHz_500kBPS_CFG3 (0x87)

#define MCP_20MHz_250kBPS_CFG1 (0x41)
#define MCP_20MHz_250kBPS_CFG2 (0xFB)
#define MCP_20MHz_250kBPS_CFG3 (0x86)

#define MCP_20MHz_200kBPS_CFG1 (0x01)
#define MCP_20MHz_200kBPS_CFG2 (0xFF)
#define MCP_20MHz_200kBPS_CFG3 (0x87)

#define MCP_20MHz_100kBPS_CFG1 (0x04)
#define MCP_20MHz_100kBPS_CFG2 (0xFA)
#define MCP_20MHz_100kBPS_CFG3 (0x87)

#define MCP_20MHz_80kBPS_CFG1 (0x04)
#define MCP_20MHz_80kBPS_CFG2 (0xFF)
#define MCP_20MHz_80kBPS_CFG3 (0x87)

#define MCP_20MHz_40kBPS_CFG1 (0x09)
#define MCP_20MHz_40kBPS_CFG2 (0xFF)
#define MCP_20MHz_40kBPS_CFG3 (0x87)

typedef struct __canMsg
{
	uint16_t	canID;
	uint32_t	canEID;
	uint8_t		canIDE;
	uint8_t		canRTR;
	uint8_t		canSRR;
	uint8_t		canDLC;
	uint8_t		canDATA[8];
	

}canMsg;
//pmod CAN function 
static void dumpstat(const char *name, int fd);
static void do_msg(int fd, unsigned char *buf, int len);

bool mcp25625_init(int fd, const uint8_t canIDMode, const uint8_t canSpeed, const uint8_t canClock);
void mcp25625_reset(int fd);
bool mcp25625_setCANCTRL_Mode(int fd, uint8_t mcpMode);
bool mcp25625_configRate(int fd, const uint8_t canSpeed, const uint8_t canClock);
void mcp25625_initCANBuffers(int fd);
void mcp25625_modifyRegister(int fd, const uint8_t address, const uint8_t mask, const uint8_t data);
uint8_t mcp25625_readRegister(int fd, const uint8_t address);
void mcp25625_setRegister(int fd, const uint8_t address, const uint8_t value);
uint8_t mcp25625_getNextFreeTXBuf(int fd, uint8_t *txbuf);
void mcp25625_write_canMsg(int fd, const uint8_t buffer_sidh_addr);
void mcp25625_write_id(int fd, unsigned char *rts, const uint8_t mcp_addr);
void mcp25625_write_data(int fd, const uint8_t mcp_addr);
void mcp25625_loadTXBuffer(int fd, unsigned char * rts, unsigned char * txbuf, const uint8_t buffer_addr);
void mcp25625_setMsg(int fd, unsigned char * rts, unsigned char * txbuf, const uint8_t buffer_addr);

uint8_t sendMsgBuf(int fd, uint16_t id, uint32_t eid, uint8_t ide, uint8_t rtr, uint8_t len, uint8_t *data);
void setMsg(int fd, uint16_t id, uint32_t eid, uint8_t ide, uint8_t rtr, uint8_t len, uint8_t * data);
uint8_t sendMsg(int fd);
void wait(int delay);

canMsg myCanMsg;
int fd2 = 0;
uint8_t txbuf;

int main(void)
{
	//pmod variable
	const char * pname = SPI_DEV;
	uint16_t id = 0x2;
	uint32_t eid = 0x0;
	uint8_t ide = 1;
	uint8_t rtr = 0x0;
	uint8_t dlc = 0x8;
	uint8_t data[8] = {0,1,2,3,4,5,6,7};	
	uint8_t txreq = 0;
	uint8_t a = 0, j;
	

	//Spi Open
	if((fd2 = open(pname, O_RDWR))<0)
	{
		perror("Spi Open Success\n");
		return -1;
	}
	printf("Spi Open Success\n");
	
	//Spi stat verification
	dumpstat(pname, fd2);

	//Spi init
	if(mcp25625_init(fd2, MCP_ANY, CAN_250KBPS, MCP_20MHZ) == mcp25625_SUCCESS)
		printf("MCP25625 Initialized Successfully!\n");
	else
	{
		perror("MCP25625 Initializing Error\n");
		return -1;
	}
	
	for(;;)
	{
		if(sendMsgBuf(fd2, id, eid, ide, rtr, dlc, data) != CAN_OK)
			printf("Send Message Fail\n");
		else
			printf("Send Message Success\n");

		mcp25625_modifyRegister(fd2, txbuf, 0x08, 0);

		
	}

	close(fd2);

    return 0;
}

void wait(int delay)
{
	int i;

	for(i=0; i<delay; i++)
		;
}

//pmod CAN function 
bool mcp25625_init(int fd, const uint8_t canIDMode, const uint8_t canSpeed, const uint8_t canClock)
{
	uint8_t mcpMode, res;

	mcp25625_reset(fd);

	if(mcp25625_setCANCTRL_Mode(fd, MCP_CONFIG) == mcp25625_SUCCESS)
		printf("Entering Configuration Mode..\n");
	else
	{
		printf("Fail to Entering Configuration Mode..\n");
		return mcp25625_FAIL;
	}

	if(mcp25625_configRate(fd, canSpeed, canClock) == mcp25625_SUCCESS)
		printf("Bitrate Setting Success!!\n");
	else
	{
		printf("Fail to Setting Bitrate..\n");
		return mcp25625_FAIL;
	}

	mcp25625_initCANBuffers(fd);

	mcp25625_modifyRegister(fd, MCP_RXB0CTRL, MCP_RXB_RX_MASK, MCP_RXB_RX_ANY);
	mcp25625_modifyRegister(fd, MCP_RXB1CTRL, MCP_RXB_RX_MASK, MCP_RXB_RX_ANY);

	if(mcp25625_setCANCTRL_Mode(fd, MCP_NORMAL) == mcp25625_SUCCESS)
		printf("Entering to Normal Mode...!\n");
	else
	{
		printf("Fail to Entering Normal Mode..\n");
		return mcp25625_FAIL;
	}	
	
	return mcp25625_SUCCESS;	
}

void mcp25625_reset(int fd)
{
	unsigned char buf = MCP_RESET;

	do_msg(fd, &buf, 1);
}

bool mcp25625_setCANCTRL_Mode(int fd, uint8_t mcpMode)
{
	uint8_t n;

	mcp25625_modifyRegister(fd, MCP_CANCTRL, MODE_MASK, mcpMode);

	n = mcp25625_readRegister(fd, MCP_CANCTRL);
	n &= MODE_MASK;

	if(n == mcpMode)
		return mcp25625_SUCCESS;

	return mcp25625_FAIL;
}

bool mcp25625_configRate(int fd, const uint8_t canSpeed, const uint8_t canClock)
{
	uint8_t set, cfg1, cfg2, cfg3;
    set = 1;
    switch (canClock)
    {
        case (MCP_8MHZ):
        switch (canSpeed) 
        {
            case (CAN_40KBPS):                                              //  40Kbps
            cfg1 = MCP_8MHz_40kBPS_CFG1;
            cfg2 = MCP_8MHz_40kBPS_CFG2;
            cfg3 = MCP_8MHz_40kBPS_CFG3;
            break;

            case (CAN_80KBPS):                                              //  80Kbps
            cfg1 = MCP_8MHz_80kBPS_CFG1;
            cfg2 = MCP_8MHz_80kBPS_CFG2;
            cfg3 = MCP_8MHz_80kBPS_CFG3;
            break;

            case (CAN_100KBPS):                                             // 100Kbps
            cfg1 = MCP_8MHz_100kBPS_CFG1;
            cfg2 = MCP_8MHz_100kBPS_CFG2;
            cfg3 = MCP_8MHz_100kBPS_CFG3;
            break;

            case (CAN_200KBPS):                                             // 200Kbps
            cfg1 = MCP_8MHz_200kBPS_CFG1;
            cfg2 = MCP_8MHz_200kBPS_CFG2;
            cfg3 = MCP_8MHz_200kBPS_CFG3;
            break;

            case (CAN_250KBPS):                                             // 250Kbps
            cfg1 = MCP_8MHz_250kBPS_CFG1;
            cfg2 = MCP_8MHz_250kBPS_CFG2;
            cfg3 = MCP_8MHz_250kBPS_CFG3;
            break;

            case (CAN_500KBPS):                                             // 500Kbps
            cfg1 = MCP_8MHz_500kBPS_CFG1;
            cfg2 = MCP_8MHz_500kBPS_CFG2;
            cfg3 = MCP_8MHz_500kBPS_CFG3;
            break;
        
            default:
            set = 0;
	    return mcp25625_FAIL;
            break;
        }
        break;

        case (MCP_16MHZ):
        switch (canSpeed) 
        {

            case (CAN_40KBPS):                                              //  40Kbps
            cfg1 = MCP_16MHz_40kBPS_CFG1;
            cfg2 = MCP_16MHz_40kBPS_CFG2;
            cfg3 = MCP_16MHz_40kBPS_CFG3;
            break;

            case (CAN_80KBPS):                                              //  80Kbps
            cfg1 = MCP_16MHz_80kBPS_CFG1;
            cfg2 = MCP_16MHz_80kBPS_CFG2;
            cfg3 = MCP_16MHz_80kBPS_CFG3;
            break;

            case (CAN_100KBPS):                                             // 100Kbps
            cfg1 = MCP_16MHz_100kBPS_CFG1;
            cfg2 = MCP_16MHz_100kBPS_CFG2;
            cfg3 = MCP_16MHz_100kBPS_CFG3;
            break;

            case (CAN_200KBPS):                                             // 200Kbps
            cfg1 = MCP_16MHz_200kBPS_CFG1;
            cfg2 = MCP_16MHz_200kBPS_CFG2;
            cfg3 = MCP_16MHz_200kBPS_CFG3;
            break;

            case (CAN_250KBPS):                                             // 250Kbps
            cfg1 = MCP_16MHz_250kBPS_CFG1;
            cfg2 = MCP_16MHz_250kBPS_CFG2;
            cfg3 = MCP_16MHz_250kBPS_CFG3;
            break;

            case (CAN_500KBPS):                                             // 500Kbps
            cfg1 = MCP_16MHz_500kBPS_CFG1;
            cfg2 = MCP_16MHz_500kBPS_CFG2;
            cfg3 = MCP_16MHz_500kBPS_CFG3;
            break;

            default:
            set = 0;
	    return mcp25625_FAIL;
            break;
        }
        break;
        
        case (MCP_20MHZ):
        switch (canSpeed) 
        {
            case (CAN_40KBPS):                                              //  40Kbps
            cfg1 = MCP_20MHz_40kBPS_CFG1;
            cfg2 = MCP_20MHz_40kBPS_CFG2;
            cfg3 = MCP_20MHz_40kBPS_CFG3;
            break;

            case (CAN_80KBPS):                                              //  80Kbps
            cfg1 = MCP_20MHz_80kBPS_CFG1;
            cfg2 = MCP_20MHz_80kBPS_CFG2;
            cfg3 = MCP_20MHz_80kBPS_CFG3;
            break;

            case (CAN_100KBPS):                                             // 100Kbps
            cfg1 = MCP_20MHz_100kBPS_CFG1;
            cfg2 = MCP_20MHz_100kBPS_CFG2;
            cfg3 = MCP_20MHz_100kBPS_CFG3;
            break;

            case (CAN_200KBPS):                                             // 200Kbps
            cfg1 = MCP_20MHz_200kBPS_CFG1;
            cfg2 = MCP_20MHz_200kBPS_CFG2;
            cfg3 = MCP_20MHz_200kBPS_CFG3;
            break;

            case (CAN_250KBPS):                                             // 250Kbps
            cfg1 = MCP_20MHz_250kBPS_CFG1;
            cfg2 = MCP_20MHz_250kBPS_CFG2;
            cfg3 = MCP_20MHz_250kBPS_CFG3;
            break;

            case (CAN_500KBPS):                                             // 500Kbps
            cfg1 = MCP_20MHz_500kBPS_CFG1;
            cfg2 = MCP_20MHz_500kBPS_CFG2;
            cfg3 = MCP_20MHz_500kBPS_CFG3;
            break;

            default:
            set = 0;
            return mcp25625_FAIL;
            break;
        }
        break;
        
        default:
        set = 0;
		return mcp25625_FAIL;
        break;
    }

    if (set) {

        mcp25625_setRegister(fd, MCP_CNF3, cfg3);
	wait(100);

        mcp25625_setRegister(fd, MCP_CNF2, cfg2);
	wait(100);

        mcp25625_setRegister(fd, MCP_CNF1, cfg1);
	wait(100);
        return mcp25625_SUCCESS;
    }
     
    return mcp25625_FAIL;
}

void mcp25625_initCANBuffers(int fd)
{
	uint8_t i;
	unsigned char a1, a2, a3;

	a1 = MCP_RXF0SIDH;
	a2 = MCP_RXF3SIDH;

	for(i=0; i<9; i++)
	{
		mcp25625_setRegister(fd, a1, 0);
		mcp25625_setRegister(fd, a2, 0);
		a1++;
		a2++;
	}
/*
	mcp25625_modifyRegister(fd, MCP_RXF0SIDL, 0x08, 0x08);
	mcp25625_modifyRegister(fd, MCP_RXF1SIDL, 0x08, 0x08);
	mcp25625_modifyRegister(fd, MCP_RXF2SIDL, 0x08, 0x08);
	mcp25625_modifyRegister(fd, MCP_RXF3SIDL, 0x08, 0x08);
	mcp25625_modifyRegister(fd, MCP_RXF4SIDL, 0x08, 0x08);
*/
	a1 = MCP_RXM0SIDH;

	for(i=0; i<5; i++)
	{
		mcp25625_setRegister(fd, a1, 0);
		a1++;
	}

	a1 = MCP_TXB0CTRL;
	a2 = MCP_TXB1CTRL;
	a3 = MCP_TXB2CTRL;

	for(i=0; i<11; i++)
	{
		mcp25625_setRegister(fd, a1, 0);
		mcp25625_setRegister(fd, a2, 0);
		mcp25625_setRegister(fd, a3, 0);
		a1++;
		a2++;
		a3++;
	}

	mcp25625_setRegister(fd, MCP_RXB0CTRL, 0);
	mcp25625_setRegister(fd, MCP_RXB1CTRL, 0);
}

void mcp25625_modifyRegister(int fd, const uint8_t address, const uint8_t mask, const uint8_t data)
{
	unsigned char buf[4];
	memset(buf, 0, sizeof(buf));
	
	buf[0] = MCP_BITMOD;
	buf[1] = address;
	buf[2] = mask;
	buf[3] = data;

	do_msg(fd, buf, sizeof(buf));

}

uint8_t mcp25625_readRegister(int fd, const uint8_t address)
{
	unsigned char buf[2];
	memset(buf, 0, sizeof(buf));

	buf[0] = MCP_READ;
	buf[1] = address;

	do_msg(fd, buf, sizeof(buf));

	return buf[0];	
}

void mcp25625_setRegister(int fd, const uint8_t address, const uint8_t value)
{
	unsigned char buf[3];
	memset(buf, 0, sizeof(buf));

	buf[0] = MCP_WRITE;
	buf[1] = address;
	buf[2] = value;

	do_msg(fd, buf, sizeof(buf));
	
}

uint8_t mcp25625_getNextFreeTXBuf(int fd, uint8_t *txbuf)
{
	
	uint8_t res, i, ctrlval;
	uint8_t ctrlregs[MCP_N_TXBUFFERS] = {MCP_TXB0CTRL, MCP_TXB1CTRL, MCP_TXB2CTRL};

	res = MCP_ALLTXBUSY;
	*txbuf = 0x00;

	for(i=0; i<MCP_N_TXBUFFERS; i++)
	{
		ctrlval = mcp25625_readRegister(fd, ctrlregs[i]);
		if((ctrlval & MCP_TXB_TXREQ_M)==0)
		{
			*txbuf = ctrlregs[i] + 1;
			res = mcp25625_SUCCESS;
			return res;
		} 
	}
	return res;
}

void mcp25625_write_data(int fd, const uint8_t mcp_addr)
{
//	printf("write_data\n");

	int i;
	uint8_t a1 = mcp_addr;
	unsigned char buf[3];
	memset(buf, 0, sizeof(buf));

	buf[0] = MCP_WRITE;
	for(i=0; i<myCanMsg.canDLC; i++)
	{
		buf[1] = a1++;
		buf[2] = (unsigned char)myCanMsg.canDATA[i];
		
		do_msg(fd, buf, sizeof(buf));
	}
}

uint8_t sendMsgBuf(int fd, uint16_t id, uint32_t eid, uint8_t ide, uint8_t rtr, uint8_t len, uint8_t * data)
{
//	printf("sendMsgBuf\n");
	uint8_t res;

	setMsg(fd, id, eid, ide, rtr, len, data);

	res = sendMsg(fd);

	return res;
}

void setMsg(int fd, uint16_t id, uint32_t eid, uint8_t ide, uint8_t rtr, uint8_t len, uint8_t * data)
{
//	printf("setMsg\n");

	int i;
	myCanMsg.canID = id;
	myCanMsg.canEID = eid;
	myCanMsg.canIDE = ide;
	myCanMsg.canRTR = rtr;
	myCanMsg.canDLC = len;
	
	for(i=0; i<len; i++)
		myCanMsg.canDATA[i] = data[i];

	printf("canID = %02x\n", myCanMsg.canID);
	printf("canEID = %02x\n", myCanMsg.canEID);
	printf("canIDE = %02x\n", myCanMsg.canIDE);
	printf("canRTR = %02x\n", myCanMsg.canRTR);
	printf("canDLC = %02x\n", myCanMsg.canDLC);

	for(i=0; i<len; i++)
		printf("canDATA[%d] = %02x\n", i, myCanMsg.canDATA[i]);
}

uint8_t sendMsg(int fd)
{
//	printf("sendMsg\n");
	
	uint8_t res, res1;
	uint16_t uTimeOut = 0;

	do{
		res = mcp25625_getNextFreeTXBuf(fd, &txbuf);
		uTimeOut++;
	}
	while(res == MCP_ALLTXBUSY && (uTimeOut < TIMEOUTVALUE));
	printf("selected txbuf = %02x\n", txbuf);

	if(uTimeOut == TIMEOUTVALUE)
		return CAN_GETTXBFTIMEOUT;

	uTimeOut = 0;
	mcp25625_write_canMsg(fd, txbuf);

	mcp25625_modifyRegister(fd, txbuf -1, MCP_TXB_TXREQ_M, 0);

	do{
		uTimeOut++;
		res1 = mcp25625_readRegister(fd, txbuf -1);
		res1 = res1 & 0x08;
	}
	while(res1 && (uTimeOut < TIMEOUTVALUE));

	if(uTimeOut == TIMEOUTVALUE)
		return CAN_SENDMSGTIMEOUT;

	return CAN_OK;
	
}

void mcp25625_write_canMsg(int fd, const uint8_t buffer_sidh_addr)
{
//	printf("write_canMsg\n");
	uint8_t i, n;
	uint8_t mcp_addr = buffer_sidh_addr;
	uint8_t txDLC = myCanMsg.canDLC;
	unsigned char rts = 0x80;	
	unsigned char txbuf[14];
	memset(txbuf, 0, sizeof(txbuf));	

	mcp25625_setMsg(fd, &rts, txbuf, mcp_addr);

	//request to send
	do_msg(fd, &rts, 1);

}

void mcp25625_setMsg(int fd, unsigned char *rts, unsigned char * txbuf, const uint8_t mcp_addr)
{

	int i;
	uint8_t a1;
	unsigned char buf[4];
	uint8_t txDLC = myCanMsg.canDLC;

	memset(buf, 0, sizeof(buf));
	
/* Extended ID */
	buf[MCP_SIDH] = (uint8_t)(myCanMsg.canID >> 3);
	buf[MCP_SIDL] = (uint8_t)((myCanMsg.canID & 0x07) <<5);
	buf[MCP_SIDL] |= (uint8_t)(0x08);
	buf[MCP_EID8] = 0;
	buf[MCP_EID0] = 0;

	txbuf[0] = MCP_LD_TXBUF;
	txbuf[1] = buf[MCP_SIDH];
	txbuf[2] = buf[MCP_SIDL];
	txbuf[3] = buf[MCP_EID8];
	txbuf[4] = buf[MCP_EID0];
	
	if(myCanMsg.canRTR == 1)
		txDLC |= MCP_RTR_MASK;

	txbuf[5] = txDLC;
	
	for(i=0; i<myCanMsg.canDLC; i++)
		txbuf[i+6] = myCanMsg.canDATA[i];

	mcp25625_loadTXBuffer(fd, rts, txbuf, mcp_addr);
}

void mcp25625_loadTXBuffer(int fd, unsigned char *rts, unsigned char * txbuf, const uint8_t buffer_addr)
{
	uint8_t n, i;
	unsigned char aPoint;

	switch(buffer_addr)
	{
		case MCP_TXB0SIDH:
		aPoint = 0x0;
		*rts |= 0x01;
		break;

		case MCP_TXB0D0:
		aPoint = 0x1;
		*rts |= 0x01;
		break;

		case MCP_TXB1SIDH:
		aPoint = 0x2;
		*rts |= 0x02;
		break;

		case MCP_TXB1D0:
		aPoint = 0x3;
		*rts |= 0x02;
		break;

		case MCP_TXB2SIDH:
		aPoint = 0x4;
		*rts |= 0x04;
		break;

		case MCP_TXB2D0:
		aPoint = 0x5;
		*rts |= 0x04;
		break;
	}

	txbuf[0] |= aPoint;
	do_msg(fd, txbuf, myCanMsg.canDLC + 6);
}

static void dumpstat(const char *name, int fd)
{
	__u8	lsb, bits;
	__u32	mode, speed;

	if (ioctl(fd, SPI_IOC_RD_MODE32, &mode) < 0) {
		perror("SPI rd_mode");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0) {
		perror("SPI rd_lsb_fist");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0) {
		perror("SPI bits_per_word");
		return;
	}
	if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
		perror("SPI max_speed_hz");
		return;
	}
	
	printf("%s: spi read mode 0x%x, %d bits %sper word, %d Hz max\n",
		name, mode, bits, lsb ? "(lsb first) " : "", speed);

}

static void do_msg(int fd, unsigned char * buf, int len)
{
	struct spi_ioc_transfer	xfer[2];
	unsigned char			*bp;
	int						status;

	memset(xfer, 0, sizeof xfer);

	xfer[0].tx_buf = (unsigned long)buf;
	xfer[0].len = len;

	xfer[1].rx_buf = (unsigned long) buf;
	xfer[1].len = len;

	status = ioctl(fd, SPI_IOC_MESSAGE(2), xfer);
	if (status < 0) {

		printf("status : %d\n", status);
		perror("SPI_IOC_MESSAGE");
		return;
	}

}

static void do_read(int fd, int len)
{
	unsigned char	buf[32], *bp;
	int		status;

	/* read at least 2 bytes, no more than 32 */
	if (len < 2)
		len = 2;
	else if (len > sizeof(buf))
		len = sizeof(buf);

	memset(buf, 0, sizeof buf);

	status = read(fd, buf, len);

	if (status < 0) {
		perror("read");
		return;
	}

	if (status != len) {
		fprintf(stderr, "short read\n");
		return;
	}

	printf("read(%2d, %2d): %02x %02x,", len, status, buf[0], buf[1]);

	status -= 2;
	bp = buf + 2;

	while (status-- > 0)
		printf(" %02x", *bp++);
	printf("\n");
}
