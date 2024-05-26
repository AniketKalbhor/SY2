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
void fibonacci(int n)
{
    struct Stack stack;
    initialize(&stack);

    int a = 0, b = 1, next;
    for (int i = 0; i < n; i++)
    {
        push(&stack, a);
        next = a + b;
        a = b;
        b = next;
    }
    int j = n - 1;
    int count = 0;
    int number[100];
    printf("Fibonacci Series: ");
    while (!isEmpty(&stack))
    {
        number[j] = pop(&stack);
        j--;
        count += 1;
    }
    for (int i = 0; i < count; i++)
    {
        printf("%d ", number[i]);
    }

    printf("\n");
}

int main()
{
    int num;
    printf("Enter the number of terms in Fibonacci series: ");
    scanf("%d", &num);
    fibonacci(num);

    return 0;
}
