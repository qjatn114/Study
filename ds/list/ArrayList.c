#include <stdio.h>
#include "ArrayList.h"

void ListInit(List *plist)
{
	plist->numOfData = 0;				//현재 데이터 수는 0
	plist->curPosition = -1;			//현재 아무 위치도 가르키지 않음
}

void LInsert(List *plist, LData data)
{
	if(plist->numOfData >= LIST_LEN)
	{
		puts("저장 불가");
		return;
	}
	
	plist->arr[plist->numOfData] = data;		//데이터 저장
	(plist->numOfData)++;						//저장된 데이터 수 증가
}

int LFirst(List *plist, LData *pdata)
{
	if(plist->numOfData == 0)
		return FALSE;
	
	plist->curPosition = 0;
	*pdata = plist->arr[0];
	return TRUE;
}

int LNext(List *plist, LData *pdata)
{
	if(plist->curPosition >= (plist->numOfData)-1)
		return FALSE;

	(plist->curPosition)++;
	*pdata = plist->arr[plist->curPosition];
	return TRUE;
}

LData LRemove(List *plist)
{
	int rpos = plist->curPosition;		//삭제할 데이터의 인덱스 값 참조
	int num = plist->numOfData;
	int i;
	LData rdata = plist->arr[rpos];		//삭제할 데이터를 임시 저장

//삭제를 위한 데이터의 이동을 진행하는 반복문
	for(i=rpos;i<num-1;i++)
		plist->arr[i] = plist->arr[i+1];

	(plist->numOfData)--;
	(plist->curPosition)--;
	return rdata;
}

int LCount(List *plist)
{
	return plist->numOfData;
}
