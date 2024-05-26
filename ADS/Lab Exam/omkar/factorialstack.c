#include <stdio.h>
#define MAX 10
struct Stack
{
    int arr[MAX];
    int top;
};
void initialize(struct Stack *stack)
{
    stack->top = -1;
}
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}
int isFull(struct Stack *stack)
{
    return stack->top == MAX - 1;
}

void push(struct Stack *stack, int value)
{
    if (isFull(stack))
    {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

int factorial(int n)
{
    struct Stack stack;
    initialize(&stack);

    for (int i = 1; i <= n; i++)
    {
        push(&stack, i);
    }

    int result = 1;
    while (!isEmpty(&stack))
    {
        result *= pop(&stack);
    }

    return result;
}

int main()
{
    int num;
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &num);
    printf("Factorial of %d is %d\n", num, factorial(num));

    return 0;
}
