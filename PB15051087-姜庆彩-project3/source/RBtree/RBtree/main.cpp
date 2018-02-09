//
//  main.cpp
//  RBtree
//
//  Created by 姜庆彩 on 2017/12/11.
//  Copyright © 2017年 姜庆彩. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#define N 60
using namespace std;
typedef enum COLOR{
    RED,
    BLACK
}COLOR;
typedef struct RBTreeNode{
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    struct RBTreeNode *parent;
    COLOR color;
    int key;
    int size;
}Node,*RBTree;
Node *nil = NULL;
void preorder_RBtree(RBTree *T, ofstream out);
void gen_rand_num(){
    int i, j;
    int input[N] = {0};
    ofstream out("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/input/input.txt", ios_base::out);
    for(i = 0;i < N;)
    {
        input[i] = rand()%256 + 1;
        for(j = 0;j < i;j++)
            if(input[j] == input[i]) break; //重复
        if(j == i) i++; //也就是没有重复项
    }
    for(i = 0;i < N;i++)
        out << input[i] << endl;
    out.close();
}
void read_num(int arr[], int scale){
    int i;
    ifstream in("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/input/input.txt", ios_base::in);
    for(i=0; i<scale; i++)
        in >> arr[i];
    in.close();
}
void LeftRotate(RBTree *T, Node *x){
    if( x-> right != nil )
    {
        Node *y = x->right;
        x->right = y->left;
        if(y->left != nil)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        
        if( x->parent == nil )
        {
            *T=y;
        }
        else
        {
            if( x == x->parent->left )
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = y;
            }
        }
        y->left = x;
        x->parent = y;
        y->size = x->size;
        x->size = x->left->size + x->right->size + 1;
    }
}
void RightRotate(RBTree *T, Node *x)
{
    if( x->left != nil )
    {
        Node *y = x->left;
        x->left = y->right;
        if( y->right != nil )
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if( x->parent == nil )
        {
            *T = y;
        }
        else
        {
            if(x == x->parent->left )
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = y;
            }
        }
        y->right = x;
        x->parent = y;
        y->size = x->size;
        x->size = x->left->size + x->right->size + 1;
    }
}

