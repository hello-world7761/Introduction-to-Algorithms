//
//  merge_sort.h
//  sort
//
//  Created by 姜庆彩 on 2017/10/1.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#ifndef merge_sort_h
#define merge_sort_h
#include <string.h>
#include "greater.h"
void merge(char (*source)[33],int p,int q,int r)
{
    const int n1 = q-p+1;
    const int n2 = r-q;
    int i, j, k, l, o;
    char L[n1+1][33];
    char R[n2+1][33];
    for (l = 0;l < n1;l++)
    {
   
        strcpy(L[l], source[p+l]);

    }
    for (o = 1;o <= n2;o++)
    {
        strcpy(R[o-1], source[q+o]);
    }
    strcpy(L[n1],"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");//对应书本上的无穷大字符串
    strcpy(R[n2],"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
    i = 0;
    j = 0;
    for (k = p; k <= r; ++k)
    {
        if(greater(R[j], L[i]))
           {
               strcpy(source[k], L[i]);
               ++i;
           }
        else
           {
               strcpy(source[k], R[j]);
               ++j;
           }
    }
    
}
void merge_sort(char (*source)[33], int p, int r)
{
    int q;
    if (p < r)
    {
        q = (p+r)/2;
        merge_sort(source, p, q);
        merge_sort(source, q+1, r);
        merge(source, p, q, r);
    }
}
    

#endif /* merge_sort_h */
