/*

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

int main()
{
    void CreatCLM(CrossList *T);
    void PrintCLM(CrossList T);
    CrossList AddCLM(CrossList A, CrossList B);
    CrossList SubCLM(CrossList A, CrossList B);
    CrossList MulCLM(CrossList A, CrossList B);
    CrossList CopyCLM(CrossList A);
    float DetCLM(CrossList A);
    float GetCofactor(CrossList A);
    CrossList InvCLM(CrossList A);

    CrossList M,N,T;

    CreatCLM(&M);
    CreatCLM(&N);

    //T = AddCLM(M,N);
    //T = SubCLM(M,N);
    T = MulCLM(M,N);
    //T = CopyCLM(M);

    //T = InvCLM(M);

    PrintCLM(T);

    //printf("%f", DetCLM(M));

    return 1;
}
*/

#include <SparseMatriceLib/CL/CLMatrice.h>

void CreatCLM(CrossList *T)     //创建十字链表
{
    int row,col,nonzero;
    int i,j;
    float data;
    int k;
    CrossList *M;
    M = T;

    if(M)
        free(M);

    printf("input\n");
    printf("请依次输入矩阵参数：行数，列数和非零元个数。例：3 3 3\n");
    scanf("%d %d %d",&row,&col,&nonzero);  //输入M的行数、列数和非零元的个数
    M->mu = row;
    M->nu = col;
    M->tu = nonzero;

    if(!(M->rhead = (OLink*)malloc((row+1)*sizeof(OLink))))
        return;     //overflow
    if(!(M->chead = (OLink*)malloc((col+1)*sizeof(OLink))))
        return;     //overflow

    for(k = 0; k<= M->mu; k++)
        M->rhead[k] = NULL;
    for(k = 0; k<= M->nu; k++)
        M->chead[k] = NULL;

    for(k = 1; k<= M->tu; k++)
    {
        printf("请输入第 %d 个非零元的信息\n",k);
        printf("请输入行号(正整数):\n");
        scanf("%d",&i);
        printf("请输入列号(正整数):\n");
        scanf("%d",&j);
        printf("请输入值:\n");
        scanf("%f",&data);

        OLNode *p,*q;
        p = (OLNode*)malloc(sizeof(OLNode));
        p->row = i;
        p->col = j;
        p->data = data;

        if(M->rhead[i] == NULL || M->rhead[i]->col > j){
            p->right = M->rhead[i];
            M->rhead[i] = p;
        }
        else{
            for(q = M->rhead[i]; (q->right) && q->right->col < j; q = q->right);
            p->right = q->right;
            q->right = p;
        }

        if(M->chead[j] == NULL || M->chead[j]->row > i){
            p->down = M->chead[j];
            M->chead[j] = p;
        }
        else{
            for(q = M->chead[j]; (q->down) && q->down->row < i; q = q->down);
            p->down = q->down;
            q->down = p;
        }

        //free(p);
        //free(q);
    }

    T = M;
}

CrossList InvCLM(CrossList M)
{
    CrossList N;
    float DetCLM(CrossList A);
    float GetCofactor(CrossList A, int a, int b);
    int i,j,k;
    float det,t;
    OLNode *q, *r;

    det = DetCLM(M);

    if(fabs(det) < 0.000001){
        printf("Error: inversion does not exit\n");
        return M;
    }

    N.mu = M.mu;
    N.nu = M.mu;

    if(!(N.rhead = (OLink*)malloc((N.mu+1)*sizeof(OLink)))){
        printf("Error: overflow\n");
        return M;     //overflow
    }
    if(!(N.chead = (OLink*)malloc((N.nu+1)*sizeof(OLink)))){
        printf("Error: overflow\n");
        return M;     //overflow
    }

    for(k = 0; k<= N.mu; k++)
        N.rhead[k] = NULL;
    for(k = 0; k<= N.nu; k++)
        N.chead[k] = NULL;

    printf("done15\n");

    for(i = 1; i <= M.mu; i++)
    {
        for(j = 1; j <= M.nu; j++)
        {
            if(fabs(t = GetCofactor(M, j, i)) < 0.000001){
                printf("t = %f\n",t);
                continue;
            }

            q = (OLNode*)malloc(sizeof(OLNode));
            q->row = i;
            q->col = j;
            q->data = t / det;

            printf("row;%d,col:%d,data;%f\n",i,j,t/det);

            if(N.rhead[q->row] == NULL || N.rhead[q->row]->col > q->col){
                q->right = N.rhead[q->row];
                N.rhead[q->row] = q;
            }
            else{
                for(r = N.rhead[q->row]; (r->right) && r->right->col < q->col; r = r->right);
                q->right = r->right;
                r->right = q;
            }

            if(N.chead[q->col] == NULL || N.chead[q->col]->row > q->row){
                q->down = N.chead[q->col];
                N.chead[q->col] = q;
            }
            else{
                for(r = N.chead[q->col]; (r->down) && r->down->row < q->row; r = r->down);
                q->down = r->down;
                r->down = q;
            }

        }

    }

    return N;
}


