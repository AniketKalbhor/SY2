#include <stdio.h>

#define MAX_SIZE 10

struct TwoStacks
{
    int arr[MAX_SIZE];
    int top1;
    int top2;
};

void initialize(struct TwoStacks *stacks)
{
    stacks->top1 = -1;
    stacks->top2 = MAX_SIZE;
}

int isStack1Full(struct TwoStacks *stacks)
{
    return stacks->top1 + 1 == stacks->top2;
}
int isStack2Full(struct TwoStacks *stacks)
{
    return stacks->top2 - 1 == stacks->top1;
}
int isStack1Empty(struct TwoStacks *stacks)
{
    return stacks->top1 == -1;
}
int isStack2Empty(struct TwoStacks *stacks)
{
    return stacks->top2 == MAX_SIZE;
}
void pushStack1(struct TwoStacks *stacks, int value)
{
    if (isStack1Full(stacks))
    {
        printf("Stack 1 is full. Cannot push.\n");
    }
    else
    {
        stacks->arr[++stacks->top1] = value;
    }
}

void pushStack2(struct TwoStacks *stacks, int value)
{
    if (isStack2Full(stacks))
    {
        printf("Stack 2 is full. Cannot push.\n");
    }
    else
    {
        stacks->arr[--stacks->top2] = value;
    }
}

int popStack1(struct TwoStacks *stacks)
{
    if (isStack1Empty(stacks))
    {
        printf("Stack 1 is empty. Cannot pop.\n");
        return -1;
    }
    else
    {
        return stacks->arr[stacks->top1--];
    }
}

int popStack2(struct TwoStacks *stacks)
{
    if (isStack2Empty(stacks))
    {
        printf("Stack 2 is empty. Cannot pop.\n");
        return -1;
    }
    else
    {
        return stacks->arr[stacks->top2++];
    }
}

void displayStack1(struct TwoStacks *stacks)
{
    printf("Stack 1: ");
    for (int i = 0; i <= stacks->top1; i++)
    {
        printf("%d ", stacks->arr[i]);
    }
    printf("\n");
}

void displayStack2(struct TwoStacks *stacks)
{
    printf("Stack 2: ");
    for (int i = MAX_SIZE - 1; i >= stacks->top2; i--)
    {
        printf("%d ", stacks->arr[i]);
    }
    printf("\n");
}

int main()
{
    struct TwoStacks stacks;
    initialize(&stacks);

    pushStack1(&stacks, 1);
    pushStack1(&stacks, 2);
    pushStack2(&stacks, 3);
    pushStack2(&stacks, 4);

    displayStack1(&stacks);
    displayStack2(&stacks);

    printf("Popped from Stack 1: %d\n", popStack1(&stacks));
    printf("Popped from Stack 2: %d\n", popStack2(&stacks));

    displayStack1(&stacks);
    displayStack2(&stacks);

    return 0;
}
