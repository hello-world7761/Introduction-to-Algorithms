//
//  main.cpp
//  johnson
//
//  Created by 姜庆彩 on 2018/1/5.
//  Copyright © 2018年 姜庆彩. All rights reserved.
//
#include <iostream>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
using namespace std;
typedef struct{
    int d[258];//书本上的d
    int p[258];//书本上的π
    int weight[258][258];
    int vertixNum;
}Graph;

void Random_Weight(int weight[][258], int i);
void reset(int arr[][258], int i);
void inputEdge(int info[][258], int i);
void Initialize_Single_Source(Graph &G, int s);
void Relax(int u, int v, Graph &G);
bool Bellman_Ford(Graph &G, int s);
int FindMin(int d[], int flag[], int bound);
void Print_Path(Graph &G, int v, int s);
bool dijkstra(Graph &G, int s);
bool Johnson(Graph &G);


int scale[6] = {8, 16, 32, 64, 128, 256};
int edgeNum[6] = {24, 64, 160, 384, 896, 2048};

ifstream fin;
ofstream fout;

void Random_Weight(int weight[][258], int i)//构建随机边权值
{
    int edgeProduce = 0, verticeNum = scale[i];
    int low = - edgeNum[i] / scale[i];
    int high = scale[i];
    int rangeSize = high - low + 1;
    int posNum = 0, negNum = 0;
    int negNumLimit = edgeNum[i] / scale[i];
    int posNumLimit = edgeNum[i] - negNumLimit;
    int row, coloum, temp;
    while(edgeProduce < edgeNum[i])
    {
        row = rand() % verticeNum + 1;
        coloum = rand() % verticeNum + 1;
        if(weight[row][coloum] == INT_MAX)
        {
            temp = rand() % rangeSize + low;
            if(temp > 0 && posNum < posNumLimit)
            {
                weight[row][coloum] = temp;
                posNum++;
                edgeProduce++;
            }
            if(temp < 0 && negNum < negNumLimit)
            {
                weight[row][coloum] = temp;
                negNum++;
                edgeProduce++;
            }
        }
    }
}
void reset(int arr[][258], int i)
{
    for(int j=0; j<=i; j++)
        for(int k=0; k<=i; k++)
            arr[j][k] = INT_MAX;
}

void inputEdge(int info[][258], int i)//输入边信息
{
    for(int j=1; j<=i; j++)
    {
        for(int k=1; k<=i; k++)
        {
            if(info[j][k] != INT_MAX)
            {
                fout << left << setw(3) << j << "->" << right << setw(3) << k;
                fout << "   weight:" << info[j][k] << endl;
            }
        }
    }
}
void Initialize_Single_Source(Graph &G, int s)
{
    for(int i=1; i<=G.vertixNum; i++)
    {
        G.d[i] = INT_MAX;
        G.p[i] = -1;
    }
    G.d[s] = 0;
}

void Relax(int u, int v, Graph &G)
{
    if(G.d[v] > G.d[u] + G.weight[u][v])
    {
        G.d[v] = G.d[u] + G.weight[u][v];
        G.p[v] = u;
    }
}

bool Bellman_Ford(Graph &G, int s)
{
    Initialize_Single_Source(G, s);
    for(int i=1; i<G.vertixNum; i++)
    {
        for(int u=1; u<=G.vertixNum; u++)
            for(int v=1; v<=G.vertixNum; v++)
            {
                if(G.weight[u][v] != INT_MAX)
                    Relax(u, v, G);
            }
    }
    for(int u=1; u<=G.vertixNum; u++)
        for(int v=1; v<=G.vertixNum; v++)
        {
            if(G.weight[u][v] != INT_MAX)
            {
                if(G.d[v] > G.d[u] + G.weight[u][v])
                    return false;
            }
        }
    return true;
}
int FindMin(int d[], int flag[], int bound)
{
    int minium = INT_MAX;
    int index = bound;
    for(int i=1; i<=bound; i++)
    {
        if(d[i] < minium && flag[i])
        {
            minium = d[i];
            index = i;
        }
    }
    return index;
}
void Print_Path(Graph &G, int v, int s)
{
    if(v == s)
        fout << s;
    else
    {
        Print_Path(G, G.p[v], s);
        fout << "->" << v;
    }
}

