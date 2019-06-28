#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct person
{
	char name[20];
	int rand_num;
}p;

void raffle(p *m)
{
	int i,j;
	int tmp;

	srand(time(NULL));

	for(i=0;i<22;i++)
	{
redo:
		tmp = rand() %22 +1;
		for(j=i;j>=0;j--)
		{
			if(m[j].rand_num==tmp)
			{
				goto redo;
			}
		}
		m[i].rand_num = tmp;
	}
}

void print_res(p *m)
{
	int i;
	printf("Result : \n");

	for(i=1;i<23;i++)
	{
		printf("%s -%3d   ",m[i - 1].name,m[i-1].rand_num);

		if( !(i%3) )
		{
			printf("\n");
		}
	}
	printf("\n");
}

int main(void)
{
	//구조체 배열
	p member[23] = {
			{"박민지",},{"이주환",},{"이동훈",},{"유영재",}, 
			{"정범수",},{"양성민",},{"김동혁",},{"한지용",},
			{"이도일",},{"이창호",},{"안경환",},{"김동주",},
			{"최지영",},{"한보미",},{"김왕배",},{"김주호",},
			{"이대로",},{"홍기화",},
			};
	raffle(member);
	print_res(member);

	return 0;
}
