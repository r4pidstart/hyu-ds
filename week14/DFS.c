#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 10
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

typedef struct graph
{
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int n;
}graph;

void init(graph *s)
{
    s->n=0;
    for(int i=0; i<MAX_VERTICES; i++)
        for(int j=0; j<MAX_VERTICES; j++)
            s->adjMatrix[i][j]=0;
}

void insertVertex(graph *g)
{
    if(g->n == MAX_VERTICES)
    {
        printf("노드 삽입 불가\n");
        return;
    }
    g->n++;
}

void insertEdge(graph *g, int u, int v)
{
    if(u >= g->n || v >= g->n)
    {
        printf("정점 번호가 잘못됨\n");
        return;
    }
    g->adjMatrix[u][v]=1;
    g->adjMatrix[v][u]=1;
}

void dfs(graph *g, int v)
{
    visited[v]=TRUE;
    printf("%d -> ", v);
    for(int i=0; i<g->n; i++)
        if(g->adjMatrix[v][i] && !visited[i])
            dfs(g, i);
}

int main(void)
{
    graph g;

    init(&g);
    for(int i=0; i<MAX_VERTICES; i++)
        visited[i]=0;
    for(int i=0; i<7; i++)
        insertVertex(&g);
    
    insertEdge(&g, 0, 4);
    insertEdge(&g, 0, 6);
    insertEdge(&g, 1, 3);
    insertEdge(&g, 3, 5);
    insertEdge(&g, 4, 1);
    insertEdge(&g, 4, 2);
    insertEdge(&g, 6, 2);

    dfs(&g, 0);
}
