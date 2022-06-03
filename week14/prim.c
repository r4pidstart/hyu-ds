#include<stdio.h>
#include<stdlib.h>

#define INF 1000
#define MAX 7
#define TRUE 1
#define FALSE 0

int graph[MAX][MAX]=
{
    {0, 28, INF, INF, INF, 10, INF},
    {28, 0, 16, INF, INF, INF, 14},
    {INF, 16, 0, 12, INF, INF, INF},
    {INF, INF, 12, 0, 22, INF ,18},
    {INF, INF, INF, 22, 0, 25, 24},
    {10, INF, INF, INF, 25, 0, INF},
    {INF, 14, INF, 18, 24, INF, 0}
};

int selected[MAX], dist[MAX];

int getMinVertex(int n)
{
    int v;
    for(int i=0; i<n; i++)
        if(!selected[i])
        {
            v=i; break;
        }

    for(int i=0; i<n; i++)
        if(!selected[i] && dist[i] < dist[v])
            v=i;
    return v;
}

void prim(int s, int n)
{
    for(int i=0; i<n; i++)
        dist[i]=INF;
    
    dist[s]=0;
    for(int i=0; i<n; i ++)
    {
        int u=getMinVertex(n);
        selected[u]=TRUE;

        printf("%d -> ", u);
        for(int j=0; j<n; j++)
            if(graph[u][j] != INF)
                dist[j]=graph[u][j];
    }
}

int main(void)
{
    prim(0, MAX);
}
