#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat edge_detect(Mat blur)
{
    Mat output;

    cvtColor(blur, output, COLOR_RGB2GRAY);
    threshold(output,output,50,150,THRESH_BINARY);

    return output;
}

int main(int argc , char** argv)
{
    Mat img=imread("sample.jpg",-1);
    Mat blur;
    Mat edge;

    if(img.empty()){
        return -1;
    }

    GaussianBlur(img,blur,Size(3,3),0,0);

    edge=edge_detect(blur);

    imwrite("org_img.jpg",img);
    imwrite("edge.jpg",edge);

    imshow("Origin Image", img);
    imshow("Edge Image",edge);

    waitKey(0);

    destroyWindow("Origin Image");
    destroyWindow("Edge Image");

    return 0;
}
