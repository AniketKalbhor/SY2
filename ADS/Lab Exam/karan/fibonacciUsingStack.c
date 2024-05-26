#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int data) {
    if (top >= MAX - 1) {
        printf("Stack overflow\n");
    } else {
        stack[++top] = data;
    }
}

int pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;  // Return a sentinel value to indicate underflow
    } else {
        return stack[top--];
    }
}

int isEmpty() {
    return top == -1;
}

void fibonacci(int n) {
    if (n <= 0) {
        printf("Invalid input\n");
        return;
    } else if (n == 1) {
        printf("Fibonacci Series: 0\n");
        return;
    } else if (n == 2) {
        printf("Fibonacci Series: 0 1\n");
        return;
    }

    // Push the first two Fibonacci numbers
    push(0);
    push(1);

    int a, b, c;
    printf("Fibonacci Series: 0 1 ");

    for (int i = 2; i < n; i++) {
        // Pop the top two elements
        b = pop();
        a = pop();

        // Calculate the next Fibonacci number
        c = a + b;
        printf("%d ", c);

        // Push the last two Fibonacci numbers back onto the stack
        push(b);
        push(c);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of terms in the Fibonacci series: ");
    scanf("%d", &n);

    fibonacci(n);

    return 0;
}
