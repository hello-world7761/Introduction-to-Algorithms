//
//  main.c
//  all_sorts
//
//  Created by 姜庆彩 on 2017/10/1.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <time.h>
int main() {
    int patition(int (*source),int p,int r);
    void quick_sort(int *source, int p, int r);
    void bubble_sort(int *source, int n);
    void counting_sort(int *source,const int n);
    void radix_sort(int *source,const int n);
    const int a[6] = {pow(2,2),pow(2,5),pow(2,8),pow(2,11),pow(2,14),pow(2,17)};
    int j;
    int source[a[5]];
    clock_t start,finish;
    double duration;
    FILE * fp = fopen("/Users/jqc/Documents/学习/算法基础/project_1/PB15051087-project1/exp2/input/input_numbers.txt", "r+");
    FILE * fpw = fopen("/Users/jqc/Documents/学习/算法基础/project_1/PB15051087-project1/exp2/output/radix_sort/result_of_n=17.txt", "w+");
    for (j=0; j<a[5]; ++j)
    {
        fscanf(fp,"%d",&source[j]);
    }
    start = clock();
   // quick_sort(source, 0, a[5]-1);
   // bubble_sort(source, a[5]);
   // counting_sort(source,a[5]);
    radix_sort(source, a[5]);
    finish = clock();
    duration = ((double)(finish - start))/CLOCKS_PER_SEC;
    for (j=0; j<a[5]; ++j)
    {
        printf("%d\n",source[j]);
    }
    for(j=0; j<a[5]; ++j)
    {
        fprintf(fpw , "%d" , source[j] );
        fputc('\n',fpw);
    }
    fprintf(fpw,"%lf",duration);
    fputs(" seconds",fpw);
    printf("This Sort Take %lf seconds\n",duration);
    fclose(fp);
    fclose(fpw);
}


void radix_sort(int *source,const int n)
{
    int temp[n][5];//用于保存source[]的各位数字，以便对各位进行排序
    int i,j,k,l;
    int temp2,temp3;
    for (i=0; i<n; i++)
    {
        for (j=4; j>=0; j--)
        {
            temp[i][4-j] = source[i]/ (int)pow(10,j)%10;//取各位数字
          //  printf("%d %d %d\n",i,j,temp[i][j]);
        }
    }
    for (j=5; j>=0; j--)
    {
        for (i=n-1; i>0; i--) 
        {
            for (k=1; k<n; k++)
            {
                if(temp[k-1][j] > temp[k][j])
                {
                    temp2 = source[k-1];
                    source[k-1] = source[k];
                    source[k] = temp2;
                        for (l=4; l>=0; l--)
                        {
                            temp3 = temp[k-1][l];
                            temp[k-1][l] = temp[k][l];
                            temp[k][l] = temp3;
                        }
                }
            }
        }
    }
}
void counting_sort(int *source, const int n)
{
    int temp[n];
    int store[65535+1];
    int i;
    int j;
    for(i=0; i<n; i++)
    {
        temp[i] = source[i];
    }
    for(i=0; i<=65535; i++)
    {
        store[i] = 0;
    }
    for(j=0; j<n; j++)
    {
        store[temp[j]]++;
    }
    for(i=1; i<65535;i++)
    {
        store[i] = store[i]+store[i-1];
    }
    for(j=n; j>=0;j--)
    {
        source[store[temp[j]]] = temp[j];
        store[temp[j]]--;
    }
}
void bubble_sort(int *source ,int n)
{
    int i,j;
    for(i=n-1; i>0; --i)
    {
        for (j = 1; j < n; ++j)
        {
            if (source[i] > source[j])
            {
                int temp = source[i];
                source[i] = source[j];
                source[j] = temp;
            }
        }
    }
}
void quick_sort(int *source, int p,int r)
{
    int q;
    if(p<r)
    {
        q=patition(source,p,r);
        quick_sort(source,p,q-1);
        quick_sort(source,q+1,r);
    }
}
int patition(int *source, int p, int r)
{
    int temp,last;
    last = source[r];
    int i = p-1;
    int j;
    for (j=p;j<=r-1;j++)
    {
        if(last >= source[j])
        {
            i++;
            if(i!=j){
                temp = source[i];
                source[i] = source[j];
                source[j] = temp;
            }
        }
    }
    temp = source[r];
    if(r!=i+1)
        source[r] = source[i+1];
    source[i+1] = temp ;
    return i+1;
}


