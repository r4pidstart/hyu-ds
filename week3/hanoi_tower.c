#include<stdio.h>

int hanoi(int n, int target, char s, char e, char v)
{
    if(n==1)
    {
        printf("%d번 원판을 %c에서 %c로 이동\n", target, s, e);
        return 1;
    }
    else
    {
        int ret=0;
        ret+=hanoi(n-1, target, s, v, e);
        ret+=hanoi(1, target+n-1, s, e, v);
        ret+=hanoi(n-1, target, v, e, s);
        return ret;
    }
}

int main(void)
{
    printf("원판의 갯수를 입력하세요.\n");
    int a; scanf("%d", &a);

    printf("총 이동 횟수: %d\n", hanoi(a, 1, 'A', 'C', 'B'));
}
