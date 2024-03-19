#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void display(int G[MAX][MAX], int vertex)
{
    int i, j;
    for (i = 0;i < vertex;i++)
    {
        for (j = 0;j < vertex;j++)
            printf("%d ",G[i][j]);
        printf("\n");
    }
}

int minDist(int dist[], int visited[], int v)
{
    int min = 999, minIndex, i;
    for (i = 0;i < v;i++)
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    return minIndex;
}

void displayMST(int parent[], int G[MAX][MAX], int vertex)
{
    int i, j;
    printf("Edge \tWeight\n");
    for (i = 1;i < vertex;i++)
    {
        printf("%d - %d \t%d\n",parent[i],i,G[i][parent[i]]);
    }
}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0;i < n;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void Prims(int G[MAX][MAX], int vertex)
{
    int visited[MAX], dist[MAX], parent[MAX];
    int i, j, u;
    for (i = 0;i < vertex;i++)
    {
        visited[i] = 0;
        dist[i] = 999;
        parent[i] = -1;
    }
    printf("\n");
    printArray(visited, vertex);
    printArray(dist, vertex);
    printArray(parent, vertex);
    printf("\n");

    dist[0] = 0;
    for (i = 0;i < vertex-1;i++)
    {
        u = minDist(dist, visited, vertex);
        visited[u] = 1;
        for (j = 0;j < vertex;j++)
        {
            if (G[u][j] != 999 && visited[j] == 0 && G[u][j] < dist[j])
            {
                dist[j] = G[u][j];
                parent[j] = u;
            }
            printf("iteration: %d\n", i+1);
            printArray(visited, vertex);
            printArray(dist, vertex);
            printArray(parent, vertex);
            printf("\n");
        }
    }
    printf("\n");
    displayMST(parent, G, vertex);
}

int main()
{
    int G[MAX][MAX], vertex, e, i, j, u, v;
    printf("Enter number of vertices: ");
    scanf("%d",&vertex);
    for (i = 0;i < vertex;i++)
        for (j = 0;j < vertex;j++)
            G[i][j] = 0;
    printf("Enter the number of edges: ");
    scanf("%d",&e);
    for (i = 0;i < e;i++)
    {
        printf("Enter edge: ");
        scanf("%d",&u);
        scanf("%d",&v);
        printf("Enter weight: ");
        scanf("%d",&G[u][v]);
        G[v][u] = G[u][v];
    }
    display(G, vertex);
    Prims(G, vertex);
}