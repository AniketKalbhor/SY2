#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Stack
{
    struct Node* top;
};

void initializeStack(struct Stack* stack)
{
    stack->top = NULL;
}

int isEmpty(struct Stack* stack)
{
    return (stack->top == NULL);
}

void push(struct Stack* stack, int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return -1;
    }

    int data = stack->top->data;

    struct Node* temp = stack->top;
    stack->top = stack->top->next;

    free(temp);

    return data;
}

int peek(struct Stack* stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty\n");
        return -1;
    }

    return stack->top->data;
}

void printStack(struct Stack* stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty");
        return;
    }

    struct Node* current = stack->top;

    while(current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeStack(struct Stack* stack)
{
    while(!isEmpty(stack))
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

    printStack(&stack);

    printf("Top element: %d\n", peek(&stack));
    printf("Popped element: %d\n",pop(&stack));

    printStack(&stack);
    freeStack(&stack);
    return 0;
}
