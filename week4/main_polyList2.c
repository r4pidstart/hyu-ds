#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct poly
{
    int exp;
    int num;
    struct poly* next;
}   poly;

void clearPoly(poly** A)
{
    while(*A)
    {
        poly* tmp=(*A);
        (*A)=(*A)->next;
        free(tmp);
    }
    *A=0;
}

void printPoly_impl(poly* A, char* buffer)
{
    int first=1;
    while(A)
    {
        if(first) first=0;
        else if(A->num >= 0) buffer+=sprintf(buffer, "+");
        buffer+=sprintf(buffer, "%dx^%d", A->num, A->exp);
        A=A->next;
    }
}

void printPoly(poly* A)
{
    char buf[1024]="";
    printPoly_impl(A, buf);
    printf("%s", buf);
}

poly* make_node(int exp, int coeff, poly* next)
{
    poly *tmp=(poly*)malloc(sizeof(poly));
    if(!tmp) exit(-1);
    tmp->exp=exp, tmp->num=coeff, tmp->next=next;
    return tmp;
}

void addTerm(poly** A, int exp, int coeff)
{
    if(!*A)
        *A=make_node(exp, coeff, 0);
    else
    {
        // find last node, node->exp > exp
        if((*A)->exp < exp) // insert first node
            *A=make_node(exp, coeff, *A);
        else
        {
            poly* cur=*A, *prev=*A;
            while(cur->next && cur->next->exp > exp)
                prev=cur, cur=cur->next;
            
            if(cur->next && cur->next->exp == exp)
                cur->next->num+=coeff;
            else
                cur->next=make_node(exp, coeff, cur->next);
            
            if(cur->num == 0)
            {
                prev->next=cur->next;
                free(cur);
            }
        }
    }
}

poly* multiPoly(poly* A, poly* B)
{
    poly* cur1=A, *cur2=B, *ret=0;
    while(cur1)
    {
        cur2=B;
        while(cur2)
        {
            addTerm(&ret, cur1->exp+cur2->exp, cur1->num*cur2->num);
            cur2=cur2->next;
        }
        cur1=cur1->next;
    }
    return ret;
}

int main(void)
{
    poly* A=NULL, *B=NULL;

    addTerm(&A, 1, 1);
    addTerm(&A, 0, 1);
    printf("poly A: ");
    printPoly(A);
    printf("\n");

    addTerm(&B, 1, 1);
    addTerm(&B, 0, -1);

    printf("poly B: ");
    printPoly(B);
    printf("\n");

    printf("A*B: ");
    poly* ret=multiPoly(A,B);
    printPoly(ret);
    printf("\n");

    clearPoly(&A);
    clearPoly(&B);
    clearPoly(&ret);
    return 0;
}
