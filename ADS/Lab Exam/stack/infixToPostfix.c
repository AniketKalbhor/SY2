//WAP to convert a given Infix expression into its equivalent Postfix expression and evaluate it using stack
// precedence of operators: ^ > * = / > + = -
// pop if precedence of operator in stack is greater than or equal to precedence of operator in infix expression, or we encounter ')'

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pop (char stack[], int *top){
    if (*top == -1){
        printf("Stack underflow\n");
        exit(0);
    }
    return stack[(*top)--];
}

void push (char stack[], int *top, char ch){
    if (*top == 99){
        printf("Stack overflow\n");
        exit(0);
    }
    stack[++(*top)] = ch;
}

int precedence (char ch){
    if (ch == '^')
        return 3;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

int main(){
    char infix[100], postfix[100], stack[100];
    int top = -1;
    printf("Enter the infix expression: ");
    scanf("%s", infix);
    int i = 0, j = 0;
    while (infix[i] != '\0'){
        if (infix[i] == '('){
            push(stack, &top, infix[i]);
        }
        else if (infix[i] == ')'){
            while (stack[top] != '('){
                postfix[j++] = pop(stack, &top);
            }
            postfix[j++] = pop(stack, &top);
        }
        else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^'){
            while (precedence(stack[top]) >= precedence(infix[i])){
                postfix[j++] = pop(stack, &top);
            }
            push(stack, &top, infix[i]);
        }
        else{
            postfix[j++] = infix[i];
        }
        i++;
    }
    while (top != -1){
        postfix[j++] = pop(stack, &top);
    }
    printf("Postfix expression: %s\n", postfix);
}