#include<stdio.h>

int list[7]={38, 27, 43, 3, 9, 82, 10};

void swap(int *a, int *b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void quickSort(int lst[], int s, int e)
{
    if(s>=e)
        return;

    int pivot=lst[s], l=s, r=e;
    while(l<r)
    {
        while(pivot < lst[r]) r--;
        while(l<r && pivot >= lst[l]) l++;
        swap(lst+l, lst+r);
    }
    swap(lst+s, lst+l);

    quickSort(lst, s, r-1), quickSort(lst, r+1, e);
}

int main(void)
{
    quickSort(list, 0, 6);
    for(int i=0; i<7; i++)
        printf("%d\t", list[i]);
    printf("\n");
}