bool dijkstra(Graph &G, int s)
{
    int flag[300];
    int q = G.vertixNum;
    int u;
    Initialize_Single_Source(G, s);
    for(int i=1; i<=G.vertixNum; i++)
        flag[i] = 1;
    while(q--)
    {
        u = FindMin(G.d, flag, G.vertixNum);
        flag[u] = 0;
        for(int v=1; v<=G.vertixNum; v++)
            if(flag[v] && G.weight[u][v] != INT_MAX)
                Relax(u, v, G);
    }
    for(int i=1; i<=G.vertixNum; i++)
        if(G.p[i] == -1 && i != s)
            return false;
    return true;
}

bool Johnson(Graph &G)
{
    int h[300];
    G.vertixNum++;
    for(int i=1; i<G.vertixNum; i++)
        G.weight[G.vertixNum][i] = 0;
    if(!Bellman_Ford(G, G.vertixNum))
        return false;
    else
    {
        for(int i=1; i<G.vertixNum; i++)
            h[i] = G.weight[G.vertixNum][i];
        G.vertixNum--;
        for(int u=1; u<=G.vertixNum; u++)
            for(int v=1; v<=G.vertixNum; v++)
            {
                if(G.weight[u][v] != INT_MAX)
                    G.weight[u][v] = G.weight[u][v] + h[u] - h[v];
            }
        for(int u=1; u<=G.vertixNum; u++)
        {
            if(!dijkstra(G, u))
                return false;
            for(int v=1; v<=G.vertixNum; v++)
            {
                Print_Path(G, v, u);
                if(v == u)
                    fout << "->" << u;
                G.d[v] += h[v] - h[u];
                fout << "   Total Length:" << G.d[v] << endl;
            }
        }
    }
    return true;
}

int main()
{
    srand((unsigned)time(NULL));
    char inputPath[6][200] =
    {
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/input/size1/input.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/input/size2/input.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/input/size3/input.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/input/size4/input.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/input/size5/input.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/input/size6/input.txt"
    };
    char outputSizePath[6][200] =
    {
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size1/output2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size2/output2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size3/output2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size4/output2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size5/output2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size6/output2.txt"
    };
    
    char outputTimePath[6][200] =
    {
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size1/time2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size2/time2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size3/time2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size4/time2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size5/time2.txt",
        "/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project2/output/size6/time2.txt"
    };
    clock_t start, finish;
    double  duration;
    Graph G;
    bool NO_Negetive_circle;
    int weight[258][258];
    for(int i=0; i<6; i++)
    {
        reset(weight, scale[i]);
        Random_Weight(weight, i);
        fout.open(inputPath[i], ios_base::out);
        inputEdge(weight, scale[i]);
        fout.close();
    }
    int i = 0;
    
    while(i<6)
    {
        char s[200];
        reset(G.weight, scale[i]);
        fin.open(inputPath[i]);
        G.vertixNum = scale[i];
        int Read_Num = 0, row, coloum, temp;
        while(Read_Num < edgeNum[i])
        {
            fin >> row;
            fin.getline(s, 10, '>');
            fin >> coloum;
            fin.getline(s, 15, ':');
            fin >> temp;
            G.weight[row][coloum] = temp;
            Read_Num++;
        }
        fout.open(outputSizePath[i], ios_base::out);
        start = clock();
        NO_Negetive_circle = Johnson(G);
        finish = clock();
        
        if(!NO_Negetive_circle)//存在负权值回路
        {
            fout.close();
            fout.open(inputPath[i], ios_base::out);
            reset(weight, scale[i]);
            Random_Weight(weight, i);
            inputEdge(weight, scale[i]);
            i--;
        }
        else
        {
            fout.close();
            fout.open(outputTimePath[i], ios_base::out);
            duration = ((double)(finish - start))/CLOCKS_PER_SEC;
            fout << "Time Cost = " << duration << 's' << endl;
        }
        fout.close();
        fin.close();
        i++;
    }
}

