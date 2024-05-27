// Write a Program to accept a graph from user and represent it with Adjacency Matrix and perform DFS BFS traversals on it.
#include <stdio.h>
#include <stdlib.h>
#define MAX 50
//bfs code
struct Queue
{
    int data;
    struct Queue* next;
};

struct Queue* front;
struct Queue* rear;

int isEmpty()
{
    return (front == NULL && rear == NULL);
}

void enQueue(int key)
{
    struct Queue* p = (struct Queue*)malloc(sizeof(struct Queue));
    if (p == NULL)
        printf("Memory allocation failed\n");
    p->data = key;
    p->next = NULL;
    if (isEmpty()){
        front = p;
        rear = p;
    }
    else{
        rear->next = p;
        rear = p;
    }
}

int deQueue()
{
    if (isEmpty())
        printf("Queue is empty\n");
    struct Queue* temp = front;
    int val = temp->data;
    if (front == rear){
        front = NULL;
        rear = NULL;
    }
    else
        front = front->next;
    free(temp);
    return val;
}

void BFS(int G[10][10],int vertex)
{
    int visited[vertex], i, u, start;
    for (i = 0;i < vertex;i++)
        visited[i] = 0;
    printf("Enter starting vertex: ");
    scanf("%d",&start);
    visited[start] = 1;
    enQueue(start);

    while(!isEmpty())
    {
        u = deQueue();
        printf("%d ",u);

        for (i = 0;i < vertex;i++)
        {
            if (G[u][i] == 1 && visited[i] == 0)
            {
                enQueue(i);
                visited[i] = 1;
            }
        }
    }
}

//dfs code 
int stack[MAX];
int top = -1;
int emptyStack()
{
    if (top == -1)
        return 1;
    else
        return 0;
}

void push(int n)
{
    if (top >= MAX-1)
        printf("Stack overflow\n");
    stack[++top] = n;
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

void DFS(int G[10][10], int vertex)
{
    int visited[vertex], i, u, st;
    for (i = 0;i < vertex;i++)
        visited[i] = 0;
    printf("Enter start vertex\n");
    scanf("%d",&st);
    push(st);
    printf("%d ",st);
    visited[st] = 1;
    u = st;

    while (!emptyStack())
    {
        for (i = 0;i < vertex;i++)
            if (G[u][i] == 1 && visited[i] != 1)
            {
                push(i);
                visited[i] = 1;
                printf("%d ",i);
                u = i;
                break;
            }
        if (i == vertex)
        {
            pop();
            u = stack[top];
        }
    }
}