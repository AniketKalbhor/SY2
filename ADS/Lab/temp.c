#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

int findParent(int i, int parent[MAX_VERTICES])
{
    while (i != parent[i])
    {
        i = parent[i];
    }
    return i;
}

void getUnion(int i, int j, int parent[MAX_VERTICES])
{
    int a = findParent(i, parent);
    int b = findParent(j, parent);

    parent[b] = a;
}

void Kruskals(int G[MAX_VERTICES][MAX_VERTICES], int numVertices)
{
    int minWeight = 0;
    int edges = 0;
    int parent[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++)
    {
        parent[i] = i;
    }

    while (edges < numVertices - 1)
    {
        int min = 999;
        int a = -1;
        int b = -1;

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (G[i][j] < min && findParent(i, parent) != findParent(j, parent))
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
            minWeight += min;
            edges++;
        }
    }

    printf("Weight of MST is %d\n", minWeight);
}

int main()
{
    int G[MAX_VERTICES][MAX_VERTICES];
    int numVertices, numEdges, u, v, weight;

    printf("Enter number of vertices: ");
    scanf("%d", &numVertices);

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            G[i][j] = 999;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++)
    {
        printf("Enter edge: ");
        scanf("%d %d", &u, &v);

        printf("Enter weight: ");
        scanf("%d", &weight);

        G[u][v] = G[v][u] = weight;
    }

    for (int k = 0; k < numVertices; k++)
    {
        for (int l = 0; l < numVertices; l++)
        {
            printf("%d ", G[k][l]);
        }
        printf("\n");
    }

    Kruskals(G, numVertices);

    return 0;
}