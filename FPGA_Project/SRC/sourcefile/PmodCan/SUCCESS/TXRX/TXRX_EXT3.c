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


//pmod CAN definition
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
#define CAN_ERROR			2

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

#define MCP_RXBUF_0		MCP_RXB0SIDH
#define MCP_RXBUF_1		MCP_RXB1SIDH

#define MCP_TX_INT          0x1C       
#define MCP_TX01_INT        0x0C       
#define MCP_RX_INT          0x03       
#define MCP_NO_INT          0x00       
#define MCP_TX01_MASK       0x14
#define MCP_TX_MASK        0x54

#define MCP_TXB_TXREQ_M		0x08
#define MCP_RTR_MASK		0x40
#define MCP_RX_RTR			0x08
#define MCP_N_TXBUFFERS		3

#define MCP_STAT_RXIF_MASK	(0x03)
#define MCP_STAT_RX0IF		(1<<0)
#define MCP_STAT_RX1IF		(1<<1)
#define MCP_RXB_EXIDE_M		0x08

//SPI instruction set
#define MCP_RESET	0xC0
#define MCP_READ	0x03
#define MCP_WRITE	0x02
#define MCP_LD_TXBUF	0x40
#define MCP_READ_RX_BUFFER	0x90
#define MCP_READ_STATUS	0xA0
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
uint8_t mcp25625_getNextFreeTXBuf(int fd, uint8_t *tx_sidh);
void mcp25625_write_canMsg(int fd, const uint8_t buffer_sidh_addr);
void mcp25625_write_id(int fd, unsigned char *rts, const uint8_t mcp_addr);
void mcp25625_write_data(int fd, const uint8_t mcp_addr);
void mcp25625_loadTXBuffer(int fd, unsigned char * rts, unsigned char * txbuf, const uint8_t buffer_addr);
void mcp25625_setMsg(int fd, unsigned char * rts, unsigned char * txbuf, const uint8_t buffer_addr);

uint8_t sendMsgBuf(int fd, uint16_t id, uint32_t eid, uint8_t ide, uint8_t rtr, uint8_t len, uint8_t *data);
void setMsg(int fd, uint16_t id, uint32_t eid, uint8_t ide, uint8_t rtr, uint8_t len, uint8_t * data);
uint8_t sendMsg(int fd);


uint8_t readMsgBuf(int fd, uint16_t *id, uint8_t *len, unsigned char *rxBuf, uint8_t RXxIF);
uint8_t readMsg(int fd, uint8_t RXxIF);
uint8_t mcp25625_readStatus(int fd);
void mcp25625_read_canMsg(int fd, const uint8_t buffer_sidh_addr, uint8_t nm);
void mcp25625_read_buf(int fd, const uint8_t mcp_addr, uint8_t *ext, uint16_t *id, uint8_t nm);

void mcp25625_ReadRXBuffer(int fd, unsigned char * rxbuf, const uint8_t buffer_addr, uint8_t nm);

void wait(int delay);

canMsg myCanMsg;
int fd_spi;
uint8_t tx_sidh;


typedef struct _SPI_RX{
	uint16_t id;
	uint32_t eid;
	uint8_t  ide;
	uint8_t  dlc;
	uint8_t  Buf[8];
	uint8_t ReceiveStatus;
}SPI_RX;

typedef struct _SPI_TX{
	uint16_t id;
	uint32_t eid;
	uint8_t ide;
	uint8_t rtr;
	uint8_t dlc;
	uint8_t Buf[8];
	uint8_t txreq;
}SPI_TX;

