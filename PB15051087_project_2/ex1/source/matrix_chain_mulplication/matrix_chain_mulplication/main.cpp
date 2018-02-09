//
//  main.cpp
//  matrix_chain_mulplication
//
//  Created by 姜庆彩 on 2017/12/2.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;
int scale_of_matrix[4] = {5, 10, 20, 30};
int number_of_matrix[31];
int m[35][35],s[35][35];
ofstream result;
void creat_random_number()
{
    int i;
    for(i=0; i<30; i++)
    {
        number_of_matrix[i] = rand()%255+1;
    }
}
void matrix_chain_order(int p[], int scale)
{
    int n = scale-1, j, q;
    for(int i=1; i<scale;i++)
        m[i][i] = 0;
    for (int l=2; l<=n; l++)
    {
        for(int i=1; i<=n-l+1; i++)
        {
            j = i + l -1;
            m[i][j] = INT_MAX;
            for(int k=i; k<j; k++)
            {
                q = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                if(q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}
void print_optimal_parens(int s[][35], int i, int j)
{
    if(i == j)
{       cout << 'A' << i ;
        result << 'A' << i;
}
    else
    {
        cout << '(';
        result << '(';
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j]+1, j);
        cout << ')';
        result << ')';
    }
}
int main()
{
    int i;
    int data[31];
    srand((unsigned)time(NULL));
    ofstream out("/Users/jqc/Documents/学习/算法基础/project_2/matrix-chain_multiplication/input/input.txt", ios_base::out);
    ifstream in;
    ofstream result_time;
    clock_t start, finish;
    double  duration;
    result.open("/Users/jqc/Documents/学习/算法基础/project_2/matrix-chain_multiplication/output/result.txt", ios_base::out);
    result_time.open("/Users/jqc/Documents/学习/算法基础/project_2/matrix-chain_multiplication/output/time.txt", ios_base::out);
    creat_random_number();
    for(i=0; i<32; i++)
    {
        out << number_of_matrix[i]<< endl;
    }
    out.close();
    for(i=0; i<4; i++)
    {
        int j = scale_of_matrix[i] + 1;
        in.open("/Users/jqc/Documents/学习/算法基础/project_2/matrix-chain_multiplication/input/input.txt", ios_base::in);
        for(int k=0; k<j; k++)
            in >> data[k];
        start = clock();
        matrix_chain_order(data, j);
        for(int k=0; k<j; k++)
            cout << data[k] <<endl;
        result << "the order of sacle" << i << "is: ";
        print_optimal_parens(s, i, j-1);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        result_time << "the cost of sacle" << i << "is: " << duration << "second" << endl;
        cout << endl;
        result << endl;
    }
    result_time.close();
    result.close();
}

