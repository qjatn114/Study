/*
* Copyright (C) 2013 - 2016  Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or (b) that interact
* with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_DEV				"/dev/i2c-0"

#define LIDAR_ADDR			0x62
#define ACQ_COMMAND			0x00
#define STATUS				0x01
#define SIG_COUNT_VAL		0x02
#define ACQ_CONFIG_REG		0x04
#define THRESHOLD_BYPASS	0x1C
#define READ_FROM			0x89

#define NO_CORRECTION		0
#define CORRECTION			1

#define AR_VELOCITY			0
#define AR_PEAK_CORR		1
#define AR_NOISE_PEAK		2
#define AR_SIGNAL_STRENGTH	3
#define AR_FULL_DELAY_HIGH	4
#define AR_FULL_DELAY_LOW	5

#define OUTPUT_OF_ALL		0
#define DISTANCE_ONLY		1
#define DISTANCE_WITH_VEL	2
#define VELOCITY_ONLY		3

#define USAGE				"exe 1\n"

unsigned get_status(void);
void lidar_read(unsigned char, unsigned, unsigned char *);
void lidar_write(unsigned char, unsigned char);
void measurement(unsigned char, unsigned char, unsigned char *);
void display(unsigned char, unsigned char *);

int fd = 0;

int main(int argc, char **argv)
{
	unsigned char receives[8] = {AR_VELOCITY, 0,
								0, AR_PEAK_CORR,
								AR_NOISE_PEAK, AR_SIGNAL_STRENGTH,
								AR_FULL_DELAY_HIGH, AR_FULL_DELAY_LOW};

	unsigned char i, options;

	char * fname = NULL;

	if(argc <2)
		printf("%s\n", USAGE);
	else 
		fname = I2C_DEV;

	options = atoi(argv[1]);

	if((fd = open(fname, O_RDWR))<0)
	{
		perror("Open error");
		return -1;
	}

	if(ioctl(fd, I2C_SLAVE, LIDAR_ADDR)<0)
	{
		perror("Slave Addr Connect Error");
		return -1;
	}

	lidar_write(SIG_COUNT_VAL, 0x80);
	lidar_write(ACQ_CONFIG_REG, 0x08);
	lidar_write(THRESHOLD_BYPASS, 0x00);

	for(;;)
	{
		measurement(CORRECTION, options, receives);

		for(i=0; i<99; i++)
			measurement(NO_CORRECTION, options, receives);
	}	

	close(fd);

	return 0;
}

unsigned get_status(void)
{
	unsigned char buf[1] = {STATUS};

	if(write(fd, buf, 1) != 1)
	{
		perror("Write Reg Error!");
		return -1;
	}

	if(read(fd, buf, 1)!=1)
	{
		perror("Read Reg Error");
		return -1;
	}

	return buf[0] & 0x01;
}

void lidar_read(unsigned char reg, unsigned read_size, unsigned char * receives)
{
	unsigned char buf[1] = {reg};
	unsigned busy_flag = 1;
	unsigned busy_counter = 0;

	while(busy_flag)
	{
		busy_flag = get_status();
		busy_counter++;

		if(busy_counter > 9999)
		{
			printf("Busy Count Time Out!\n");
			return;
		}
	}

	if(!busy_flag)
	{
		if(write(fd, buf, 1)!=1)
		{
			perror("Write Reg Error");
			return;
		}

		if(read(fd, receives, read_size) != read_size)
		{
			perror("Read Reg Error");
			return;
		}
	}
}

void lidar_write(unsigned char reg, unsigned char val)
{
	unsigned char buf[2] = {reg, val};

	if(write(fd, buf, 2)!= 2)
	{
		perror("Write Reg Error");
		return;
	}

	usleep(1000);
}

void measurement(unsigned char is_corr, unsigned char opt, unsigned char * buf)
{
	unsigned char i;

	if(is_corr)
		lidar_write(ACQ_COMMAND, 0x04);
	else
		lidar_write(ACQ_COMMAND, 0x03);

	lidar_read(READ_FROM, 8, buf);

	for(i=0; i<6; i++)
		buf[i] = buf[i+2];

	display(opt, buf);
}

void display(unsigned char opt, unsigned char *buf)
{
	unsigned char i;
	char * strings[5] = {"Velocity", NULL, NULL, NULL, "Distance"};
	int tmp_data;
	tmp_data = buf[AR_FULL_DELAY_HIGH] << 8 | buf[AR_FULL_DELAY_LOW];

	switch(opt)
	{
		case DISTANCE_ONLY:
			printf("%s\t\t\t = %d\n", strings[4], tmp_data);
			break;
	}
	printf("\n");
}
