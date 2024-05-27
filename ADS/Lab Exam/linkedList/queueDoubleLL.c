//       Implement ADD and DELETE operations of QUEUE on Doubly linked lists
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Queue
{
    struct Node* front;
    struct Node* rear;
};

int isEmpty(struct Queue* q)
{
    if (q->front == NULL)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void Enqueue(struct Queue* q, int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (q->rear == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }

    else
    {
        q->rear->next = newNode;
        newNode->prev = q->rear;
        q->rear = newNode;
    }
}

int Dequeue(struct Queue* q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }

    struct Node* newNode = q->front;

    if (q->front == q->rear)
    {
        q->front = NULL;
        q->rear = NULL;
    }

    int data = newNode->data;

    q->front = q->front->next;
    q->front->prev = NULL;

    return data;
}

void displayQueue(struct Queue* q)
{
    if (isEmpty(&q))
    {
        printf("Queue is empty\n");
        return;
    }

    struct Node* newNode = q->front;

    while (newNode != NULL)
    {
        printf("%d ",newNode->data);
        newNode = newNode->next;
    }

    printf("\n");
}

int main()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;

    int data;

    while(1)
    {
        int choice;
        printf("1.Insert \n2.Delete \n3.Display \n4. Exit\n\n");
        printf("Enter your choice");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter value to insert\n");
            scanf("%d",&data);
            Enqueue(q,data);
            break;
        case 2:
            Dequeue(q);
            break;
        case 3:
            displayQueue(q);
            break;
        case 4:
            exit(0);
        }
    }
}
