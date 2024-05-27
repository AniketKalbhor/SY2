//  WAP to implement following by using stack A. Factorial of a given number B. Generation of Fibonacci series
#include <stdio.h>
#include <stdlib.h>

// Stack structure definition
typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

// Function to initialize the stack
Stack* createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Function to check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Function to push an element onto the stack
void push(Stack *stack, int item) {
    if (isFull(stack))
        return;
    stack->data[++stack->top] = item;
}

// Function to pop an element from the stack
int pop(Stack *stack) {
    if (isEmpty(stack))
        return -1;
    return stack->data[stack->top--];
}

// Function to calculate factorial using stack
int factorial(int n) {
    Stack *stack = createStack(n);
    int result = 1;

    // Push all numbers from 1 to n onto the stack
    for (int i = 1; i <= n; i++) {
        push(stack, i);
    }

    // Pop and multiply the elements to get the factorial
    while (!isEmpty(stack)) {
        result *= pop(stack);
    }

    free(stack->data);
    free(stack);
    return result;
}

// Function to generate Fibonacci series using stack
void generateFibonacci(int n) {
    if (n <= 0) return;

    Stack *stack = createStack(n);
    int a = 0, b = 1;

    printf("Fibonacci series: %d %d ", a, b);
    for (int i = 2; i < n; i++) {
        int next = a + b;
        push(stack, next);
        a = b;
        b = next;
        printf("%d ", next);
    }
    printf("\n");

    free(stack->data);
    free(stack);
}

int main() {
    int choice, n;

    do {
        printf("\n\n1. Factorial of a given number\n2. Generation of Fibonacci series\n0. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to calculate factorial: ");
                scanf("%d", &n);
                printf("Factorial of %d is %d\n", n, factorial(n));
                break;
            case 2:
                printf("Enter the number of terms for Fibonacci series: ");
                scanf("%d", &n);
                generateFibonacci(n);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