int main(void)
{
	SPI_RX RX;
	SPI_TX TX = {0x2, 0x0, 1, 0x0, 0x8, {1,2,3,4,5,6,7,8},0};

	uint8_t Err = 0;

	//pmod variable
	const char * pname = SPI_DEV;
	int cnt=0;

	//Spi Open
	if((fd_spi = open(pname, O_RDWR))<0)
	{
		perror("Spi Open Success\n");
		return -1;
	}
	printf("Spi Open Success\n");
	
	//Spi stat verification
	dumpstat(pname, fd_spi);

	//Spi init
	if(mcp25625_init(fd_spi, MCP_ANY, CAN_250KBPS, MCP_20MHZ) == mcp25625_SUCCESS)
		printf("MCP25625 Initialized Successfully!\n");
	else
	{
		perror("MCP25625 Initializing Error\n");
		return -1;
	}
	
	for(;;)
	{
		RX.ReceiveStatus = mcp25625_readStatus(fd_spi);	
		RX.ReceiveStatus &= MCP_STAT_RXIF_MASK;


		if((RX.ReceiveStatus & MCP_STAT_RX0IF) == MCP_STAT_RX0IF)
		{
			printf("Receive SUCCESS RX0IF= %d\n",RX.ReceiveStatus);
			readMsgBuf(fd_spi, &RX.id, &RX.dlc, RX.Buf, MCP_STAT_RX0IF);
	
			if( (myCanMsg.canIDE & 0x80000000) == 0x80000000 )
			{
				printf("Extended ID : 0x%x  DLC : %1d Data\n ",RX.id, RX.dlc);
			}
			else
			{
				printf("Standard ID : 0x%x DLC : %1d Data\n", RX.id, RX.dlc);
			}
		}
		else if( (RX.ReceiveStatus & MCP_STAT_RX1IF) == MCP_STAT_RX1IF)
		{
			printf("Receive SUCCESS RX1IF=%d\n",RX.ReceiveStatus);
			readMsgBuf(fd_spi, &RX.id, &RX.dlc, RX.Buf, MCP_STAT_RX1IF);

			if( (myCanMsg.canIDE & 0x80000000) == 0x80000000)
			{
				printf("Extended ID : 0x%x DLC : %1d\n",RX.id, RX.dlc);
			}
			else
			{
				printf("Standard ID : 0x%x DLC : %1d\n",RX.id, RX.dlc);
			}
		}

		cnt++;
		if (cnt==30)
		{
			Err = mcp25625_readStatus(fd_spi);
			Err &= MCP_STAT_RXIF_MASK;
			if(Err == 0)
			{
				sendMsgBuf(fd_spi, TX.id, TX.eid, TX.ide, TX.rtr, TX.dlc, TX.Buf);
				mcp25625_modifyRegister(fd_spi, tx_sidh, 0x08,0);
			}
			else
			{
			}
//			sendMsgBuf(fd_spi, TX.id, TX.eid, TX.ide, TX.rtr, TX.dlc, TX.Buf);
//			mcp25625_modifyRegister(fd_spi, tx_sidh, 0x08,0);
			cnt =0;
		}

	}

	close(fd_spi);

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

	/* RX Interrupt Enable */
	//

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

uint8_t mcp25625_getNextFreeTXBuf(int fd, uint8_t *tx_sidh)
{
	
	uint8_t res, i, ctrlval;
	uint8_t ctrlregs[MCP_N_TXBUFFERS] = {MCP_TXB0CTRL, MCP_TXB1CTRL, MCP_TXB2CTRL};

	res = MCP_ALLTXBUSY;
	*tx_sidh = 0x00;

	for(i=0;i<MCP_N_TXBUFFERS;i++)
	{
		ctrlval = mcp25625_readRegister(fd, ctrlregs[i]);
		if((ctrlval & MCP_TXB_TXREQ_M)==0)
		{
			*tx_sidh = ctrlregs[i] + 1;
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
	uint8_t res, res1;
	uint16_t uTimeOut = 0;

	do{
		res = mcp25625_getNextFreeTXBuf(fd, &tx_sidh);
		uTimeOut++;
	}
	while(res == MCP_ALLTXBUSY && (uTimeOut < TIMEOUTVALUE));
	printf("selected txbuf = %02x\n", tx_sidh);

	if(uTimeOut == TIMEOUTVALUE)
		return CAN_GETTXBFTIMEOUT;

	uTimeOut = 0;
	mcp25625_write_canMsg(fd, tx_sidh);

	mcp25625_modifyRegister(fd, tx_sidh -1, MCP_TXB_TXREQ_M, MCP_TXB_TXREQ_M);

	do{
		uTimeOut++;
		res1 = mcp25625_readRegister(fd, tx_sidh -1);
		res1 = res1 & 0x08;
	}
	while(res1 && (uTimeOut < TIMEOUTVALUE));

	if(uTimeOut == TIMEOUTVALUE)
		return CAN_SENDMSGTIMEOUT;

	return CAN_OK;
	
}

void mcp25625_write_canMsg(int fd, const uint8_t buffer_sidh_addr)
{
	uint8_t mcp_addr = buffer_sidh_addr;
	uint8_t txDLC = myCanMsg.canDLC;
	unsigned char rts = 0x80;	
	unsigned char txbuf[14];
	memset(txbuf, 0, sizeof(txbuf));	

	mcp25625_setMsg(fd, &rts, txbuf, mcp_addr);

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

/* Receive Msg */
uint8_t readMsgBuf(int fd, uint16_t *id, uint8_t *len, unsigned char *rxBuf, uint8_t RXxIF)
{
	uint8_t i;

	printf("readMsgBuf FUNC\n");

	if(readMsg(fd, RXxIF) == CAN_OK)
	{
		*id = myCanMsg.canID;
		*len = myCanMsg.canDLC;

		if(myCanMsg.canIDE)
		{
			myCanMsg.canEID = 0x80000000;
		}


		for(i=0;i<myCanMsg.canDLC;i++)
			rxBuf[i] = myCanMsg.canDATA[i];
		
		printf("Receive Success\n");

		return CAN_OK;
	}
	else
	{
		printf("Receive Fail\n");
		return CAN_FAIL;
	}
	
	printf("Receive Error\n");
	return CAN_ERROR;
}

uint8_t readMsg(int fd, uint8_t RXxIF)
{
	uint8_t  res;
	uint8_t nm;
	unsigned char stat;

	printf("readMsg FUNC\n");

	stat = RXxIF;	

	if( stat & MCP_STAT_RX0IF)
	{
		nm = 0;
		mcp25625_read_canMsg(fd, MCP_RXB0SIDH, nm);
		mcp25625_modifyRegister(fd, MCP_CANINTF, MCP_STAT_RX0IF, 0);
		res = CAN_OK;
	}	
	else if(stat & MCP_STAT_RX1IF)
	{
		nm = 1;
		mcp25625_read_canMsg(fd, MCP_RXB1SIDH, nm);
		mcp25625_modifyRegister(fd, MCP_CANINTF, MCP_STAT_RX1IF, 0);
		res = CAN_OK;
	}
	else
	{
		res = CAN_FAIL;
	}
	
	return res;
}

uint8_t mcp25625_readStatus(int fd)
{
	unsigned char buf[2];

	memset(buf, 0, sizeof(buf));

	buf[0] = MCP_READ_STATUS;

	do_msg(fd, buf, sizeof(buf));
	
	buf[0] = buf[0] & 0x03;
	return buf[0];	
}

void mcp25625_read_canMsg(int fd, const uint8_t buffer_sidh_addr, uint8_t nm)
{
	uint8_t mcp_addr, ctrl;
	uint8_t ide;
	uint16_t id;	
	
	printf("read_canMsg FUNC\n");

	mcp_addr = buffer_sidh_addr;
	
	mcp25625_read_buf(fd, mcp_addr, &ide, &id, nm);

	myCanMsg.canID = id;
	myCanMsg.canIDE = ide;
}

void mcp25625_read_buf(int fd, const uint8_t mcp_addr, uint8_t *ext, uint16_t *id, uint8_t nm)
{
	uint8_t rxbuf[16];
	uint8_t ctrl;
	uint8_t i;	
	uint8_t offset;
	printf("read_buf FUNC\n");

	*ext = 0;
	*id = 0;
	
	 mcp25625_ReadRXBuffer(fd, rxbuf, MCP_READ_RX_BUFFER, nm);
	
	
	for(i=0;i<15;i++)
	{
		if(rxbuf[i] == 0x60)
		{
			offset = i;
			printf("OFFSET = %d\n",offset);
			break;
		}
	}


	
	*id = (rxbuf[MCP_SIDH + offset] << 3) + (rxbuf[MCP_SIDL + offset] >> 5);
	printf("Std ID : 0x%x\n",*id);

	
	if( (rxbuf[MCP_SIDL + offset] & MCP_RXB_EXIDE_M) == MCP_RXB_EXIDE_M)
	{
		*ext = 1;
		*id = (*id << 2) + (rxbuf[MCP_SIDL + offset] & 0x03);
		*id = (*id << 8) + (rxbuf[MCP_EID8 + offset]);
		*id = (*id << 8) + (rxbuf[MCP_EID0 + offset]);
		printf("Ext ID : 0x%x\n",*id);
	}

	
	
	ctrl = mcp25625_readRegister(fd, mcp_addr-1);
	printf("RXBxCTRL : 0x%x\n",ctrl);

	
	myCanMsg.canDLC = rxbuf[4 + offset];
	printf("DLC : 0x%x\n",myCanMsg.canDLC);

	myCanMsg.canDLC = mcp25625_readRegister(fd, mcp_addr+4);
	printf("DLC : 0x%x\n",myCanMsg.canDLC);	

	for(i=0; i<myCanMsg.canDLC; i++)
	{
		myCanMsg.canDATA[i] = rxbuf[i + 5 + offset];
		printf("RXBUF DATA = 0x%x\n",rxbuf[i+5+offset]);
	}

	if(ctrl & MCP_RX_RTR)
		myCanMsg.canRTR = 1;
	else
		myCanMsg.canRTR = 0;

	printf("RTR : 0x%x\n",myCanMsg.canRTR);
}

void mcp25625_ReadRXBuffer(int fd, unsigned char * rxbuf, const uint8_t buffer_addr, uint8_t nm)
{
	int i;
	printf("ReadRXBuffer Func\n");

	if(nm == 0)		
	{
		rxbuf[0] = buffer_addr & 0xF9;	
	}
	else if(nm == 1)
	{
		rxbuf[0] = buffer_addr & 0xF9;
		rxbuf[0] |= 0x04;
	}

	do_msg(fd, rxbuf, 16);
	
	for(i=0;i<15;i++)
	{
		printf("RXB[%d] = 0x%x\n",i,rxbuf[i]);
	}
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
