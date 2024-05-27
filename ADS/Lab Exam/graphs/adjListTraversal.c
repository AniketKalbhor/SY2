// Write a Program to accept a graph from user and represent it with Adjacency List and perform DFS-BFS traversals on it.
#include <stdio.h>
#include <stdlib.h>
#define MAX 15

struct Node
{
    int vertex;
    struct Node* next;
};

struct Node* front;
struct Node* rear;
struct Node* a[MAX];

int emptyQueue()
{
    return (front == NULL && rear == NULL);
}

void enqueue(int key)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));
    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    p->vertex = key;
    p->next = NULL;

    if (emptyQueue())
    {
        front = p;
        rear = p;
    }
    else
    {
        rear->next = p;
        rear = p;
    }
}

int dequeue()
{
    struct Node* temp = front;

    if (emptyQueue())
    {
        printf("Queue is empty\n");
        return -1;
    }
    int value = temp->vertex;

    if (front == rear)
    {
        front = NULL;
        rear = NULL;
    }
    else
        front = front->next;

    free(temp);
    return value;
}

void BFS(struct Node* a[MAX], int v)
{
    int visited[MAX], st, u, i;
    for (i = 0; i < v; i++)
        visited[i] = 0;

    printf("Enter start vertex\n");
    scanf("%d", &st);
    visited[st] = 1;
    enqueue(st);
    while (!emptyQueue())
    {
        u = dequeue();
        printf("%d ", u);
        struct Node* p = a[u];
        while (p != NULL)
        {
            if (visited[p->vertex] == 0)
            {
                enqueue(p->vertex);
                visited[p->vertex] = 1;
            }
            p = p->next;
        }
    }
}


//----------------------------------DFS----------------------------------

int stack[MAX];
int top = -1;

int emptyStack()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

void push(int key)
{
    if (top >= MAX - 1)
        printf("Stack overflow\n");
    stack[++top] = key;
}

int pop()
{
    if (emptyStack())
    {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

void DFS(struct Node* a[MAX], int v)
{
    int visited[MAX], i, u, st;
    struct Node* p;
    for (i = 0; i < v; i++)
        visited[i] = 0;

    printf("Enter start vertex\n");
    scanf("%d", &st);
    push(st);
    printf("%d ", st);
    visited[st] = 1;
    u = st;
    p = a[u];

    do
    {
        p = a[u];
        while (p != NULL)
        {
            if (visited[p->vertex] == 0)
            {
                push(p->vertex);
                visited[p->vertex] = 1;
                printf("%d ", p->vertex);
                u = p->vertex;
                break;
            }
            else
                p = p->next;
        }
        if (p == NULL)
        {
            pop();
            u = stack[top];
        }
    } while (!emptyStack());
}

void display_list(struct Node* a[MAX], int v)
{
    int i;
    struct Node* p;
    printf("\nAdjacency list:\n");
    for (i = 0; i < v; i++)
    {
        p = a[i];
        printf("%d", i);
        while (p != NULL)
        {
            printf("->%d", p->vertex);
            p = p->next;
        }
        printf("\n");
    }
}

int main()
{
    struct Node* p;
    struct Node* newV;
    int u, v, vertex,e, i;
    char ch;
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
        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = v;
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
    int choice;
    while (1)
    {
        display_list(a, vertex);
        printf("\n1. DFS using adj list\n2. BFS using adj list\n3. Exit\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                DFS(a, vertex);
                break;
            case 2:
                BFS(a, vertex);
                break;
            case 3:
                exit(0);
        }
    }
}