float GetCofactor(CrossList M, int row, int col)
{
    CrossList T,N;
    CrossList CopyCLM(CrossList A);
    void PrintCLM(CrossList A);
    float DetCLM(CrossList A);
    OLNode *p, *q, *r, *pre;
    int i,j;
    float ans;


    T = CopyCLM(M);

    N.nu = T.nu - 1;
    N.mu = T.mu - 1;

    if(!(N.rhead = (OLink*)malloc((N.mu+1)*sizeof(OLink)))){
        printf("Error: overflow");
        return -1;     //overflow
    }
    if(!(N.chead = (OLink*)malloc((N.nu+1)*sizeof(OLink)))){
        printf("Error: overflow");
        return -1;
    }

    //构建代数余子式
    for(j = 1; j < col; j++)
    {
        if(T.chead[j] != NULL && T.chead[j]->row <= row){
            pre = q = T.chead[j];
            //printf("q->row:%d,p->row:%d,q->data:%d\n",q->row,p->row,q->data);
            if(q->row == row){
                T.chead[j] = q->down;
            }
            else
            {
                //printf("done14\n");
                while((q->down != NULL) && (q->row <= row))
                {
                    //printf("done15\n");
                    q = q->down;
                    if(q->row == row){
                        //printf("pre->data:%d,q->data:%d\n",pre->data,q->data);
                        pre->down = q->down;
                        break;
                    }
                    pre = pre->down;
                }
            }
        }

        N.chead[j] = T.chead[j];
    }
    printf("done6\n");

    for(j = col + 1; j <= T.nu; j++)
    {
        printf("T.chead[%d]:%d,data:%f,row:%d\n",j,T.chead[j]->row,T.chead[j]->data,row);
        if(T.chead[j] != NULL && T.chead[j]->row <= row){
            printf("done16\n");
            pre = q = T.chead[j];
            //printf("q->row:%d,p->row:%d,q->data:%d\n",q->row,p->row,q->data);
            if(q->row == row){
                T.chead[j] = q->down;
            }
            else
            {
                //printf("done14\n");
                while((q->down != NULL) && (q->row <= row))
                {
                    //printf("done15\n");
                    q = q->down;
                    if(q->row == row){
                        //printf("pre->data:%d,q->data:%d\n",pre->data,q->data);
                        pre->down = q->down;
                        break;
                    }
                    pre = pre->down;
                }
            }
        }

        N.chead[j-1] = T.chead[j];
    }


    //printf("N.chead[1]->data:%d\n",N.chead[1]->data);

    printf("done7\n");

    for(i = 1; i < row; i++)
    {
        if(T.rhead[i] != NULL && T.rhead[i]->col <= col){
            pre = q = T.rhead[i];
            //printf("q->row:%d,p->row:%d,q->data:%d\n",q->row,p->row,q->data);
            if(q->col == col){
                T.rhead[i] = q->right;
            }
            else
            {
                //printf("done14\n");
                while((q->right != NULL) && (q->col <= col))
                {
                    //printf("done15\n");
                    q = q->right;
                    if(q->col == col){
                        //printf("pre->data:%d,q->data:%d\n",pre->data,q->data);
                        pre->right = q->right;
                        break;
                    }
                    pre = pre->right;
                }
            }
        }

        N.rhead[i] = T.rhead[i];
    }

    printf("done8\n");
    //printf("%d %d",p->row,T.mu);


    for(i = row + 1; i <= T.mu; i++)
    {
        if(T.rhead[i] != NULL && T.rhead[i]->col <= col){
            pre = q = T.rhead[i];
            //printf("q->row:%d,p->row:%d,q->data:%d\n",q->row,p->row,q->data);
            if(q->col == col){
                T.rhead[i] = q->right;
            }
            else
            {
                //printf("done14\n");
                while((q->right != NULL) && (q->col <= col))
                {
                    //printf("done15\n");
                    q = q->right;
                    if(q->col == col){
                        //printf("pre->data:%d,q->data:%d\n",pre->data,q->data);
                        pre->right = q->right;
                        break;
                    }
                    pre = pre->right;
                }
            }
        }

        N.rhead[i-1] = T.rhead[i];

    }

    for(j = col + 1; j <= T.nu; j++)
    {
        for(r = N.chead[j-1]; r != NULL; r = r->down)
        {
            printf("done11\n");
            printf("r->col:%d,r->row:%d\n",r->col,r->row);
            r->col -= 1;
        }
    }

    for(i = row + 1; i <= T.mu; i++)
    {
        for(r = N.rhead[i-1]; r != NULL; r = r->right)
        {
            //printf("done11\n");
            //printf("r->col:%d,r->row:%d\n",r->col,r->row);
            r->row -= 1;
        }
    }


    printf("done11\n");
    PrintCLM(N);

    if((row+col)%2 == 1)
        ans = (-1)*DetCLM(N);
    else
        ans = DetCLM(N);

    return ans;
}


