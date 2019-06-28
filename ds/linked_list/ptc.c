#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

void ListInit(List *plist)
{
	plist->head = (Node *)malloc(sizeof(Node));
	plist->head->next = NULL;
	
}
