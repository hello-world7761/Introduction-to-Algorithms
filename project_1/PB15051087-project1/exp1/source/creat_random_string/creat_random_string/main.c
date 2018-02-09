//
//  main.c
//  creat_random_number
//
//  Created by 姜庆彩 on 2017/9/29.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <math.h>
//产生长度为length的随机字符串
int genRandomString(int length,char* ouput)
{
    int i;
    //srand((unsigned)time( NULL ));
    for (i = 0; i < length; i++)
    {
        ouput[i] = 'a' + rand() % 26;
    }
    return 0;
}

int main()
{
    int j,i;
    //char line2[32];
    FILE *fp = fopen("/Users/jqc/Documents/学习/算法基础/project_1/PB15051087-project1/exp1/input/input_strings.txt", "w+");
    srand((unsigned)time( NULL ));
    if (fp==0) {
        printf("can't open file\n");
        return 0;
    }
    for(i=pow(2,17);i>0;i--)
    {
    j = rand() % 31 + 1;//防止空串出现
    char line[32] = {0};
    memset(line, 0, 32);
    genRandomString(j, line);
    printf("line=%s\n", line);
    fputs(line,fp);
    fputc('\n',fp);
    }
    /*fseek(fp,0,SEEK_SET);
    fscanf(fp,"%s",line2);
    puts(line2);*/
    fclose(fp);
    
}
