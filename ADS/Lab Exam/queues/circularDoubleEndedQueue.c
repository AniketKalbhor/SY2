//       Write a Program to implement circular double ended queue where user can add and remove the elements from both front and rear of the queue
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct DEQueue
{
    int data[MAX];
    int front;
    int rear;
};

void initialize(struct DEQueue* dq)
{
    dq->front = -1;
    dq->rear = -1;
}

int isEmpty(struct DEQueue* dq)
{
    if (dq->front == -1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int isFull(struct DEQueue* dq)
{
    if (dq->front == 0  && dq->rear == MAX - 1 || dq->front  == dq->rear + 1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void insertAtFront(struct DEQueue* dq, int key)
{
    if (isFull(dq))
    {
        printf("Queue is full\n");
        return;
    }

    if (isEmpty(dq))
    {
        dq->front = 0;
        dq->rear = 0;
    }

    else if (dq->front == 0)
    {
        dq->front = MAX - 1;
    }

    else
    {
        dq->front = dq->front - 1;
    }

    dq->data[dq->front] = key;
}

void insertAtRear(struct DEQueue* dq, int key)
{
    if (isFull(dq))
    {
        printf("Queue is full\n");
        return;
    }

    if (isEmpty(dq))
    {
        dq->front = 0;
        dq->rear = 0;
    }

    else if (dq->rear == MAX - 1)
    {
        dq->rear = 0;
    }

    else
    {
        dq->rear = dq->rear + 1;
    }

    dq->data[dq->rear] = key;
}

int deleteAtFront(struct DEQueue* dq)
{
    if (isEmpty(dq))
    {
        printf("Queue is empty\n");
        return -1;
    }

    int key = dq->data[dq->front];

    if (dq->front == dq->rear)
    {
        dq->front = -1;
        dq->rear = -1;
    }

    else if (dq->front == MAX - 1)
    {
        dq->front = 0;
    }

    else
    {
        dq->front = dq->front + 1;
    }

    return key;
}

int deleteAtRear(struct DEQueue* dq)
{
    if (isEmpty(dq))
    {
        printf("Queue is empty\n");
        return -1;
    }

    int key = dq->data[dq->rear];

    if (dq->front == dq->rear)
    {
        dq->front = -1;
        dq->rear = -1;
    }

    else if (dq->rear == 0)
    {
        dq->rear = MAX - 1;
    }

    else
    {
        dq->rear = dq->rear - 1;
    }

    return key;

}

void display(struct DEQueue *dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty\n");
        return;
    }

    printf("Deque elements are: ");
    int i = dq->front;
    if (dq->front <= dq->rear) {
        while (i <= dq->rear) {
            printf("%d ", dq->data[i]);
            i++;
        }
    } else {
        while (i <= MAX - 1) {
            printf("%d ", dq->data[i]);
            i++;
        }
        i = 0;
        while (i <= dq->rear) {
            printf("%d ", dq->data[i]);
            i++;
        }
    }
    printf("\n");
}

int main() {
    struct DEQueue dq;
    initialize(&dq);

    insertAtRear(&dq, 5);
    insertAtRear(&dq, 10);
    insertAtFront(&dq, 15);
    display(&dq);

    printf("Deleted element from front: %d\n", deleteAtFront(&dq));
    printf("Deleted element from rear: %d\n", deleteAtRear(&dq));
    display(&dq);

    return 0;
}
