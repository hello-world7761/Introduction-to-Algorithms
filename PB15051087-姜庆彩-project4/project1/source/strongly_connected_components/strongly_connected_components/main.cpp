//
//  main.cpp
//  strongly_connected_components
//
//  Created by 姜庆彩 on 2017/12/17.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//
#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 128
using namespace std;
ofstream fout("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project1/output/size5/output1.txt");
class Graph {
    int V;    // 顶点个数
    list<int> *adj;    //邻接表 最晚的完成时间的顶点放在栈顶
    void fillOrder(int v, bool visited[], stack<int> &Stack);// DFS打印以v起点的边
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);
    void addEdge(int v, int w);//打印所有的强连通分量
    void printSCCs();//得到当前图的转置图
    Graph getTranspose();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int> [V];
}

void Graph::DFSUtil(int v, bool visited[]) {
    visited[v] = true;
    fout << v << " ";
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

Graph Graph::getTranspose() {
    Graph g(V);
    for (int v = 0; v < V; v++) {
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i) {
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) {
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            fillOrder(*i, visited, Stack);
    
    //所有从v顶点可达的顶点都已处理完，v顶点访问完成
    Stack.push(v);
}

void Graph::printSCCs() {
    stack<int> Stack;
    
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    // 根据完成时间压入栈中，栈顶是完成时间最晚的顶点
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            fillOrder(i, visited, Stack);
    
    // 创建转置图
    Graph gr = getTranspose();
    // 准备第二次DFS
    for (int i = 0; i < V; i++)
        visited[i] = false;
    
    while (Stack.empty() == false) {
        int v = Stack.top();
        Stack.pop();
        // 打印以v为起点的强连通分量
        if (visited[v] == false) {
            fout <<"以下一行为强连通分量"<<endl;
            gr.DFSUtil(v, visited);
            fout << endl;
        }
    }
}

int main() {
    // 创建图
    clock_t start,finish;
    double duration;
    Graph g(N);
    int count = -1;
    int x = N;
    while(x != 0){
        x = x / 2;
        count++;
    }
    int m = 0;
    m = N * count;
    int flag[N][N] = {0};
    int *a = new int[m];
    int *b = new int[m];
    start = clock();
    FILE *fp;
    fp=fopen("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project1/input/size5/input.txt","w");
    ofstream time1("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project4/project1/output/size5/time1.txt");
    srand((unsigned) time(NULL));
    for(int i = 0;i < m;i++){
        a[i] = rand() % N;
        b[i] = rand() % N;
        while((flag[a[i]][b[i]] == 1)||(a[i] == b[i])){
            a[i] = rand() % N;
            b[i] = rand() % N;
        }
        flag[a[i]][b[i]] = 1;
        fprintf(fp,"%d    %d\n",a[i],b[i]);
    }
    
    for(int i = 0;i < m;i++)    g.addEdge(a[i], b[i]);
    g.printSCCs();
    finish = clock();
    duration = (double)(finish- start)/CLOCKS_PER_SEC;
    time1 << "运行时间为:"<< duration<< "秒"<<endl;
    return 0;
}
