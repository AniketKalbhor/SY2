/*       WAP to implement two stack using array and perform following operations on it. A. PUSH, B. POP, C. StackFull D. StackeEmpty E. Display Stack.*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct twoStack
{
    int top1;
    int top2;
    int data[MAX];
};

void initialize(struct twoStack* stack)
{
    stack->top1 = -1;
    stack->top2 = MAX;
}

int isFull(struct twoStack* stack)
{
    if (stack->top1 + 1 == stack->top2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmpty1(struct twoStack* stack)
{
    if (stack->top1 == -1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int isEmpty2(struct twoStack* stack)
{
    if (stack->top2 == MAX)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void push1(struct twoStack* stack, int key)
{
    if (isFull(stack))
    {
        printf("Stack 1 overflow\n");
        return;
    }
    else
    {
        stack->data[++stack->top1] = key;
    }
}

void push2(struct twoStack* stack, int key)
{
    if (isFull(stack))
    {
        printf("Stack 2 overflow\n");
        return;
    }
    else
    {
        stack->data[--stack->top2] = key;
    }
}

int pop1(struct twoStack* stack)
{
    if (isEmpty1(stack))
    {
        printf("Stack 1 underflow\n");
        return -1;
    }

    else
    {
        return stack->data[stack->top1--];
    }
}

int pop2(struct twoStack* stack)
{
    if (isEmpty2(stack))
    {
        printf("Stack 2 underflow\n");
        return -1;
    }

    else
    {
        return stack->data[stack->top2++];
    }
}

void displayStack1(struct twoStack *ts) {
    if (isEmpty1(ts)) {
        printf("Stack 1 is empty\n");
    } else {
        printf("Stack 1: ");
        for (int i = 0; i <= ts->top1; i++) {
            printf("%d ", ts->data[i]);
        }
        printf("\n");
    }
}

void displayStack2(struct twoStack *ts) {
    if (isEmpty2(ts)) {
        printf("Stack 2 is empty\n");
    } else {
        printf("Stack 2: ");
        for (int i = MAX - 1; i >= ts->top2; i--) {
            printf("%d ", ts->data[i]);
        }
        printf("\n");
    }
}

int main()
{
    struct twoStack stack;

    initialize(&stack);

    while(1)
    {
        int choice;
        int key;
        int popped;
        printf("1.Push1 2.Push2 3.Pop1 4.Pop2 5.Display1 6.Display2 7.Exit\n\n");

        printf("Enter the choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter data to push\n");
            scanf("%d",&key);
            push1(&stack, key);
            break;
        case 2:
            printf("Enter data to push\n");
            scanf("%d",&key);
            push2(&stack, key);
            break;
        case 3:
            popped = pop1(&stack);
            printf("%d popped\n",popped);
            break;
        case 4:
            popped = pop2(&stack);
            printf("%d popped\n",popped);
            break;
        case 5:
            displayStack1(&stack);
            break;
        case 6:
            displayStack2(&stack);
            break;
        case 7:
            exit(0);
        }
    }
}
