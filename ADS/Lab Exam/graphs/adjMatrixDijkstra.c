//Write a Program to implement Dijkstra’s algorithm to find shortest distance between two nodes of a user defined graph. Use Adjacency Matrix to represent a graph
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void disp(int dist[MAX], int vertices)
{
    printf("Vertex\t Dist from source:\n");
    for (int i = 0; i < vertices; i++)
        printf("%d\t %d\n", i, dist[i]);
}

int minDist(int dist[MAX], int visited[MAX], int vertices)
{
    int min = 9999;
    int index;

    for (int i = 0; i < vertices; i++)
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    return index;
}

void Dijkstras(int graph[MAX][MAX], int source, int vertices)
{
    int dist[MAX], visited[MAX];
    int u;

    for (int i = 0; i < vertices; i++)
    {
        dist[i] = 9999;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (int i = 0; i < vertices - 1; i++)
    {
        u = minDist(dist, visited, vertices);
        visited[u] = 1;
        for (int i = 0; i < vertices; i++)
            if (visited[i] != 1 && graph[u][i] && dist[u] != 9999 && dist[u] + graph[u][i] < dist[i])
                dist[i] = dist[u] + graph[u][i];
    }

    disp(dist, vertices);
}

int main()
{
    int graph[MAX][MAX], numVertices, numEdges, i, j, u, v, weight, source;

    printf("Enter number of vertices: ");
    scanf("%d", &numVertices);
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            graph[i][j] = 999;

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);
    for (int i = 0; i < numEdges; i++)
    {
        printf("Enter edge: ");
        scanf("%d %d", &u, &v);

        printf("Enter weight: ");
        scanf("%d", &weight);

        graph[u][v] = graph[v][u] = weight;
    }

    for (int k = 0; k < numVertices; k++)
    {
        for (int l = 0; l < numVertices; l++)
            printf("%d \t", graph[k][l]);
        printf("\n");
    }

    printf("Enter starting vertex: ");
    scanf("%d", &source);

    Dijkstras(graph, source, numVertices);
}