//
//  main.c
//  sort
//
//  Created by 姜庆彩 on 2017/9/30.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "insert_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"
#include "merge_sort.h"
int main() {
    const int a[6] = {pow(2,2),pow(2,5),pow(2,8),pow(2,11),pow(2,14),pow(2,17)};//排序规模，每次变换规模时讲所有的a[]替换
    char source[a[0]][33];
    int i;
    FILE *fp,*fpw;
    clock_t start,finish;
    double duration;
    if((fp=fopen("/Users/jqc/Documents/学习/算法基础/project_1/PB15051087-project1/exp1/input/input_strings.txt","r+"))==NULL)
    {
        printf("Open file ERROR");
    }
   // printf("%d",a[0]);
    for(i=0;i<a[0];i++)
    {
   
        fscanf(fp,"%s",source[i]);
    }
    start = clock();
    // insert_sort(source,a[0]);
    // heap_sort(source,a[0]-1);
    // quick_sort(source,0,a[0]-1);
    merge_sort(source, 0, a[0]-1);
    finish = clock();
    duration = ((double)(finish - start))/CLOCKS_PER_SEC;

    for(i=0;i<a[0];i++)
    {
        
        printf("%s\n",source[i]);
    }
    if((fpw=fopen("/Users/jqc/Documents/学习/算法基础/project_1/PB15051087-project1/exp1/output/merge_sort/result_of_sort_n=2.txt","w"))==NULL)
    {
        printf("Open file ERROR");
    }
    for(i=0;i<a[0];i++)
    {
        fputs(source[i],fpw);
        fputc('\n',fpw);
        
    }
    fprintf(fpw,"%lf",duration);
    fputs(" seconds",fpw);
    printf("This Sort Take %lf seconds\n",duration);
   // printf("%d",CLOCKS_PER_SEC);
    fclose(fp);
    fclose(fpw);
}