CrossList CopyCLM(CrossList M)      //重新开辟一个空间，并使其与所复制的十字链表相同
{
    OLNode *p,*q,*r;
    CrossList N;
    int i,k;

    N.mu = M.mu;
    N.nu = M.mu;
    N.tu = N.tu;

    if(!(N.rhead = (OLink*)malloc((N.mu+1)*sizeof(OLink)))){
        printf("Error: overflow\n");
        return M;     //overflow
    }
    if(!(N.chead = (OLink*)malloc((N.nu+1)*sizeof(OLink)))){
        printf("Error: overflow\n");
        return M;     //overflow
    }

    for(k = 0; k<= N.mu; k++)
        N.rhead[k] = NULL;
    for(k = 0; k<= N.nu; k++)
        N.chead[k] = NULL;

    for(i = 1; i <= M.nu; i++)
    {
        p = M.chead[i];
        while(p != NULL)
        {
            //p->data = -(p->data);
            q = (OLNode*)malloc(sizeof(OLNode));
            q->row = p->row;
            q->col = p->col;
            q->data = p->data;

            if(N.rhead[q->row] == NULL || N.rhead[q->row]->col > q->col){
                q->right = N.rhead[q->row];
                N.rhead[q->row] = q;
            }
            else{
                for(r = N.rhead[q->row]; (r->right) && r->right->col < q->col; r = r->right);
                q->right = r->right;
                r->right = q;
            }

            if(N.chead[q->col] == NULL || N.chead[q->col]->row > q->row){
                q->down = N.chead[q->col];
                N.chead[q->col] = q;
            }
            else{
                for(r = N.chead[q->col]; (r->down) && r->down->row < q->row; r = r->down);
                q->down = r->down;
                r->down = q;
            }

            p = p->down;
        }
    }

    return N;
}

