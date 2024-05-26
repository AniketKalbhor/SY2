#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int data)
{
    if (top >= MAX - 1)
    {
        printf("Stack overflow\n");
    }
    stack[++top] = data;
}

int pop()
{
    if (top == -1)
    {
        printf("Stack underflow\n");
    }

    return stack[top--];
}

int isEmpty()
{
    if (top == -1)
    {
        return 1;
    }

    return 0;
}

void factorial(int n)
{
    int result = 1;

    if (n == 0)
    {
        printf("0");
        return;
    }
    else if (n == 1)
    {
        printf("1");
        return;
    }
    else
    {
        for (int i = 1;i <= n;i++)
        {
            push(i);
        }
    }

    for (int i = 1;i < n;i++)
    {
        result = result*pop();
    }

    printf("Result: %d\n",result);
}

int main()
{
    int n;
    printf("Enter the number whose factorial you want\n");
    scanf("%d",&n);

    factorial(n);
}
