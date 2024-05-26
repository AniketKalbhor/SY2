#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Stack
{
    struct Node *top;
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
void initializeStack(struct Stack *stack)
{
    stack->top = NULL;
}
int isEmpty(struct Stack *stack)
{
    return stack->top == NULL;
}

void push(struct Stack *stack, int value)
{
    struct Node *newNode = createNode(value);
    if (isEmpty(stack))
    {
        stack->top = newNode;
    }
    else
    {
        newNode->next = stack->top;
        stack->top->prev = newNode;
        stack->top = newNode;
    }
    printf("Pushed %d onto the stack.\n", value);
}
int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow. Cannot pop from an empty stack.\n");
        return -1;
    }

    struct Node *temp = stack->top;
    int poppedValue = temp->data;

    if (temp->next != NULL)
    {
        temp->next->prev = NULL;
    }

    stack->top = temp->next;
    free(temp);

    printf("Popped %d from the stack.\n", poppedValue);
    return poppedValue;
}

void displayStack(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements: ");
    struct Node *temp = stack->top;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeStack(struct Stack *stack)
{
    while (!isEmpty(stack))
    {
        pop(stack);
    }
}

int main()
{
    struct Stack stack;
    initializeStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    displayStack(&stack);

    pop(&stack);
    pop(&stack);

    displayStack(&stack);

    freeStack(&stack);

    return 0;
}