float DetCLM(CrossList M)       //计算行列式
{
    CrossList CopyCLM(CrossList A);
    float ans = 0;
    OLNode *p, *q, *r, *pre;
    CrossList N,T;
    int i,j;

    if(M.nu != M.mu)
    {
        printf("Error: wrong form");
        return -1;
    }

    if(M.nu == 1){
        if(M.chead[1]==NULL)
            return 0;
        else{
            //printf("M.chead[1]->data:%d\n",M.chead[1]->data);
            return M.chead[1]->data;
        }
    }
    else{
        p = M.chead[1];

        while(p != NULL)
        {
            T = CopyCLM(M);

            N.nu = T.nu - 1;
            N.mu = T.mu - 1;

            if(!(N.rhead = (OLink*)malloc((N.mu+1)*sizeof(OLink)))){
                printf("Error: overflow");
                return -1;     //overflow
            }
            if(!(N.chead = (OLink*)malloc((N.nu+1)*sizeof(OLink)))){
                printf("Error: overflow");
                return -1;
            }

            //printf("done5\n");
            //构建代数余子式
            for(j = 2; j <= T.nu; j++)
            {
                if(T.chead[j] != NULL && T.chead[j]->row <= p->row){
                    pre = q = T.chead[j];
                    //printf("q->row:%d,p->row:%d,q->data:%d\n",q->row,p->row,q->data);
                    if(q->row == p->row){
                        T.chead[j] = q->down;
                    }
                    else
                    {
                        //printf("done14\n");
                        while((q->down != NULL) && (q->row <= p->row))
                        {
                            //printf("done15\n");
                            q = q->down;
                            if(q->row == p->row){
                                //printf("pre->data:%d,q->data:%d\n",pre->data,q->data);
                                pre->down = q->down;
                                break;
                            }
                            pre = pre->down;
                        }
                    }
                }
            }

            //printf("done6\n");

            for(j = 2; j <= T.nu; j++)
            {
                N.chead[j-1] = T.chead[j];
            }

            //printf("N.chead[1]->data:%d\n",N.chead[1]->data);

            //printf("done7\n");

            for(i = 1; i < p->row; i++)
            {
                if(T.rhead[i] != NULL){
                    if(T.rhead[i]->col == 1){
                        N.rhead[i] = T.rhead[i]->right;
                    }
                    else{
                        N.rhead[i] = T.rhead[i];
                    }
                    for(r = N.rhead[i]; r != NULL; r = r->right)
                    {
                        //printf("r->col:%d,r->row:%d\n",r->col,r->row);
                        r->col -= 1;
                    }
                }
                else{
                    N.rhead[i] = NULL;
                }
            }

            //printf("done8\n");
            //printf("%d %d",p->row,T.mu);

            for(i = p->row + 1; i <= T.mu; i++)
            {
                //printf("done10\n");
                if(T.rhead[i] != NULL){
                    //printf("done13,i=%d,col=%d\n",i,T.rhead[i]->col);
                    if(T.rhead[i]->col == 1){
                        N.rhead[i-1] = T.rhead[i]->right;
                        //printf("done12\n");
                    }
                    else{
                        N.rhead[i-1] = T.rhead[i];
                    }
                    for(r = N.rhead[i-1]; r != NULL; r = r->right)
                    {
                        //printf("done11\n");
                        //printf("r->col:%d,r->row:%d\n",r->col,r->row);
                        r->col -= 1;
                        r->row -= 1;
                    }
                }
                else{
                    N.rhead[i-1] = NULL;
                }
            }

            //printf("done9\n");

            //printf("p->data:%d\n",p->data);

            if((p->row)%2 == 1){
                //printf("ans:%d\n",ans);
                ans += (p->data)*DetCLM(N);
                //printf("Det(N):%d, p->data:%d,ans:%d\n",DetCLM(N),p->data,ans);
            }
            else{
                //printf("ans:%d\n",ans);
                ans -= (p->data)*DetCLM(N);
                //printf("Det(N):%d, p->data:%d,ans:%d\n",DetCLM(N),p->data,ans);
            }

            p = p->down;
        }
    }//else

    return ans;
}

