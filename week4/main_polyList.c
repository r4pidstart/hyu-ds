#include<stdio.h>
#include<stdlib.h>

typedef struct poly
{
    int exp, coeff;
    struct poly *next;
}   poly;

void initPoly(poly *A)
{
    A->exp = -1; // mark this node as head <- ..?
    A->next = NULL;
}

void clearPoly(poly *A)
{
    poly *cur=A->next; // skip head
    while(cur)
    {
        poly *tmp=cur;
        cur=cur->next;
        free(tmp);
    }
    initPoly(A);
}

void printPoly_impl(poly A, char *buffer)
{
    poly *cur=A.next;
    while(cur)
    {
        if(A.next->exp != cur->exp && cur->coeff > 0) buffer+=sprintf(buffer, "+");
        buffer+=sprintf(buffer, "%dx^%d", cur->coeff, cur->exp);
        cur=cur->next;
    }
}

void printPoly(poly A)
{
    char buffer[1024]="";
    printPoly_impl(A, buffer);
    printf("%s", buffer);
}

void addTerm(poly *A, int exp, int coeff)
{
    poly *cur=A;

    while(cur->next && cur->next->exp > exp) // move to last node
        cur=cur->next;

    if(cur->next == NULL || cur->next->exp != exp)
    {
        poly *new=(poly *)malloc(sizeof(poly));
        new->exp=exp, new->coeff=coeff, new->next=cur->next;
        cur->next=new;
    }
    else
    {
        cur->next->coeff += coeff;
        if(cur->next->coeff == 0)
        {
            // delete next node
            poly *tmp=cur->next;
            cur->next=cur->next->next;
            free(tmp);
        }
    }
}

poly multiPoly(poly A, poly B)
{
    poly ret;
    initPoly(&ret);

    for(poly *curA=A.next; curA; curA=curA->next)
        for(poly *curB=B.next; curB; curB=curB->next)
            addTerm(&ret, curA->exp + curB->exp, curA->coeff * curB->coeff);
    return ret;
}

int main(void)
{
    poly A,B;

    initPoly(&A);
    initPoly(&B);

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
    printPoly(multiPoly(A,B));
    printf("\n");

    clearPoly(&A);
    clearPoly(&B);

    printPoly(A);
    printPoly(B);

    return 0;   
}
