#include <stdio.h>
#include <stdlib.h>

#define MAX 5

struct Deque
{
    int arr[MAX];
    int front, rear;
};
void initialize(struct Deque *deque)
{
    deque->front = -1;
    deque->rear = -1;
}
int isEmpty(struct Deque *deque)
{
    return (deque->front == -1 && deque->rear == -1);
}
int isFull(struct Deque *deque)
{
    return (deque->front == (deque->rear + 1) % MAX);
}

void addToFront(struct Deque *deque, int value)
{
    if (isFull(deque))
    {
        printf("Deque is full. Cannot add to front.\n");
        return;
    }

    if (isEmpty(deque))
    {
        deque->front = 0;
        deque->rear = 0;
    }
    else
    {
        deque->front = (deque->front - 1 + MAX) % MAX;
    }

    deque->arr[deque->front] = value;
    printf("Added %d to the front of the deque.\n", value);
}

void addToRear(struct Deque *deque, int value)
{
    if (isFull(deque))
    {
        printf("Deque is full. Cannot add to rear.\n");
        return;
    }

    if (isEmpty(deque))
    {
        deque->front = 0;
        deque->rear = 0;
    }
    else
    {
        deque->rear = (deque->rear + 1) % MAX;
    }

    deque->arr[deque->rear] = value;
    printf("Added %d to the rear of the deque.\n", value);
}

void removeFromFront(struct Deque *deque)
{
    if (isEmpty(deque))
    {
        printf("Deque is empty. Cannot remove from front.\n");
        return;
    }

    int removedValue = deque->arr[deque->front];

    if (deque->front == deque->rear)
    {
        initialize(deque);
    }
    else
    {
        deque->front = (deque->front + 1) % MAX;
    }

    printf("Removed %d from the front of the deque.\n", removedValue);
}
void removeFromRear(struct Deque *deque)
{
    if (isEmpty(deque))
    {
        printf("Deque is empty. Cannot remove from rear.\n");
        return;
    }

    int removedValue = deque->arr[deque->rear];

    if (deque->front == deque->rear)
    {
        initialize(deque);
    }
    else
    {
        deque->rear = (deque->rear - 1 + MAX) % MAX;
    }

    printf("Removed %d from the rear of the deque.\n", removedValue);
}
void display(struct Deque *deque)
{
    if (isEmpty(deque))
    {
        printf("Deque is empty.\n");
        return;
    }

    printf("Deque elements: ");
    int i = deque->front;
    do
    {
        printf("%d ", deque->arr[i]);
        i = (i + 1) % MAX;
    } while (i != (deque->rear + 1) % MAX);
    printf("\n");
}

int main()
{
    struct Deque deque;
    initialize(&deque);

    int choice, value;

    do
    {
        printf("\n--- Deque Operations ---\n");
        printf("1. Add to Front\n");
        printf("2. Add to Rear\n");
        printf("3. Remove from Front\n");
        printf("4. Remove from Rear\n");
        printf("5. Display Deque\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the value to add to the front: ");
            scanf("%d", &value);
            addToFront(&deque, value);
            break;
        case 2:
            printf("Enter the value to add to the rear: ");
            scanf("%d", &value);
            addToRear(&deque, value);
            break;
        case 3:
            removeFromFront(&deque);
            break;
        case 4:
            removeFromRear(&deque);
            break;
        case 5:
            display(&deque);
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