CrossList MulCLM(CrossList A, CrossList B)   //A * B
{
    int i,j;
    CrossList M;
    //int a[400][400];
    float temp = 0;
    OLNode *p,*q,*r,*s;

    if(A.nu != B.mu){
        printf("Error: not match");
        return A;
    }

    M.mu = A.mu;
    M.nu = B.nu;

    if(!(M.rhead = (OLink*)malloc((M.mu+1)*sizeof(OLink)))){
        printf("Error: overflow");
        return A;     //overflow
    }
    if(!(M.chead = (OLink*)malloc((M.nu+1)*sizeof(OLink)))){
        printf("Error: overflow");
        return A;
    }

    for(i = 1; i <= A.mu; i++)
    {
        for(j = 1; j <= B.nu; j++)
        {
            r = A.rhead[i];
            s = B.chead[j];
            while(r && s)
            {
                if(r->col == s->row){
                    temp += r->data * s->data;
                    r = r->right;
                    s = s->down;
                }
                else if(r->col > s->row){
                    s = s->down;
                }
                else if(r->col < s->row){
                    r = r->right;
                }
            }
            if(fabs(temp) > 0.000001){          //float ?
                p = (OLNode*)malloc(sizeof(OLNode));
                p->row = i;
                p->col = j;
                p->data = temp;

                if(M.rhead[i] == NULL || M.rhead[i]->col > j){
                    p->right = M.rhead[i];
                    M.rhead[i] = p;
                }
                else{
                    for(q = M.rhead[i]; (q->right) && q->right->col < j; q = q->right);
                    p->right = q->right;
                    q->right = p;
                }

                if(M.chead[j] == NULL || M.chead[j]->row > i){
                    p->down = M.chead[j];
                    M.chead[j] = p;
                }
                else{
                    for(q = M.chead[j]; (q->down) && q->down->row < i; q = q->down);
                    p->down = q->down;
                    q->down = p;
                }
            }//if

            temp  = 0;
        }//for2
    }//for1

    return M;
}

CrossList SubCLM(CrossList A, CrossList B)   //A - B
{
    CrossList AddCLM(CrossList M, CrossList N);  //调用加法
    int i;
    OLNode *p;
    CrossList T;

    printf("done3\n");

    for(i = 1; i <= B.nu; i++)
    {
        p = B.chead[i];
        while(p != NULL)
        {
            p->data = -(p->data);
            p = p->down;
        }
    }

    printf("done4\n");

    T = AddCLM(A,B);

    return T;
}

CrossList AddCLM(CrossList A,CrossList B)       //A + B
{
    OLNode *pre;
    OLNode *pa;
    OLNode *pb;
    OLNode *p;
    OLink *hl;
    int j;

    //pa = A.rhead[1];
    //pb = B.rhead[1];
    //pre = NULL;

    hl = (OLink*)malloc((A.nu+1)*sizeof(OLink));

    if((A.nu != B.nu)||(A.mu != B.mu)){
        printf("Error: not match");
        return A;
    }

    printf("done1\n");

    for(j = 1; j <= A.nu; ++j)
    {
        hl[j] = A.chead[j];
    }

    printf("done2\n");
    for(j = 1; j <= A.mu; ++j)
    {
        pa = A.rhead[j];
        pb = B.rhead[j];
        pre = NULL;

        while(pb != NULL)
        {
            if(pa == NULL || pa->col > pb->col){
                p = pb;
                if(pre == NULL)
                    A.rhead[p->row] = p;
                else
                    pre->right = p;
                p->right = pa;
                pre = p;

                if(!A.chead[p->col]||A.chead[p->col]->row > p->row){
                    p->down = A.chead[p->col];
                    A.chead[p->col] = p;
                }
                else{
                    p->down = hl[p->col]->down;
                    hl[p->col]->down = p;
                }
                hl[p->col] = p;
                pb = pb->right;
            }
            else if(pa != NULL && pa->col < pb->col){
                pre = pa;
                pa = pa->right;
            }
            else if(pa->col == pb->col){
                pa->data += pb->data;

                if(pa->data < 0.000001 && pa->data >0.000001){      //float
                    if(pre == NULL)
                        A.rhead[pa->row] = pa->right;
                    else
                        pre->right = pa->right;
                    p = pa;
                    pa = pa->right;
                    pb = pb->right;

                    if(A.chead[p->col] == p)
                        A.chead[p->row] = hl[p->col] = p->down;
                    else
                        hl[p->col]->down = p->down;
                    free(p);
                }
                else{
                    pa = pa->right;
                    pb = pb->right;
                }//else
            }//else if
        }//while
    }//for

    return A;
}

void PrintCLM(CrossList T)
{
    int i,j;
    OLNode *p;
    system("cls");
    printf("运算结果\n");
    //printf("行数:%d,列数:%d,非零元:%d\n",T.mu,T.nu,T.tu);
    for(i = 1; i <= T.mu; i++){
        p = T.rhead[i];
        for(j = 1; j <= T.nu; j++){
            if(p && p->col == j){
                printf("%6.3f\t",p->data);
                p = p->right;
            }
            else
                printf("%6.3f\t",0.0);
        }
        printf("\n");
    }
}

