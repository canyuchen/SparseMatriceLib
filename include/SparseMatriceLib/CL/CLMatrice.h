#ifndef CLMATRICE_H
#define CLMATRICE_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct OLNode{
    int row,col;
    float data;
    struct OLNode *right, *down;    //该非零元坐在行表和列表的后继链域
}OLNode, *OLink;

typedef struct{
    OLink *rhead, *chead;
    int mu, nu, tu;             //稀疏矩阵的行数、列数和非零元个数
}CrossList;

#define TRUE 1
#define FALSE 0

void CreatCLM(CrossList *T);
void PrintCLM(CrossList T);
CrossList AddCLM(CrossList A, CrossList B);
CrossList SubCLM(CrossList A, CrossList B);
CrossList MulCLM(CrossList A, CrossList B);
CrossList CopyCLM(CrossList A);
float DetCLM(CrossList A);
float GetCofactor(CrossList A,int a, int b);
CrossList InvCLM(CrossList A);


#endif //CLMATRICE_H
