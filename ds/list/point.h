#ifndef __POINT_H_
#define __POINT_H_

typedef struct _point
{
	int xpos;
	int ypos;
}Point;

//Point변ㅅ의 xpos, ypos값 설정
void SetPointPos(Point *ppos, int xpos, int ypos);

//Point변수의 xpos, ypos 정보 출력
void ShowPointPos(Point *ppos);

//두 Point변수 비교
int PointComp(Point *pos1,Point *pos2);

#endif
