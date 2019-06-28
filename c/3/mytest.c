#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void init_rand_num(int arr[])
{
        int i;
        for(i=0;i<100;i++)
        {
                arr[i] = rand() % 9 +1;
        }
}

void make_freq_table(int ft[],int fn[])
{
        int i;
        for(i=0;i<100;i++)
        {
                ft[fn[i]]++;
        }
}

void print_arr(int arr[], int len)
{
        int i, flag=1;
        for(i=1;i<len+1;i++)
        {
                printf("%3d",arr[i-1]);
                if( !(i%10))
                {
                        printf("\n");
                }
        }
}

bool check_dup(int max_tab[],int ft[],int len)
{
        int i,j;
        for(i=0;i<len;i++)
        {
                for(j=i+1; j<len; j++)
                {
                        if(max_tab[i] == max_tab[j])
                        {
                                //주소 초기할 값, 몇 바이트 초기화 할 것읹.
                                memset(ft,0x0,40);
                                return true;
                        }
                }
        }    
        return false;
}

void make_max_tab(int max_tab[],int freq_tab[])
{
        int i,j,key,len = 10;

        //삽입 정렬 알고리즘
        //데이터의 개수가 적을 때 빠름
        //데이터의 개수가 정해져 있을 경우엔 Quick Sort도 빠름
        for(i=len-1;i>0;i--)
        {
                key = freq_tab[i - 1];

                for(j=i;freq_tab[j]>key;j++)
                {
                        freq_tab[j-1] = freq_tab[j];
                }
                freq_tab[j-1] = key;
        }
        printf("max freq_tab: ");
        for(i=0;i<11;i++)
        {
                printf("%3d",freq_tab[i]);
        }
        printf("\n");

        for(i=0;i<3;i++)
        {
                max_tab[i] = freq_tab[i];
        }
}

int main(void)
{
        int freq_num[100] = {0};
        int freq_tab[11] = {0};
        int max_tab[5] = {0};

        srand(time(NULL));

        while(check_dup( max_tab,freq_tab,4))
        {
                init_rand_num(freq_num);
                printf("Print Random Number\n");
                print_arr(freq_num,100);

                printf("Print Frequency Table\n");
                make_freq_table(freq_tab,freq_num);
                print_arr(freq_tab,10);
 
                printf("Print Max Number\n");
                make_max_tab(max_tab,freq_tab);
        }

        printf("Succeeful to avoid redundancy!\n");
        print_arr(max_tab,3);
        printf("\n");


        return 0;
}
