#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define the structure for a queue
struct Queue
{
    int front, rear;
    int items[MAX_SIZE];
};

// Initialize the two queues
struct Queue queue1, queue2;

// Function to initialize a queue
void initQueue(struct Queue *q)
{
    q->front = q->rear = -1;
}

// Function to check if a queue is empty
int isEmpty(struct Queue *q)
{
    return (q->front == -1);
}

// Function to check if a queue is full
int isFull(struct Queue *q)
{
    return (q->rear == MAX_SIZE - 1);
}

// Function to enqueue (Addq) an item to a queue
void enqueue(struct Queue *q, int data)
{
    if (isFull(q))
    {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(q))
    {
        q->front = 0;
    }

    q->rear++;
    q->items[q->rear] = data;
}

// Function to dequeue (Delq) an item from a queue
int dequeue(struct Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // You can choose a different sentinel value if needed
    }

    int data = q->items[q->front];

    if (q->front == q->rear)
    {
        initQueue(q); // Reset the queue
    }
    else
    {
        q->front++;
    }

    return data;
}

// Function to display the contents of a queue
void displayQueue(struct Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue Contents: ");
    for (int i = q->front; i <= q->rear; i++)
    {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int main()
{
    // Initialize the two queues
    initQueue(&queue1);
    initQueue(&queue2);

    // Enqueue elements in both queues
    enqueue(&queue1, 1);
    enqueue(&queue1, 2);
    enqueue(&queue1, 3);

    enqueue(&queue2, 10);
    enqueue(&queue2, 20);
    enqueue(&queue2, 30);

    // Display the contents of both queues
    printf("Queue 1:\n");
    displayQueue(&queue1);

    printf("Queue 2:\n");
    displayQueue(&queue2);

    // Dequeue elements from both queues
    int item1 = dequeue(&queue1);
    int item2 = dequeue(&queue2);

    // Display the contents of both queues after dequeue
    printf("Queue 1 after dequeue:\n");
    displayQueue(&queue1);

    printf("Queue 2 after dequeue:\n");
    displayQueue(&queue2);

    return 0;
}
