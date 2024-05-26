#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct node
{
    int vertex;
    int distance;
    struct node *next;
};
int n, start, u, distance[10];
void adj_list(struct node *A[]);
int closevertex(int visited[]);
void dijkstras(struct node *A[]);
void display();
int main()
{
    struct node *A[10] = {NULL}; // Initialize the array of pointers
    adj_list(A);
    dijkstras(A);
    display();
    return 0;
}
void adj_list(struct node *A[])
{
    struct node *p, *new;
    int i, weight, v1, v2;
    printf("Enter the total number of vertices : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter Edge and weight: \n");
        scanf("%d%d%d", &v1, &v2, &weight);
        new = (struct node *)malloc(sizeof(struct node));
        new->vertex = v2;
        new->distance = weight;
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
        new->distance = weight;
        new->next = NULL;
        p = A[v2];
        if (p == NULL)
        {
            A[v2] = new;
        }
        else
        {
            while (p->next != NULL)
                p = p->next;
            p->next = new;
        }
    }
}
void dijkstras(struct node *A[])
{
    struct node *p;
    int visited[10];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        distance[i] = INT_MAX;
    }
    printf("Enter the start vertex : ");
    scanf("%d", &u);
    start = u;
    visited[u] = 1;
    distance[u] = 0;
    for (int i = 0; i <= n; i++)
    {
        u = closevertex(visited);
        visited[u] = 1;
        p = A[u];
        while (p != NULL)
        {
            if (visited[p->vertex] == 0 && p->distance + distance[u] < distance[p->vertex])
            {
                distance[p->vertex] = p->distance + distance[u];
            }
            p = p->next;
        }
    }
}
int closevertex(int visited[])
{
    int i, min = INT_MAX, index;
    for (int i = 0; i < n; i++)
    {
        if (visited[i] != 1 && distance[i] < min)
        {
            min = distance[i];
            index = i;
        }
    }

    return index;
}
void display()
{
    for (int i = 0; i < n; i++)
    {
        if (i != start)
        {
            printf("\nDistance from %d to %d: %d", start, i, distance[i]);
        }
    }
}