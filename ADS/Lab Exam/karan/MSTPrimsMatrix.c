#include <stdio.h>
#include <stdlib.h>
//#define MAX 100

int findMinDist(int dist[10], int visited[10], int v)
{
    int i, index, min = 999;

    for (i = 0;i < v;i++)
    {
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }

    return index;
}

void printMST(int parent[10], int G[10][10], int v)
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < v; i++)
    {
        printf("%d - %d \t%d \n", parent[i], i, G[i][parent[i]]);
    }
}

void Prims(int G[10][10], int v)
{
    int visited[10], dist[10], parent[10], i, j, u;

    for (i = 0;i < v;i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = 999;
    }

    dist[0] = 0;

    for (i = 0;i < v-1;i++)
    {
        u = findMinDist(dist, visited, v);
        visited[u] = 1;

        //printf("%d ",u);

        for (j = 0;j < v;j++)
        {
            if (G[u][j] != 999 && visited[j] == 0 && dist[j] > G[u][j])
            {
                dist[j] = G[u][j];
                parent[j] = u;
            }
        }
    }

   printMST(parent, G, v);
}

int main()
{
    int G[10][10], vertex, e, i, j, u, v, weight;

    printf("Enter number of vertices\n");
    scanf("%d",&vertex);

    for (i = 0;i < vertex;i++)
    {
        for (j = 0;j < vertex;j++)
        {
            G[i][j] = 999;
        }
    }

    printf("Enter the number of edges\n");
    scanf("%d",&e);

    for (i = 0;i < e;i++)
    {
        printf("Enter edge\n");
        scanf("%d",&u);
        scanf("%d",&v);

        printf("Enter weight\n");
        scanf("%d",&weight);

        G[u][v] = G[v][u] = weight;
    }

    for (int k = 0;k < vertex;k++)
    {
        for (int l = 0;l < vertex;l++)
        {
            printf("%d ",G[k][l]);
        }
        printf("\n");
    }

    Prims(G, vertex);
}
