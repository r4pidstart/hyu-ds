#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int list[7]={38, 27, 43, 3, 9, 82, 10};

void merge(int lst[], int s, int m, int e)
{
    int *tmp=(int *)malloc(sizeof(int) * (e-s+1));

    int a=s, b=m+1, cur=0;
    while(a <= m && b <= e)
    {
        if(lst[a] < lst[b])
            tmp[cur++]=lst[a++];
        else
            tmp[cur++]=lst[b++];
    }

    while(a <= m)
        tmp[cur++]=lst[a++];
    while(b <= e)
        tmp[cur++]=lst[b++];

    memcpy(lst+s, tmp, sizeof(int) * (e-s+1));
    free(tmp);
}

void mergeSort(int lst[], int s, int e)
{
    if(s==e)
        return;
    mergeSort(lst, s, (s+e)/2);
    mergeSort(lst, (s+e)/2+1, e);
    merge(lst, s, (s+e)/2, e);
}

int main(void)
{
    mergeSort(list, 0, 6);
    for(int i=0; i<7; i++)
        printf("%d\t", list[i]);
    printf("\n");
}
