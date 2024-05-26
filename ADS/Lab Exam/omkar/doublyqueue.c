#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Queue
{
    struct Node *front;
    struct Node *rear;
};

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void initializeQueue(struct Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

int isEmpty(struct Queue *queue)
{
    return queue->front == NULL;
}

void enqueue(struct Queue *queue, int value)
{
    struct Node *newNode = createNode(value);
    if (isEmpty(queue))
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        newNode->prev = queue->rear;
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("Enqueued %d into the queue.\n", value);
}
int dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue Underflow. Cannot dequeue from an empty queue.\n");
        return -1;
    }

    struct Node *temp = queue->front;
    int dequeuedValue = temp->data;

    if (temp->next != NULL)
    {
        temp->next->prev = NULL;
    }

    queue->front = temp->next;

    free(temp);

    printf("Dequeued %d from the queue.\n", dequeuedValue);
    return dequeuedValue;
}
void displayQueue(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    struct Node *temp = queue->front;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeQueue(struct Queue *queue)
{
    while (!isEmpty(queue))
    {
        dequeue(queue);
    }
}

int main()
{
    struct Queue queue;
    initializeQueue(&queue);

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    displayQueue(&queue);

    dequeue(&queue);
    dequeue(&queue);

    displayQueue(&queue);

    freeQueue(&queue);

    return 0;
}
