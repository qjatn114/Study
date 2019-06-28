#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


typedef struct __tree
{
	int data;
	int left_idx;
	int right_idx;
}tree;

typedef struct __tree_manager
{
	int cur_idx;
	int elem_num;
	int start_idx;
	tree *arr;
}tm;



void tree_ins(tm *m,int data)
{
	int idx = m->start_idx;

	while(m->arr[idx].data)
	{
		if(m->arr[idx].data >data)
		{
			idx = m->arr[idx].left_idx;
		}
		else if(m->arr[idx].data < data)
		{
			idx = m->arr[idx].right_idx;
		}
	}

	m->arr[idx].data = data;
	m->elem_num++;
	m->arr[idx].left_idx = ++m->cur_idx;
	m->arr[idx].right_idx = ++m->cur_idx;
}


void init_tree_manager(tm *m)
{
	tree *tmp = (tree *)malloc(sizeof(tree) * 128);
	memset(tmp,0x0,sizeof(tree)*128);

	(*m).arr = tmp;
	(*m).cur_idx = 0;
	(*m).start_idx = 0;
}

void print_tree(tm m)
{
	int i,j;

	for(i=j=0;j<m.elem_num;i++,j++)
	{
		if(m.arr[i].data ==0)
			j--;
		else
		{
			printf("data = %3d\n",m.arr[i].data);
			printf("left = %3d\n",m.arr[m.arr[i].left_idx].data);
			printf("right = %3d\n\n",m.arr[m.arr[i].right_idx].data);
		}
	}
}

int main(void)
{
	int i;
	int data[14] = {20,10,30,50,70,60,40,90,80,100};
	int del[4] = {50,70,10};
	
	tm manager = {0};
	fa free_arr = {0};
	
	init_tree_manager(&manager);
	init_free_arr(&free_arr);

	for(i=0;data[i];i++)
	{
		tree_ins(&manager,data[i]);
	}	

	print_tree(manager);
	
	for(i=0;del[i];i++)
	{
		tree_del(&manager,del[i],&free_arr);
	}
	printf("After Delete\m");
	print_tree(manager);

	return 0;
}
