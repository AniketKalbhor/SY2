//       Write a Program to implement multiple two queues using array and perform following operations on it. A. Addq, B. Delq, C. Display Queue.
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct twoQueue
{
    int data[MAX];
    int front1;
    int rear1;
    int front2;
    int rear2;
};

void initialize(struct twoQueue* q)
{
    q->front1 = -1;
    q->front2 = MAX;
    q->rear1 = -1;
    q->rear2 = MAX;
}

int isFull(struct twoQueue* q)
{
    if (q->rear1 + 1 == q->rear2)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int isEmpty1(struct twoQueue* q)
{
    if (q->front1 == -1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int isEmpty2(struct twoQueue* q)
{
    if (q->front2 == MAX)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void add1(struct twoQueue* q, int key)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
        return;
    }

    if (isEmpty1(q))
    {
        q->front1 = 0;
    }

    q->data[++q->rear1] = key;
}

void add2(struct twoQueue* q, int key)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
        return;
    }

    if (isEmpty2(q))
    {
        q->front2 = MAX - 1;
    }

    q->data[--q->rear2] = key;
}

int delete1(struct twoQueue* q)
{
    if (isEmpty1(q))
    {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->data[q->front1];

    if (q->front1 == q->rear1)
    {
        q->front1 = -1;
        q->rear1 = -1;
    }

    else
    {
        q->front1 = q->front1 + 1;
    }

    return value;
}

int delete2(struct twoQueue* q)
{
    if (isEmpty2(q))
    {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->data[q->front2];

    if (q->front2 == q->rear2)
    {
        q->front2 = MAX;
        q->rear2 = MAX;
    }

    else
    {
        q->front2 = q->front2 - 1;
    }

    return value;
}

void displayQueue1(struct twoQueue* q) {
    if (isEmpty1(q)) {
        printf("Queue 1 is empty\n");
    } else {
        printf("Queue 1: ");
        for (int i = q->front1; i <= q->rear1; i++) {
            printf("%d ", q->data[i]);
        }
        printf("\n");
    }
}

void displayQueue2(struct twoQueue* q) {
    if (isEmpty2(q)) {
        printf("Queue 2 is empty\n");
    } else {
        printf("Queue 2: ");
        for (int i = q->front2; i >= q->rear2; i--) {
            printf("%d ", q->data[i]);
        }
        printf("\n");
    }
}

int main()
{
    struct twoQueue tq;
    initialize(&tq);

    int choice, value;

    while (1) {
        printf("1. Add to Queue 1\n");
        printf("2. Add to Queue 2\n");
        printf("3. Delete from Queue 1\n");
        printf("4. Delete from Queue 2\n");
        printf("5. Display Queue 1\n");
        printf("6. Display Queue 2\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to add to Queue 1: ");
                scanf("%d", &value);
                add1(&tq, value);
                break;
            case 2:
                printf("Enter value to add to Queue 2: ");
                scanf("%d", &value);
                add2(&tq, value);
                break;
            case 3:
                value = delete1(&tq);
                if (value != -1) {
                    printf("Deleted value from Queue 1: %d\n", value);
                }
                break;
            case 4:
                value = delete2(&tq);
                if (value != -1) {
                    printf("Deleted value from Queue 2: %d\n", value);
                }
                break;
            case 5:
                displayQueue1(&tq);
                break;
            case 6:
                displayQueue2(&tq);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
