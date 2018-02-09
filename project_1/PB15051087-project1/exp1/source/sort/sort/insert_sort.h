//
//  insert_sort.h
//  insert_sort
//
//  Created by 姜庆彩 on 2017/9/30.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#ifndef insert_sort_h
#define insert_sort_h

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "greater.h"

void insert_sort(char (*source)[33],int n)//a为数组，n为数组个数
{
    int i,j;
    char temp[33];
    for (j = 1;j < n;j++) {
        i = j - 1;
        strcpy(temp,source[j]);
        while (i >= 0 && greater(source[i],temp) ){
            strcpy(source[i+1],source[i]);
            i--;
        }
        //a[i+1]=*key;
        strcpy(source[i+1],temp);
    }
}

#endif /* insert_sort_h */
