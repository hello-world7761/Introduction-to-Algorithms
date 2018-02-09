//
//  main.c
//  create_ramdom_numbers
//
//  Created by 姜庆彩 on 2017/10/1.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
int main() {
    const int i =pow(2, 17);
    int source[i];
    int j;
    srand((unsigned)time( NULL ));
    for(j=0; j<i; ++j)
    {
        source[j] = rand() % 65534+1;
        //+1防止产生0
    }
    FILE * fp = fopen("/Users/jqc/Documents/学习/算法基础/project_1/PB15051087-project1/exp2/input/input_numbers.txt", "w+");
   
    for(j=0; j<i; ++j)
    {
        fprintf(fp , "%d" , source[j] );
        fputc('\n',fp);
    }
    return 0;
}
