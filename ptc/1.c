#include <stdio.h>
#include <stdlib.h>

typedef struct __node
{
	int data;
	struct __node *next;
}Node;

typedef struct __list
{
	Node *head;
	Node *before;
	Node *cur;
	int numOfData;
	int (*comp)(int,int);
	
}List;


typedef int LData;

void List_Init(List *plist);
void LInsert(List *plist,int data);
int LFirst(List *plist, int *data);
int LNext(List *plist,int *data);
LData LRemove(List *plist);
int LCount(List *plist);
void FInsert(List *plist,int data);
void SInsert(List *plist,int data);

void SetSortRule(List *plist,int (*comp)(int,int));
int WhoIsPrecede(int d1,int d2);

int main(void)
{
	List list;
	int data;
	List_Init(&list);

	SetSortRule(&list,WhoIsPrecede);

	LInsert(&list,11);
	LInsert(&list,11);
	LInsert(&list,22);
	LInsert(&list,22);
	LInsert(&list,33);

	printf("current data : %d\n",LCount(&list));

	if(LFirst(&list,&data))
	{
		printf("%d",data);
		while(LNext(&list,&data))
			printf("%d",data);
	}
	printf("\n\n");

	if(LFirst(&list,&data))
	{
		if(data == 22)
			LRemove(&list);

		while(LNext(&list,&data))
		{
			if(data ==22)
				LRemove(&list);
		}
	}
	printf("current data %d\n",LCount(&list));

	if(LFirst(&list,&data))
	{
		printf("%d",data);
		while(LNext(&list,&data))
			printf("%d",data);
	}
	printf("\n\n");

	return 0;
}


void List_Init(List *plist)
{
	plist->head = (Node *)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->numOfData = 0;
	plist->comp = NULL;
}

void LInsert(List *plist,int data)
{
	if(!plist->comp)
		FInsert(plist,data);
	else
		SInsert(plist,data);
}

void FInsert(List *plist,int data)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;
}

void SInsert(List *plist,int data)
{
	Node *tmp = plist->head;
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;

	while( !(tmp->next == NULL) && (plist->comp(data,tmp->next->data) ))
		tmp = tmp->next;
	newNode->next = tmp->next;
	tmp->next = newNode;
}

int LFirst(List *plist, int *data)
{
	if(plist->head->next == NULL)
		return 0;
	*data = plist->head->next->data;
	plist->before = plist->head;
	plist->cur = plist->head->next;
	return 1;
}

int LNext(List *plist,int *data)
{
	if(plist->cur->next == NULL)
		return 0;
	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*data = plist->cur->data;
	return 1;
}

LData LRemove(List *plist)
{
	Node *rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List *plist)
{
	return plist->numOfData;
}

void SetSortRule(List *plist,int (*comp)(int,int))
{
	plist->comp = comp;
}
int WhoIsPrecede(int d1,int d2)
{
	if(d1>d2)
		return 1;
	else
		return 0;
}
