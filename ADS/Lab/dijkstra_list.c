#include <stdio.h>
#include <stdlib.h>
#define MAX 10

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* a[MAX];

int minDist(int dist[MAX], int visited[MAX], int vertex) {
    int min = 9999;
    int index = -1;

    for (int i = 0; i < vertex; i++) {
        if (visited[i] == 0 && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }

    return index;
}

void disp(int dist[MAX], int vertex) {
    printf("Vertex\tDistance from source\n");
    for (int i = 0; i < vertex; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

void Dijkstras(int v, int source) {
    int dist[MAX], visited[MAX], u;
    for (int i = 0; i < v; i++) {
        dist[i] = 9999;
        visited[i] = 0;
    }
    dist[source] = 0;

    for (int i = 0; i < v - 1; i++) {
        u = minDist(dist, visited, v);
        if (u == -1)
            break;
        visited[u] = 1;

        struct Node* p = a[u];
        while (p != NULL) {
            int vert = p->vertex;
            int weight = p->weight;
            if (!visited[vert] && dist[u] + weight < dist[vert])
                dist[vert] = dist[u] + weight;
            p = p->next;
        }
    }

    disp(dist, v);
}

int main() {
    struct Node* p;
    struct Node* newV;
    int u, v, vertex,e, i;
    int weight, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertex);
    for (int i = 0; i < vertex; i++)
        a[i] = NULL;

    printf("Enter the number of edges: ");
    scanf("%d",&e);
    for (i = 0;i < e;i++)
    {
        printf("Enter edge: ");
        scanf("%d",&u);
        scanf("%d",&v);
        printf("Enter weight: ");
        scanf("%d",&weight);

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = v;
        newV->weight = weight;
        newV->next = NULL;
        p = a[u];

        if (p == NULL)
            a[u] = newV;
        else
        {
            while (p->next != NULL)
                p = p->next;
            p->next = newV;
        }

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = u;
        newV->weight = weight;
        newV->next = NULL;
        p = a[v];

        if (p == NULL)
            a[v] = newV;
        else
        {
            while (p->next != NULL)
                p = p->next;
            p->next = newV;
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    printf("Adjacency List\n");
    for (int i = 0; i < vertex; i++) {
        printf("Vertex %d -> ", i);
        p = a[i];
        while (p != NULL) {
            printf("%d, %d\t", p->vertex, p->weight);
            p = p->next;
        }
        printf("\n");
    }
    Dijkstras(vertex, source);
    return 0;
}