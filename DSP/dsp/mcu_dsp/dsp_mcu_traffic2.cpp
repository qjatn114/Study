#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <fcntl.h>

#include "serial.h"

using namespace cv;
using namespace std;

extern char *dev0;
jmp_buf env;
int fd, rnd_time, rnd_pic;

void call_exit(int signo)
{
	longjmp(env, 1);
}

void rand(int signo)
{
	srand(time(NULL));
	rnd_time = rand() % 10 + 1;
	rnd_pic = rand() % 3 + 1;
	
	printf("rnd_time = %d\n", rnd_time);
	printf("rnd_pic = %d\n", rnd_pic);
}

int main(int argc, char **argv)
{
	int ret;
	char buf[32] = "";
	srand(time(NULL));
	rnd_time = rand() % 10 + 1;
	rnd_pic = rand() % 3 + 1;

	signal(SIGINT, call_exit);
	signal(SIGALRM, rand);

	dev0 = "/dev/ttyACM0";
	fd = serial_config(dev0);
	
	Mat rimg = imread("red.png", -1);
	Mat gimg = imread("green.jpg", -1);
	Mat yimg = imread("yellow.jpg", -1);

	if(!(ret = setjmp(env)))
	{
		for(;;)
		{
			alarm(rnd_time);
			
			switch(rnd_pic)
			{
			case 1:
				imshow("RED",rimg);
				waitKey(100);
				printf("RED, STOP\n");
				buf[0] = '1';
				break;
			case 2:
				imshow("YELLOW",yimg);
				waitKey(100);
				printf("YELLOW, FULL ACCEL\n");
				buf[0] = '2';
				break;
			case 3:
				imshow("GREEN",gimg);
				waitKey(100);
				printf("GREEN, GO\n");
				buf[0] = '3';
				break;
			default:
				break;
			}
			send_data(fd, buf, 1, 0);

			printf("*********** rnd_pic = %d *************\n",rnd_pic);

			if(rnd_pic == 1)
			{
				destroyWindow("RED");
				waitKey(10);
			}
			else if(rnd_pic == 2)
			{
				destroyWindow("YELLOW");
				waitKey(10);
			}
			else if(rnd_pic == 3)
			{
				destroyWindow("GREEN");
				waitKey(10);
			}

			pause();
		}
	}

	close_dev(fd);

	return 0;
}

