#include <stdio.h>
#include <stdlib.h>
//#define MAX 100

struct Node
{
    int vertex;
    int weight;
    struct Node* next;
};

struct Node* a[10];


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

void printMST(int parent[10], int v)
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < v; i++)
    {
        struct Node* p = a[i];
        while (p != NULL)
        {
            if (p->vertex == parent[i])
            {
                printf("%d - %d \t%d \n", parent[i], i, p->weight);
                break;
            }
            p = p->next;
        }
    }
}

void Prims(int v)
{
    int visited[10], dist[10], parent[10], u;

    for (int i = 0;i < v;i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = 999;
    }

    dist[0] = 0;

    for(int i = 0;i < v-1;i++)
    {
        u = findMinDist(dist, visited, v);
        visited[u] = 1;

        struct Node* p = a[u];
        while (p != NULL)
        {
            int vert = p->vertex;
            int weight = p->weight;

            if (!visited[vert] && weight < dist[vert])
            {
                parent[vert] = u;
                dist[vert] = weight;
            }
            p = p->next;
        }
    }

    printMST(parent, v);
}

int main()
{
    struct Node* p;
    struct Node* newV;
    int u, v, vnum, weight;
    char ch;

    printf("Enter the number of vertices\n");
    scanf("%d",&vnum);

    for (int i = 0;i < vnum;i++)
    {
        a[i] = NULL; // Corrected assignment operator
    }

    do {
        printf("Enter edge\n");
        scanf("%d",&u);
        scanf("%d",&v);

        printf("Enter weight\n");
        scanf("%d",&weight);

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = v;
        newV->weight = weight; // Fixed setting weight
        newV->next = NULL;

        p = a[u];

        if (p == NULL)
        {
            a[u] = newV;
        }
        else
        {
            while(p->next != NULL)
            {
                p = p->next;
            }
            p->next = newV;
        }

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = u;
        newV->weight = weight; // Fixed setting weight
        newV->next = NULL;

        p = a[v];

        if (p == NULL)
        {
            a[v] = newV;
        }
        else
        {
            while(p->next != NULL)
            {
                p = p->next;
            }

            p->next = newV;
        }

        printf("Add new edge?\n");
        scanf(" %c",&ch);
    }while(ch == 'y');

    printf("Adjacency List\n");

    for(int i = 0;i < vnum;i++)
    {
        printf("Vertex %d-> ",i);

        p = a[i];

        while (p != NULL)
        {
            printf("%d,%d\t",p->vertex, p->weight);
            p = p->next;
        }

        printf("\n");
    }

    Prims(vnum);

    return 0;
}
