#include <stdio.h>
#include <stdlib.h>
int n;
struct node
{
    int vertex;
    int distance;
    struct node *next;
} A[10];
void adj_list(struct node *A[]);
void prims(struct node *A[]);
int Min(int dist[], int visited[]);
int printMST(int parent[]);
int main()
{
    n = 5;
    adj_list(A);
    prims(A);
    return 0;
}
void adj_list(struct node *A[])
{
    struct node *p, *new;
    int v1, v2, i = 1, wt;
    printf("total number of edges");
    scanf("%d", &n);
    do
    {
        printf("Enter Edge and weight\n");
        scanf("%d %d %d", &v1, &v2, &wt);
        new = (struct node *)malloc(sizeof(struct node));
        new->vertex = v2;
        new->distance = wt;
        new->next = NULL;
        p = A[v1];
        if (p == NULL)
        {
            A[v1] = new;
        }
        else
        {
            while (p->next != NULL)
                p = p->next;
            p->next = new;
        }
        new = (struct node *)malloc(sizeof(struct node));
        new->vertex = v1;
        new->distance = wt;
        new->next = NULL;
        p = A[v2];
        if (p == NULL)
        {
            A[v2] = new;
        }
        else
        {
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = new;
        }
        i++;
    } while (i <= n);
}
int Min(int dist[], int visited[])
{
    int index, min = 99;
    for (int i = 0; i < n; i++)
    {
        if (dist[i] < min && visited[i] == 0)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}
void prims(struct node *A[])
{
    int visited[10], dist[10], parent[10];
    int u, v, i, j;
    struct node *p;
    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = 99;
    }
    printf("enter the start vertex");
    scanf("%d", &v);
    dist[v] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        u = Min(dist, visited);
        visited[v] = 1;
        p = A[u];
        while (p != NULL)
        {
            if (p->distance < dist[p->vertex] && visited[p->vertex] == 0)
            {
                dist[p->vertex] = p->distance;
                parent[p->vertex] = u;
            }
            p = p->next;
        }
    }
    printMST(parent);
}
int printMST(int parent[])
{
    printf("\nEdge \n");
    for (int i = 1; i < n; i++)
    {
        printf("%d - %d \t \n", parent[i], i);
    }
}