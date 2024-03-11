#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int stack[MAX];
int top = -1;

int emptyStack()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

void push(int n)
{
    if (top >= MAX-1)
        printf("Stack overflow\n");
    stack[++top] = n;
}

int pop()
{
    if (emptyStack())
    {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

void DFS(int G[10][10], int vertex)
{
    int visited[15], i, u, st;
    for (i = 0;i < vertex;i++)
        visited[i] = 0;
    printf("Enter start vertex\n");
    scanf("%d",&st);
    push(st);
    printf("%d ",st);
    visited[st] = 1;
    u = st;

    while (!emptyStack())
    {
        for (i = 0;i < vertex;i++)
            if (G[u][i] == 1 && visited[i] != 1)
            {
                push(i);
                visited[i] = 1;
                printf("%d ",i);
                u = i;
                break;
            }
        if (i == vertex)
        {
            pop();
            u = stack[top];
        }
    }
}

int main()
{
    int G[15][15], vertex, e, i, j, u, v;
    printf("Enter the number of vertices\n");
    scanf("%d",&vertex);
    for (i = 0;i < vertex;i++)
        for (j = 0;j < vertex;j++)
            G[i][j] = 0;
    printf("Enter the number of edges\n");
    scanf("%d",&e);
    for (i = 0;i < e;i++)
    {
        printf("Enter edge\n");
        scanf("%d",&u);
        scanf("%d",&v);
        G[u][v] = G[v][u] = 1;
    }
    DFS(G, vertex);
}