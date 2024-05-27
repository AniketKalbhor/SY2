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

// Reverse the string
void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Convert infix to prefix
void infixToPrefix(const char* infix, char* prefix) {
    char tempInfix[MAX_STACK_SIZE];
    strcpy(tempInfix, infix);
    reverseString(tempInfix);
    
    // Swap '(' with ')' and vice versa
    for (int i = 0; tempInfix[i] != '\0'; i++) {
        if (tempInfix[i] == '(') {
            tempInfix[i] = ')';
        } else if (tempInfix[i] == ')') {
            tempInfix[i] = '(';
        }
    }

    int j = 0;
    for (int i = 0; tempInfix[i] != '\0'; i++) {
        if (isDigit(tempInfix[i])) {
            while (isDigit(tempInfix[i]) || tempInfix[i] == '.') {
                prefix[j++] = tempInfix[i++];
            }
            prefix[j++] = ' ';
            i--;
        } else if (tempInfix[i] == '(') {
            push(tempInfix[i]);
        } else if (tempInfix[i] == ')') {
            while (top >= 0 && peek() != '(') {
                prefix[j++] = pop();
                prefix[j++] = ' ';
            }
            if (top >= 0 && peek() == '(') {
                pop();
            }
        } else if (isOperator(tempInfix[i])) {
            while (top >= 0 && precedence(peek()) > precedence(tempInfix[i])) {
                prefix[j++] = pop();
                prefix[j++] = ' ';
            }
            push(tempInfix[i]);
        }
    }
    while (top >= 0) {
        prefix[j++] = pop();
        prefix[j++] = ' ';
    }
    prefix[j] = '\0';

    reverseString(prefix);
}

// Evaluate prefix expression
double evaluatePrefix(const char* prefix) {
    double valueStack[MAX_STACK_SIZE];
    int valueTop = -1;

    int len = strlen(prefix);
    for (int i = len - 1; i >= 0; i--) {
        if (isDigit(prefix[i])) {
            double num = 0;
            int decimal = 0;
            double frac = 0.1;
            while (i >= 0 && (isDigit(prefix[i]) || prefix[i] == '.')) {
                if (prefix[i] == '.') {
                    decimal = 1;
                } else if (decimal) {
                    num = num + (prefix[i] - '0') * frac;
                    frac /= 10;
                } else {
                    num = num * 10 + (prefix[i] - '0');
                }
                i--;
            }
            valueStack[++valueTop] = num;
            i++;
        } else if (prefix[i] == ' ') {
            continue;
        } else if (isOperator(prefix[i])) {
            double operand1 = valueStack[valueTop--];
            double operand2 = valueStack[valueTop--];
            switch (prefix[i]) {
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
    char prefix[MAX_STACK_SIZE];

    printf("Enter an infix expression: ");
    strcpy(infix, "((2+3)*4)/5");

    // Remove newline character from input
    int len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }

    infixToPrefix(infix, prefix);
    printf("Prefix Expression: %s\n", prefix);

    double result = evaluatePrefix(prefix);
    printf("Result: %f\n", result);

    return 0;
}
