#include <stdio.h>
#include <limits.h>
#define vertices 5
#define MAX 100
int n;
int minimum_key(int k[], int visited[])
{
    int minimum = INT_MAX, min, i;
    for (i = 0; i < vertices; i++)
        if (visited[i] == 0 && k[i] < minimum)
            minimum = k[i], min = i;
    return min;
}
void prim(int g[vertices][vertices])
{
    int parent[vertices];
    int distance[vertices];
    int visited[vertices];
    int i, count, edge, v;
    for (i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }
    distance[0] = 0;
    parent[0] = -1;
    for (count = 0; count < vertices - 1; count++)
    {
        edge = minimum_key(distance, visited);
        visited[edge] = 1;
        for (v = 0; v < n; v++)
        {
            if (g[edge][v] && visited[v] == 0 && g[edge][v] < distance[v])
            {
                parent[v] = edge, distance[v] = g[edge][v];
            }
        }
    }
    printf("\n Edge \t  Weight\n");
    for (i = 1; i < n; i++)
        printf(" %d <-> %d    %d \n", parent[i], i, g[i][parent[i]]);
}
int main()
{

    int adj[vertices][vertices];
    int maxE, i, j, origin, destin, weight;
    printf("\nEnter number of vertices :: ");
    scanf("%d", &n);
    maxE = n * (n - 1) / 2;
    for (i = 0; i < maxE; i++)
    {
        printf("\nEnter edge [ %d ] and ( -1 -1 to quit ) : ", i);
        scanf("%d %d", &origin, &destin);
        if ((origin == -1) && (destin == -1))
            break;
        if (origin >= n || destin >= n || origin < 0 || destin < 0)
        {
            printf("\nInvalid vertex!\n");
            i--;
        }
        else
        {
            printf("Enter weight :");
            scanf("%d", &weight);
            adj[origin][destin] = weight;
            adj[destin][origin] = weight;
        }
    }
    prim(adj);
    return 0;
}