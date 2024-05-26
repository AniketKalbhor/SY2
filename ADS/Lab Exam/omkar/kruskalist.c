#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int n, e;
int parent[10];

struct node
{
    int vertex;
    int distance;
    struct node *next;
} A[10];
void kruskals(struct node *A[]);
int Findparent(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void Union(int i, int j)
{
    int x, y;
    x = Findparent(i);
    y = Findparent(j);
    parent[x] = y;
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
            {
                p = p->next;
            }
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
int main()
{
    struct node *A[10] = {0};
    adj_list(A);
    kruskals(A);
    return 0;
}
void kruskals(struct node *A[])
{
    int a, b, i, j, min = INT_MAX, cost = 0, ne = 0;
    struct node *p, *temp;
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
    while (ne < n - 1)
    {
        min = INT_MAX;
        for (i = 0; i <= n; i++)
        {
            p = A[i];
            while (p != NULL)
            {
                if (parent[i] != parent[p->vertex] && p->distance < min)
                {
                    min = p->distance;
                    a = i;
                    b = p->vertex;
                }
                p = p->next;
            }
        }
        Union(a, b);
        printf("%d-%d=>", a, b);
        ne++;
        temp = A[a];
        while (temp != NULL)
        {
            if (temp->vertex == b)
            {
                temp->distance = INT_MAX;
                break;
            }
            temp = temp->next;
        }
        temp = A[b];
        while (temp != NULL)
        {
            if (temp->vertex == a)
            {
                temp->distance = INT_MAX;
                break;
            }
            temp = temp->next;
        }
        cost += min;
    }
}