//
//  main.cpp
//  FFT
//
//  Created by 姜庆彩 on 2017/12/3.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <complex>
#include <math.h>
const double PI = acos(-1.0);
using namespace std;
int scale[4] = {4, 16, 32, 60};
double result_FFT[128];
double result_normal[128];
void creat_random_number()
{
    ofstream random_number("/Users/jqc/Documents/学习/算法基础/PB15051087_project_2/ex2/input/input.txt", ios_base::out);
    int i;
    float random;
    for (i=0; i<120; i++)
    {
        random = rand()*1.0/(RAND_MAX/256.) - 128; //creat random number between (-128,128)
        random_number << random << endl;
    }
}
void normal_solution(int scale)
{
    int i, j;
    float a[60],b[60];
    for(i=0; i<128; i++)
        result_normal[i] = 0;
    ifstream input("/Users/jqc/Documents/学习/算法基础/PB15051087_project_2/ex2/input/input.txt", ios_base::in);
    for(j=0; j<scale; j++)
    {
        input >> a[j];
    }
    for(j=0; j<scale; j++)
    {
        input >> b[j];
    }
    for(i=0; i<scale; i++)
    {
        for(j=0; j<scale; j++)
        {
            result_normal[i+j] += a[i] * b[j];
        }
    }
    input.close();
}
void recursive_FFT(complex<double> arr[], int scale, int type)//learned from Internet, type= -1 presents reverse_FFT
{
    int n, i;
    if (scale == 60)
        n = 64;
    else n = scale;
    if(n == 1) return;
    complex<double> wn(cos(type * 2 * PI / n), sin(type * 2 * PI / n)), w(1, 0);
    complex<double> a[n/2], b[n/2];
    for(i = 0; i < n; i += 2) {
        a[i/2] = arr[i];
    }
    for(i = 1; i < n; i += 2) {
        b[i/2] = arr[i];
    }
    recursive_FFT(a, n/2, type);
    recursive_FFT(b, n/2, type);
    for(int i = 0; i < n/2-1; i++) {
        arr[i] = a[i] + w * b[i];
        arr[i + n/2] = a[i] - w * b[i];
        w *= wn;
    }
}
void FFT_solution(int scale)
{
    int i;
    complex<double> a[128], b[128], c[128];
    ifstream input_FFT("/Users/jqc/Documents/学习/算法基础/PB15051087_project_2/ex2/input/input.txt", ios_base::in);
    for(i=0; i<scale; i++)
    {
        input_FFT >> a[i];
    }
    for(i=0; i<scale; i++)
    {
        input_FFT >> b[i];
    }
    recursive_FFT(a, 2*scale, 1);
    recursive_FFT(b, 2*scale, 1);
    for(i=0; i<2*scale; i++)
    {
        c[i] = a[i] * b[i];
    }
    recursive_FFT(c, 2*scale, -1);
    for(i=0; i<2*scale-1; i++)
    {
        result_FFT[i] = c[i].real()/(2*scale);
    }
    input_FFT.close();
}
int main()
{
    int i,j;
    clock_t start, finish;
    double  duration;
    ofstream output("/Users/jqc/Documents/学习/算法基础/PB15051087_project_2/ex2/output/result.txt", ios_base::out);
    ofstream output_time("/Users/jqc/Documents/学习/算法基础/PB15051087_project_2/ex2/output/time.txt", ios_base::out);
    srand((unsigned)time(NULL));
    creat_random_number();
    for(i=0; i<4; i++)
    {
        start = clock();
        normal_solution(scale[i]);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        output<< "the reslut of scale " << i << " in normal solution is: (";
        for(j=0; j<scale[i]; j++)
        {
            output << result_normal[j];
            if(j != scale[i]-1)
                output << ',';
        }
        output << ')' <<endl;
        output_time << "the cost of time in scale "<< i <<"is(normal_solution): " << duration <<" second"<< endl;
        output << endl;
    }
    for(i=0; i<4; i++)
    {
        start = clock();
        FFT_solution(scale[i]);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        output<< "the reslut of scale " << i << " in FFT solution is: (";
        for(j=0; j<scale[i]; j++)
        {
            output << result_FFT[j];
            if(j != scale[i]-1)
                output << ',';
        }
        output << ')' <<endl;
        output_time << "the cost of time in scale "<< i <<"is(FFT_Solution): " << duration <<" second"<<endl;
        output << endl;
    }
    return 0;
}
