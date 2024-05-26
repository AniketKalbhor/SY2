#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Node
{
    int vertex;
    struct Node* next;
};

struct Node* front;
struct Node* rear;
struct Node* a[10];

int stack[MAX];
int top = -1;

int isEmpty()
{
    return (front == NULL && rear == NULL);
}

void Enqueue(int key)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));

    if (p == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    p->vertex = key;
    p->next = NULL;

    if (isEmpty())
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

int Dequeue()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return -1;
    }

    struct Node* temp = front;
    int val = temp->vertex;

    if (front == rear)
    {
        front = NULL;
        rear = NULL;
    }

    else
    {
        front = front->next;
    }

    free(temp);
    return val;
}

int emptyStack()
{
    if (top == -1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void push(int key)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow\n");
    }

    else
    {
        stack[++top] = key;
    }
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

void BFS(struct Node* a[10], int v)
{
    int visited[10], st, u, i;

    for (i = 0; i < v; i++)
    {
        visited[i] = 0;
    }

    printf("Enter start vertex\n");
    scanf("%d", &st);

    visited[st] = 1;

    Enqueue(st);

    while (!isEmpty())
    {
        u = Dequeue();
        printf("%d ", u);

        struct Node* p = a[u];

        while (p != NULL)
        {
            if (visited[p->vertex] == 0)
            {
                Enqueue(p->vertex);
                visited[p->vertex] = 1;
            }
            p = p->next;
        }
    }
}

void DFS(struct Node* a[10], int v)
{
    int visited[10], i, u, st;
    struct Node* p;

    for (i = 0;i < v;i++)
    {
        visited[i] = 0;
    }
    printf("Enter start vertex\n");
    scanf("%d",&st);

    push(st);
    printf("%d ",st);

    visited[st] = 1;

    u = st;

    p = a[u];

    do {
        p = a[u];

        while(p != NULL)
        {
            if (visited[p->vertex] == 0)
            {
                push(p->vertex);
                visited[p->vertex] = 1;
                printf("%d ",p->vertex);

                u = p->vertex;
                break;
            }

            else
            {
                p = p->next;
            }
        }
        if (p == NULL)
        {
            pop();
            u = stack[top];
        }
    } while(!emptyStack());
}

void displayGraph(struct Node* a[10], int v) {
    printf("Graph Representation:\n");
    for (int i = 0; i < v; i++)
    {
        printf("Vertex %d -> ", i);
        struct Node* current = a[i];
        while (current != NULL)
        {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

int main()
{
    struct Node* p;
    struct Node* newV;
    int u, v, vnum;
    char ch;

    printf("Enter the number of vertices\n");
    scanf("%d", &vnum);

    for (int i = 0; i < vnum; i++)
    {
        a[i] = NULL;
    }

    do
    {
        printf("Enter edge\n");
        scanf("%d", &u);
        scanf("%d", &v);

        newV = (struct Node*)malloc(sizeof(struct Node));
        newV->vertex = v;
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

    displayGraph(a, vnum);

    int choice;

    while (1)
    {
        printf("\n\n1. BFS\n2. DFS\n3. Exit\n");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            BFS(a, vnum);
            break;
        case 2:
            DFS(a, vnum);
            break;
        case 3:
            exit(0);
        }
    }
}
