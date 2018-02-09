//
//  heap_sort.h
//  sort
//
//  Created by 姜庆彩 on 2017/9/30.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#ifndef heap_sort_h
#define heap_sort_h
#include <string.h>
#include "greater.h"
int parent(int i)
{
    return i/2;
}
int left(int i)
{
    return 2*i;
}
int right(int i)
{
    return 2*i+1;
}
void max_heapify(char (*source)[33],int n,int i)
{
    int l = left(i);
    int r = right(i);
    int largest;
    char  temp[33];
    if(l<=n && greater(source[l],source[i]))
    {
        largest = l;
    }
    else largest = i;
    if(r<=n && greater(source[r],source[largest]))
    {
        largest = r;
    }
    if (largest != i)
    {
        strcpy(temp,source[i]);
        strcpy(source[i],source[largest]);
        strcpy(source[largest],temp);
        max_heapify(source,n,largest);
    }
}
void build_max_heap(char (*source)[33],int n)
{
    int k;
    for (k = n/2 ;k>=1;k--)
    {
        max_heapify(source,n,k);
    }
}
void heap_sort(char (*source)[33],int n)
{
    char  temp[33];

    build_max_heap(source,n);
    int flag = n;
    int j;
    for(j = n;j>=2;j--)
    {
        strcpy(temp,source[1]);
        strcpy(source[1],source[j]);
        strcpy(source[j],temp);
        flag--;
        max_heapify(source,flag,1);
    }
}
#endif /* heap_sort_h */
