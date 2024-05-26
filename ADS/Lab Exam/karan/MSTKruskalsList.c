#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* a[10];
int parent[10]; // Declare parent array globally

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

void Kruskals(struct Node* a[10], int v)
{
    int min = 999;
    int edges = 0;
    int minWeight = 0;

    for (int i = 0; i < v; i++)
    {
        parent[i] = i;
    }

    while (edges < v - 1)
    {
        min = 999;
        int min_u = -1, min_v = -1; // variables to store vertices of the edge with minimum weight
        for (int i = 0; i < v; i++)
        {
            struct Node* p = a[i];
            while (p != NULL)
            {
                int u = i;
                int v = p->vertex;
                if (p->weight < min && findParent(u, parent) != findParent(v, parent))
                {
                    min = p->weight;
                    min_u = u;
                    min_v = v;
                }
                p = p->next;
            }
        }
        if (min_u != -1 && min_v != -1)
        {
            printf("Edge %d-%d Weight: %d\n", min_u, min_v, min);
            getUnion(min_u, min_v, parent);
            minWeight = minWeight + min;
            edges++;
        }
    }

    printf("Minimum weight of spanning tree: %d\n", minWeight);
}

int main()
{
    struct Node* p;
    struct Node* newV;
    int u, v, vnum, weight;
    char ch;

    printf("Enter the number of vertices\n");
    scanf("%d", &vnum);

    for (int i = 0; i < vnum; i++)
    {
        a[i] = NULL;
    }

    do {
        printf("Enter edge\n");
        scanf("%d", &u);
        scanf("%d", &v);

        printf("Enter weight\n");
        scanf("%d", &weight);

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = v;
        newV->weight = weight;
        newV->next = NULL;

        p = a[u];

        if (p == NULL)
        {
            a[u] = newV;
        }
        else
        {
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = newV;
        }

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = u;
        newV->weight = weight;
        newV->next = NULL;

        p = a[v];

        if (p == NULL)
        {
            a[v] = newV;
        }
        else
        {
            while (p->next != NULL)
            {
                p = p->next;
            }

            p->next = newV;
        }

        printf("Add new edge?\n");
        scanf(" %c", &ch);
    } while (ch == 'y');

    printf("Adjacency List\n");

    for (int i = 0; i < vnum; i++)
    {
        printf("Vertex %d-> ", i);

        p = a[i];

        while (p != NULL)
        {
            printf("%d,%d\t", p->vertex, p->weight);
            p = p->next;
        }

        printf("\n");
    }

    printf("Minimum Spanning Tree\n");
    Kruskals(a, vnum);

    return 0;
}
