#include <stdio.h>
#include <stdlib.h>

int cnt;


typedef struct __tree
{
	int data;
	struct __tree *left;
	struct __tree *right;
}tree;

tree *get_tree_node(void)
{
	tree *tmp = (tree *)malloc(sizeof(tree));
	tmp->left = NULL;
	tmp->right = NULL;

	return tmp;
}

void tree_ins(tree **root,int data)
{
	++cnt;

	if( !(*root) )
	{
		printf("data = %d, cnt = %d\n",data,cnt);

		*root = get_tree_node();
		(*root)->data = data;

		cnt = 0;

		return;
	}
	
	//현재 중복은 고려하고 있지 않음
	if( (*root)->data > data )
	{
		tree_ins( &(*root)->left,data);
	}
	else
	{
		tree_ins( &(*root)->right,data);
	}

}


void find_max(tree **f_max,int *max);
void chg_node(tree **node);

void del_tree(tree **root,int data)
{
	if( !(*root) )
	{
		printf("There are not node\n");
		return;
	}
	
	//
	if( (*root)->data > data)
	{
		del_tree( &(*root)->left,data);
	}
	else if( (*root)->data < data)
	{
		del_tree( &(*root)->right,data);
	}
	else if( (*root)->left && (*root)->right)
	{
		int max;
		find_max( &(*root)->left,&max);
		(*root)->data = max;
	}
	else
	{
		chg_node(root);
	}
}

void chg_node(tree **node)
{
	tree *tmp = *node;

	if( !(*node)->right)
	{
		*node = (*node)->left;
	}
	else if( !(*node)->left )
	{
		*node = (*node)->right;
	}
	
	free(tmp);
}


void find_max(tree **f_max,int *max)
{
	if( !((*f_max)->right) )
	{
		find_max( &(*f_max)->right,max);
	}	
	else
	{
		*max = (*f_max)->data;
		chg_node(f_max);
	}
}


void print_tree(tree *root)
{
	if(root)
	{
		printf("\n\n\ndata = %d, ",root->data);

		if(root->left)
		{
			printf("left = %4d,",root->left->data);
		}
		else
		{
			printf("left = NULL,");
		}
		if(root->right)
		{
			printf("right = %4d\n",root->right->data);
		}
		else
		{
			printf("right = NULL\n");
		}
		print_tree(root->left);
		print_tree(root->right);
	}
}

int main(void)
{
	int data[10] = {50,100,25,17,23,15,20,75,80};
	tree *root = NULL;
	int i;

	for(i=0; data[i];i++)
	{
		tree_ins(&root,data[i]);
	}
	
	print_tree(root);

	return 0;
}
