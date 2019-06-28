#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int cnt;

typedef struct __tree
{
	int data;
	struct __tree *left;
	struct __tree *right;
}tree;

typedef struct __stack
{
	void *data;
	struct __stack *link;
}stack;

stack *get_stack_node(void)
{
	stack *tmp;
	tmp = (stack *)malloc(sizeof(stack));
	tmp->link = NULL;
	
	return tmp;
}

tree *get_tree_node(void)
{
	tree *tmp = (tree *)malloc(sizeof(tree));
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

void *pop(stack **top)
{
	stack *tmp = *top;
	void *data = NULL;

	if(*top == NULL)
	{
		printf("stack is empty\n");
		return NULL;
	}
	
	data = (*top)->data;
	*top = (*top)->link;
	free(tmp);

	//return (*top)->data;

	return data;
}

void push(stack **top, void *data)
{
	if(data == NULL)
	{
		return;
	}
	
	stack *tmp = *top;
	*top = get_stack_node();
	(*top)->data = malloc(sizeof(void *));
	(*top)->data = data;
	(*top)->link = tmp;
}

bool stack_is_not_empty(stack *top)
{
	if(top!=NULL)
		return true;
	else
		return false;
}

void non_recur_tree_ins(tree **root,int data)
{
	tree **tmp = root;
	
	while(*tmp)
	{
		if( (*tmp)->data > data )
		{
			tmp = &(*tmp)->left;
		}
		else if( (*tmp)->data < data )
		{
			tmp = &(*tmp)->right;
		}
	}

	*tmp = get_tree_node();
	(*tmp)->data = data;
}


void find_max(tree **root,int *data);
tree *chg_node(tree *root);

void non_recur_delete_tree(tree **root,int data)
{
	tree **tmp = root;
	int num;
	
	while(*tmp)
	{
		if( (*tmp)->data > data)
		{
			tmp = &(*tmp)->left;
		}
		else if( (*tmp)->data < data)
		{
			tmp = &(*tmp)->right;
		}
		else if( (*tmp)->left && (*tmp)->right)
		{
			find_max(&(*tmp)->left,&num);
			(*tmp)->data = num;
			return;
		}
		else
		{
			(*tmp) = chg_node(*tmp);
			return;
		}
	}

	printf("Not Found\n");
}

tree *chg_node(tree *root)
{
	tree *tmp = root;

	if( !root->right)
	{
		root = root->left;
	}
	else if( !root->left )
	{
		root = root->right;
	}
	
	free(tmp);
	
	return root;
}


void find_max(tree **root,int *data)
{
	tree **tmp = root;

	while(*tmp)
	{
		if( (*tmp)->right)
		{
			tmp = &(*tmp)->right;
		}
		else
		{
			*data = (*tmp)->data;
			*tmp = chg_node(*tmp);
			break;
		}
	}
}


void print_tree(tree **root)
{
	tree **tmp = root;
	stack *top = NULL;
	
	push(&top,*tmp);
	
	while(stack_is_not_empty(top))
	{
		tree *t = (tree *)pop(&top);
		tmp = &t;
	
		printf("data = %d, ",(*tmp)->data);

		if( (*tmp)->left)
			printf("left = %d, ",(*tmp)->left->data);
		else
			printf("left = NULL, ");

		if( (*tmp)->right)
			printf("right = %d\n",(*tmp)->right->data);
		else
			printf("right = NULL\n");

		push(&top,(*tmp)->right);
		push(&top,(*tmp)->left);
	}
}

int main(void)
{
	int data[10] = {50,100,25,17,23,15,20,75,80};
	tree *root = NULL;
	int i;

	for(i=0; data[i];i++)
	{
		non_recur_tree_ins(&root,data[i]);
	}
	
	print_tree(&root);

	return 0;
}

