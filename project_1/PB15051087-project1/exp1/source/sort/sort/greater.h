//
//  greater.h
//  sort
//
//  Created by 姜庆彩 on 2017/9/30.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#ifndef greater_h
#define greater_h
#include <string.h>
int greater(char * a,char * b)// 此函数作用为判断两个字符串的大小关系，先判断长短，长短相等时再比较各位
{
    if(strlen(a)>strlen(b)) return 1;
    else if(strlen(a)<strlen(b))  return 0;
    else{
        if(strcmp(a,b)>0)  return 1;
        else return 0;
    }
    return 0;
}
#endif /* greater_h */
