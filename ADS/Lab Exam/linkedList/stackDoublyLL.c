//       Implement Push and POP operations of STACK on Doubly linked lists
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Stack
{
    struct Node* top;
};

void initialize(struct Stack* stack)
{
    stack->top = NULL;
};

void push(struct Stack* stack, int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(struct Stack* stack)
{
    if (stack->top == NULL)
    {
        printf("Stack underflow\n");
        return -1;
    }

    int data = stack->top->data;

    struct Node* temp = stack->top;

    stack->top = stack->top->next;
    stack->top->prev = NULL;

    free(temp);
    return data;
}

void displayStack(struct Stack* stack)
{
    if (stack->top == -1)
    {
        printf("Stack underflow\n");
    }

    else
    {
        struct Node* current = stack->top;

        while (current != NULL)
        {
            printf("%d ",current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main()
{
    struct Stack stack;
    initialize(&stack);

    int key;

    while (1)
    {
        int choice;
        printf("1.Push \n2.Pop \n3. Display stack \n4.Exit\n\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter element to push\n");
            scanf("%d",&key);
            push(&stack, key);
            break;
        case 2:
            pop(&stack);
            break;
        case 3:
            displayStack(&stack);
            break;
        case 4:
            exit(0);
            break;
        }
    }
}
