#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

// Stack for operators and operands
char stack[MAX_STACK_SIZE];
int top = -1;

// Stack operations
void push(char ch) {
    if (top < MAX_STACK_SIZE - 1) {
        stack[++top] = ch;
    } else {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

char peek() {
    if (top >= 0) {
        return stack[top];
    } else {
        return '\0'; // Indicates empty stack
    }
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

// Convert infix to postfix
void infixToPostfix(const char* infix, char* postfix) {
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (isDigit(infix[i])) {
            while (isDigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top >= 0 && peek() != '(') {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            if (top >= 0 && peek() == '(') {
                pop();
            }
        } else if (isOperator(infix[i])) {
            while (top >= 0 && precedence(peek()) >= precedence(infix[i])) {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            push(infix[i]);
        }
    }
    while (top >= 0) {
        postfix[j++] = pop();
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

// Evaluate postfix expression
double evaluatePostfix(const char* postfix) {
    double valueStack[MAX_STACK_SIZE];
    int valueTop = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isDigit(postfix[i])) {
            double num = 0;
            while (isDigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            if (postfix[i] == '.') {
                i++;
                double frac = 1;
                while (isDigit(postfix[i])) {
                    frac /= 10;
                    num += (postfix[i++] - '0') * frac;
                }
            }
            valueStack[++valueTop] = num;
        } else if (postfix[i] == ' ') {
            continue;
        } else if (isOperator(postfix[i])) {
            double operand2 = valueStack[valueTop--];
            double operand1 = valueStack[valueTop--];
            switch (postfix[i]) {
                case '+': valueStack[++valueTop] = operand1 + operand2; break;
                case '-': valueStack[++valueTop] = operand1 - operand2; break;
                case '*': valueStack[++valueTop] = operand1 * operand2; break;
                case '/': valueStack[++valueTop] = operand1 / operand2; break;
            }
        }
    }
    return valueStack[valueTop];
}

// Main function
int main() {
    char infix[MAX_STACK_SIZE];
    char postfix[MAX_STACK_SIZE];

    printf("Enter an infix expression: ");
    strcpy(infix, "((2+3)*4)/5");

    // Remove newline character from input
    int len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("Result: %f\n", result);

    return 0;
}
