#include <stdio.h>
#include <stdbool.h>

void num_goto_test(void)
{
	int i,j,k;
	bool flag = false;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			for(k=0;k<5;k++)
			{
				if(i==1 &&j==4&&k==0)
				{
					printf("Num_goto Error Accurance\n");
					flag = true;
				}

				if(flag)
				{
					printf("num_goto\n");
					break;
				}
			}
			
			if(flag)
			{
				printf("num_goto\n");
				break;
			}
		}
		
		if(flag)
		{
			printf("num_goto\n");
			break;
		}
	}
}

void goto_test(void)
{
	int i,j,k;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			for(k=0;k<5;k++)
			{
				if(i==1 &&j==4&&k==0)
				{
					printf("Error Accurance\n");
					goto finish;
				}
			}
		}
		
	}

	printf("Exit Normally\n");
	return;

finish:
	printf("Error Handler\n");
}	
int main(void)
{
	num_goto_test();
	goto_test();
	
	return 0;
}
