#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct thread_struct
{
	unsigned long sp1;
//	char sp2;
	unsigned long test;
	unsigned long sp0;
	unsigned long sp;
};

struct task_struct
{
	struct thread_struct thread;
};

struct task_struct *init_task(void)
{
	struct task_struct *tmp = (struct task_struct *)malloc(sizeof(struct task_struct));

	tmp->thread.sp = 3;
}

int main(void)
{
	struct task_struct *cur = NULL;
	
	cur = init_task();
	
	printf("thread.sp = %zd\n",offsetof(struct task_struct, thread.sp));

	return 0;
}