void InsertFixup(RBTree *T,Node *z){
    Node *y;
    while(z->parent->color == RED)
    {
        if(z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if(y->color == RED)
            {             //case 1
                y->color  = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else
            {
                if(z==z->parent->right)
                {   //case 2
                    z = z->parent;
                    LeftRotate(T,z);
                }
                z->parent->color = BLACK;   //case 3
                z->parent->parent->color = RED;
                RightRotate(T,z->parent->parent);
            }
        }else
        {  //same
            y = z->parent->parent->left;
            if(y->color == RED)
            {
                y->color  = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else
            {
                if(z == z->parent->left)
                {
                    z = z ->parent;
                    RightRotate(T,z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(T,z->parent->parent);
            }
        }
    }
    (*T)->color = BLACK;
}

void rbInsert(RBTree *T,int key){//插入节点函数
    if( (*T) == NULL){ //这里相较于课本多了一个根结点为空的情况
        *T = (Node*)malloc(sizeof(Node));
        //初始化nil结点
        nil = (Node*)malloc(sizeof(Node));
        nil->color = BLACK;
        nil->size  = 0;
        nil->left = NULL;
        nil->right = NULL;
        nil->parent = NULL;
        //设置结点的指向
        (*T)->parent = nil;
        (*T)->left   = nil;
        (*T)->right  = nil;
        //设置结点属性,key 和color
        (*T)->key  = key;
        (*T)->color  = BLACK;
    }else{
        Node *y = nil;
        Node *x = *T;
        while(x != nil){
            y = x;
            if(key > x->key)
                x = x->right;
            else if(key < x->key)
                x = x->left;
            else
                return ;
        }
        Node *z = (Node*)malloc(sizeof(Node));
        z->parent = y ;
        z->left   = nil;
        z->right  = nil;
        
        z->key  = key;
        z->color  = RED;
        if(key < y->key){
            y->left = z;
        }else{
            y->right = z;
        }
        InsertFixup(T,z);
    }
}
/*删除调整*/
void DeleteFixup(RBTree *T,Node *x){
    while(x != (*T) && x->color == BLACK){
        if(x == x->parent->left){
            Node *w = x->parent->right;  //w 为x的兄弟结点
            if(w->color == RED){          //case 1 兄弟结点为红色
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(T,x->parent);
                w = x->parent->right;
            }
            if(w==nil) break;
            if(w->left->color ==BLACK && w->right->color==BLACK ){   //case2 兄弟结点的两个子结点都为黑
                w->color = RED;
                x = x->parent;
            }else if(w->right->color == BLACK){    //case3 w的左子树为红色,右子树为黑色
                w->color = RED;
                w->left->color = BLACK;
                RightRotate(T,w);
                w = x->parent->right;
            }
            w->color = x->parent->color;         //case 4 w的右子树为红色
            x->parent->color = BLACK;
            w->right->color = BLACK;
            LeftRotate(T,x->parent);
        }else{  //对称 调整同上
            Node *w = x->parent->left;
            if(w->color == RED){                 //case 1
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(T,x->parent);
                w = x->parent->left;
            }
            if(w == nil) break;
            if(w->left->color == BLACK && w->right->color == BLACK ){  //case 2
                w->color = RED;
                x = x->parent;
            }else if(w->left->color == BLACK){                       //case 3
                w->color = RED;
                w->right->color = BLACK;
                LeftRotate(T,w);
                w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            RightRotate(T,x->parent);
        }
        x = *T;
    }
    x->color = BLACK;
}
Node *TREE_SUCCESSOR(RBTree *T,Node *x){
    Node *p = x->right;
    while( p->left != nil ){
        p = p->left;
    }
    return p;
}


void rbDelete(RBTree *T,Node *z){//删除结点
    if(z==nil || z==NULL)
        return ;
    Node *y;
    Node *x;
    if(z->left==nil || z->right ==nil){
        y = z;
    }else{
        y = TREE_SUCCESSOR(T,z);
    }
    //x指向实际删除结点的子结点
    if(y->left != nil)
        x = y->left ;
    else
        x = y->right;
    
    x->parent = y->parent;   //删除结点y
    if(y->parent == nil){
        *T = x;
    }else{
        if(y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if(y != z){
        z->key = y->key;
    }
    //如果删除的结点是黑色,违法了性质5,要进行删除调整
    if(y->color == BLACK){
        DeleteFixup(T,x);
    }
}

void preorder_RBtree(RBTree T, ofstream &out){
    if(T != nil){
        out << T->key<<endl;
        preorder_RBtree(T -> left, out);
        preorder_RBtree(T -> right, out);
    }
}
void inorder_RBtree(RBTree T, ofstream &out){
    if(T != nil){
        inorder_RBtree(T -> left, out);
        out << T->key<<endl;
        inorder_RBtree(T -> right, out);
    }
}
void postorder_RBtree(RBTree T, ofstream &out){
    if(T != nil){
        postorder_RBtree(T -> left, out);
        postorder_RBtree(T -> right, out);
        out << T->key<<endl;
    }
}
void show_information(RBTree T){//前序遍历输出各结点信息
    if(T != nil){
        cout << T->key << ' ' << T->color << ' ' << T->parent << ' ' << T->left << ' ' << T->right <<endl;
        show_information(T -> left);
        show_information(T -> right);
    }
}
Node *os_select(Node *x,int i)
{
    int r = x->left->size + 1;
    if(i == r)
        return x;
    else if(i < r)
        return os_select(x->left,i);
    else
        return os_select(x->right,i-r);
}
void SizeAdjust(Node *node)
{
    if(node != nil)
    {
        SizeAdjust(node->left);
        SizeAdjust(node->right);
        node->size = node->left->size + node->right->size + 1;
    }
}
int patition(int arr[], int p, int r){
    int x = arr[r];
    int i = p-1;
    int temp;
    for(int j = p; j< r; j++){
        if(arr[j] <= x){
            i = i+1;
            temp = *(arr+i);
            *(arr+i) = *(arr+r);
            *(arr+r) = temp;
        }
    }
    temp = *(arr+i+1);
    *(arr+i+1) = *(arr+r);
    *(arr+r) = temp;
    return i+1;
}
int randomized_patition(int arr[], int p, int r){
    int i;
    i = rand() % (r-p) + p;
    int temp;
    temp = *(arr+i);
    *(arr+i) = *(arr+r);
    *(arr+r) = temp;
    return patition(arr, p, r);
}
int randomized_select(int arr[], int p, int r, int i){
    if(p == r)
        return arr[p];
    int q =randomized_patition(arr, p, r);
    int k = q-p+1;
    if(i==k)
        return arr[q];
    else if(i < k)
        return randomized_select(arr, p, q-1, i);
    else return randomized_select(arr, q+1, r, i-k);
}
void test(int scale){
    int i, j;
    int arr[scale];
    read_num(arr, scale);
    clock_t start[8], finish[8];
    double duration[8];
    double total= 0.0;
    RBTree T = NULL;
    for(i = 0;i < scale/10; i++)
    {
        start[i] = clock();
        for(j = 10*i;j < 10*i + 10;j++)//每插入10个节点测试一下花费的时间
        {
            rbInsert(&T,arr[j]);//插入节点
        }
        finish[i] = clock();
        duration[i] = (double)(finish[i] - start[i]) / CLOCKS_PER_SEC;
        total += duration[i];
    }
    ofstream out;
    switch(scale){
        case 12:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size12/time1.txt");
            break;
        }
        case 24:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size24/time1.txt");
            break;
        }
        case 36:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size36/time1.txt");
            break;
        }
        case 48:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size48/time1.txt");
            break;
        }
        case 60:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size60/time1.txt");
            break;
        }
    }
    for(i = 0;i < scale/10;i++)
    {
        out << "插入第" << 10*i+1 << "个结点到第" << 10*i+10<< "个结点共花费" << duration[i]<< "秒"<< endl;
        
    }
    out<< "插入操作一共耗费"<< total<< "秒"<<endl;
    out.close();
    switch(scale){
        case 12:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size12/preorder.txt");
            break;
        }
        case 24:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size24/preorder.txt");
            break;
        }
        case 36:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size36/preorder.txt");
            break;
        }
        case 48:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size48/preorder.txt");
            break;
        }
        case 60:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size60/preorder.txt");
            break;
        }
    }
    preorder_RBtree(T, out);
    out.close();
    switch(scale){
        case 12:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size12/inorder.txt");
            break;
        }
        case 24:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size24/inorder.txt");
            break;
        }
        case 36:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size36/inorder.txt");
            break;
        }
        case 48:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size48/inorder.txt");
            break;
        }
        case 60:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size60/inorder.txt");
            break;
        }
    }
    inorder_RBtree(T, out);
    out.close();
    switch(scale){
        case 12:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size12/postorder.txt");
            break;
        }
        case 24:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size24/postorder.txt");
            break;
        }
        case 36:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size36/postorder.txt");
            break;
        }
        case 48:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size48/postorder.txt");
            break;
        }
        case 60:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size60/postorder.txt");
            break;
        }
    }
    postorder_RBtree(T, out);
    out.close();
    SizeAdjust(T);
    Node *d1 = os_select(T, scale/3);
    Node *d2 = os_select(T, scale/4);
    switch(scale){
        case 12:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size12/delete_data.txt");
            break;
        }
        case 24:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size24/delete_data.txt");
            break;
        }
        case 36:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size36/delete_data.txt");
            break;
        }
        case 48:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size48/delete_data.txt");
            break;
        }
        case 60:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size60/delete_data.txt");
            break;
        }
    }
    int r1= randomized_select(arr, 0, scale-1, scale/3);
    int r2= randomized_select(arr, 0, scale-1, scale/4);
    cout<< r1<< endl<< r2<<endl;
    out << "删除第n/3小的节点为"<< d1->key<< endl<< "删除第n/4小的节点为"<< d2->key<< endl;
    out.close();
    switch(scale){
        case 12:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size12/time2.txt");
            break;
        }
        case 24:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size24/time2.txt");
            break;
        }
        case 36:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size36/time2.txt");
            break;
        }
        case 48:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size48/time2.txt");
            break;
        }
        case 60:{
            out.open("/Users/jqc/Documents/学习/算法基础/PB15051087-姜庆彩-project3/output/size60/time2.txt");
            break;
        }
    }
    start[6] = clock();
    rbDelete(&T,d1);
    finish[6] =clock();
    duration[6] = (double)(finish[6] - start[6]) / CLOCKS_PER_SEC;
    start[7] = clock();
    rbDelete(&T,d1);
    finish[7] =clock();
    duration[7] = (double)(finish[7] - start[7]) / CLOCKS_PER_SEC;
    out<< "删除n/3小节点所需时间为"<< duration[6]<< "秒"<< endl<< "删除n/4小节点所需时间为"<< duration[7]<< "秒"<< endl;
    out.close();
    
}
int main() {
    srand((unsigned)time(NULL));
    test(12);
    test(24);
    test(36);
    test(48);
    test(60);
}

