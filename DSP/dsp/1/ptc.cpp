#include <opencv2/core/core.hpp>	//라이브러리의 핵심적인 기능이 포함. 특히 기본 자료구조와 연산 함수 포함
#include <opencv2/highgui/highgui.hpp> //영상과 비디오를 읽고 쓰는 함수를 포함
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat imge;	//영상을 담을 변수를 선언 cv::Mat 클래스의 객체를 정의한다. 0x0 크기를 갖는 영상을 정의한다.

	Mat result;

	image = imread("sample.jpg");	//영상을 읽어 디코딩하고 메모리에 할당하기 위한 읽기 함수를 간단하게 호출

	if( !image.data)		//멤버 변수인 data는 실제로 영상 데이터가 들어갈 할당된 메모리 블록을 가리키는 변수
	{
		cout<<"입력영상 오류"<<endl;		
	}


	cout <<"size:"<<image.size().height<<","<<image.size().width<<endl;
	flip(image,result,1);

	namedWindow("Original Image");	// 창을 정의
	imshow("Original Image",image);	//영상을 보여주기
	namedWindow("Output Image");
	imshow("Output Image",result);
	waitKey(0);
	return 0;
}
