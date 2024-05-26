#include <stdio.h>
#include <stdlib.h>

int findParent(int i, int parent[10])
{
    while (i != parent[i])
    {
        i = parent[i];
    }
    return i;
}

void getUnion(int i, int j, int parent[10])
{
    int a, b;

    a = findParent(i, parent);
    b = findParent(j, parent);

    parent[b] = a;
}

void Kruskals(int G[10][10], int v)
{
    int minWeight = 0;
    int edges = 0;
    int a, b;
    int parent[10];

    for(int i = 0;i < v;i++)
    {
        parent[i] = i;
    }

    while (edges < v-1)
    {
        int min = 999;
        a = -1;
        b = -1;

        for (int i = 0;i < v;i++)
        {
            for (int j = 0;j < v;j++)
            {
                if(G[i][j] < min && findParent(i, parent) != findParent(j, parent))
                {
                    a = i;
                    b = j;
                    min = G[i][j];
                }
            }
        }

        if (a != -1 && b != -1)
        {
            getUnion(a, b, parent);
            printf("%d edge: %d - %d = %d\n", edges, a, b, min);
            minWeight = minWeight + min;
            edges++;
        }
    }

    printf("Weight of MST is %d\n", minWeight);
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

    Kruskals(G, vertex);
}
