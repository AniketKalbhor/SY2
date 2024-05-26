#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define max 15
struct vertex
{
    int data;
    struct vertex *next;
};
struct stack
{
    int v;
    struct stack *next;
};
struct stack *top = NULL;
void insertl(int, int, struct vertex[], int);
struct queue
{
    int v;
    struct queue *next;
};
struct queue *front = NULL;
struct queue *rear = NULL;
void enqueue(int);
int notemptyqueue(void);
int dequeue(void);
void push(int v);
int pop();
int notemptystack();
void bfsl(struct vertex[], int);
void dfsl(struct vertex[], int);
int main()
{
    int v;
    printf("Enter number of nodes: ");
    scanf("%d", &v);
    struct vertex graphl[max];
    for (int i = 0; i < v; i++)
    {
        graphl[i].data = i;
        graphl[i].next = NULL;
    }
    int exit;
    do
    {
        printf("Do you want to enter an edge (1: yes, 0: no): ");
        scanf("%d", &exit);
        if (exit)
        {
            int v1, v2;
            printf("\nEnter the vertices of edge: ");
            scanf("%d%d", &v1, &v2);
            if ((v1 >= v) || (v2 >= v))
            {
                printf("\nError! number of nodes exceeded!");
                continue;
            }
            insertl(v1, v2, graphl, v);
        }
    } while (exit);
    printf("\nPerforming BFS using adjacency list");
    bfsl(graphl, v);
    printf("\n DFS : ");
    dfsl(graphl, v);
    return 0;
}
void insertl(int vertex1, int vertex2, struct vertex graph[], int n)
{
    struct vertex *temp;
    temp = (struct vertex *)malloc(sizeof(struct vertex));
    temp->data = vertex2;
    temp->next = graph[vertex1].next;
    graph[vertex1].next = temp;

    temp = (struct vertex *)malloc(sizeof(struct vertex));
    temp->data = vertex1;
    temp->next = graph[vertex2].next;
    graph[vertex2].next = temp;
}
void enqueue(int v)
{
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));
    temp->v = v;
    temp->next = NULL;
    if (notemptyqueue() == 0)
    {
        rear = temp;
        front = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }
}
int notemptyqueue(void)
{
    return ((front != NULL) && (rear != NULL));
}
int dequeue(void)
{
    if (front != NULL)
    {
        int temp = front->v;
        struct queue *t = front;
        front = front->next;
        if (t == rear)
        {
            rear = NULL;
        }
        free(t);
        return temp;
    }
}
void bfsl(struct vertex graph[], int n)
{
    int visited[max];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    int v;
    printf("Enter start vertex : ");
    scanf("%d", &v);
    visited[v] = 1;
    enqueue(v);
    while (notemptyqueue())
    {
        v = dequeue();
        printf("%d", v);
        struct vertex temp = graph[v];
        struct vertex *p = temp.next;
        while (p != NULL)
        {
            if (visited[p->data] == 0)
            {
                enqueue(p->data);
                visited[p->data] = 1;
            }
            p = p->next;
        }
    }
}
void dfsl(struct vertex graph[], int n)
{
    int visited[max];
    struct vertex *p;

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    int v;
    printf("Enter start vertex : ");
    scanf("%d", &v);

    push(v);
    visited[v] = 1;

    while (notemptystack())
    {
        v = pop();
        printf("%d ", v);

        p = graph[v].next;
        while (p != NULL)
        {
            if (visited[p->data] == 0)
            {
                push(p->data);
                visited[p->data] = 1;
            }
            p = p->next;
        }
    }
}
void push(int v)
{
    struct stack *temp;
    temp = (struct stack *)malloc(sizeof(struct stack));
    temp->v = v;
    temp->next = top;
    top = temp;
}
int pop()
{
    struct stack *temp = top;
    top = top->next;
    int n = temp->v;
    free(temp);
    return n;
}
int notemptystack()
{
    return (top != NULL);
}