#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#include <sys/types.h>
#include <sys/poll.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>

#include "serial.h"

using namespace std;
using namespace cv;

//extern char *dev0;
int fd;
char *dev0;
jmp_buf env;

unsigned int sig  =0;
int cnt =0;

void call_exit(int signo)
{
    destroyWindow("Origin Image");
    destroyWindow("Custom ROI Image");
    longjmp(env,1);
}

void my_sig(int signo)
{
    sig =  rand() % 3;
//    printf("%d\n",sig);
}

Mat roi_funce(Mat img, int signo)
{
    Mat output;
    Point mid[3] ={Point(328,71),Point(337,167),Point(341,265)};
    Mat mask = Mat::zeros(img.size(),img.type());
    circle(mask,mid[signo],30,Scalar(255,255,255),-1);
    bitwise_and(img,mask,output);
    return output;
}

int main(int argc, char **argv)
{
    int w, h;
    int ret;
    char buf[2] ={0,0};
    Mat img;
    Mat roi;

    dev0 ="/dev/ttyACM0";//lauchpad

    signal(SIGINT, call_exit);
    signal(SIGALRM, my_sig);

    fd = serial_config(dev0);
    img = imread("traffic.jpg",-1);

    if(img.empty())
        return -1;

    h = img.rows;
    w = img.cols;

    printf("h = %d, w = %d\n", h, w);

    imshow("Origin image",img);
    imshow("Traffic Image",img);
    waitKey(1);

    if(!(ret = setjmp(env)))
    {
        for(;;)
        {
            alarm(5);
            pause();
            buf[0] = (char)(sig+1) | 0x30;
            roi = roi_funce(img,sig);
            printf("%c\n",buf[0]);
            imshow("Traffic Image",roi);
            waitKey(500);
            send_data(fd, buf, 1, 0);
            memset(buf,0x0,2);
        }
    }

    buf[0] ='1';
    send_data(fd,buf,1, 0);
    wait(10);
    close_dev(fd);
    return 0;
}

