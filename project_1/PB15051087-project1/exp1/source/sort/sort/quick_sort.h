//
//  quick_sort.h
//  sort
//
//  Created by 姜庆彩 on 2017/9/30.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#ifndef quick_sort_h
#define quick_sort_h
#include "greater.h"
#include <string.h>
int patition(char (*source)[33],int p,int r)
{
    char temp[33];
    char last[33];
    strcpy(last,source[r]);
    int i = p-1;
    int j;
    for (j=p;j<=r-1;j++)
    {
        if(greater(last,source[j]))
        {
            i++;
            if(i!=j){
            strcpy(temp,source[i]);
            strcpy(source[i],source[j]);
            strcpy(source[j],temp);
            }
        }

    }
    strcpy(temp,source[r]);
    if(r!=i+1)
    strcpy(source[r],source[i+1]);
    strcpy(source[i+1],temp);
    return i+1;
}
void quick_sort(char (*source)[33],int p,int r)
{
    int q;
    if(p<r)
    {
        q=patition(source,p,r);
        quick_sort(source,p,q-1);
        quick_sort(source,q+1,r);
    }
}

#endif /* quick_sort_h */
