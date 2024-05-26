#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* front;
struct Node* rear;

int isEmpty()
{
    return (front == NULL && rear == NULL);
}

void Enqueue(int data)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));

    if (p == NULL)
    {
        printf("Memory allocation error\n");
    }

    p->data = data;
    p->next = NULL;

    printf("Enqueued %d\n", p->data);

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

void Dequeue()
{
    if (isEmpty())
    {
        printf("Can't dequeue, queue is empty\n");
        return;
    }

    struct Node* temp = front;
    int dequeueData = temp -> data;

    printf("Dequeued %d\n", temp->data);

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
}

void display()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }

    struct Node* current = front;

    while(current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
}

void peek()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }

    printf("%d\n", front->data);
}

int main()
{
    display();
    Enqueue(9);
    Enqueue(8);
    peek();
    Dequeue();
    Dequeue();
    Dequeue();
}
