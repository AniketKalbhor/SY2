#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 50

char operatorstack[MAX_STACK_SIZE];
int top = -1;
void pushoperator(char op);
int popOp();
int precedence(char op);
void InfixtoPostfix(const char *infix, char *postfix);
double EvaluatePostfix(const char *postfix);
double EvaluatePostfix(const char *postfix)
{
    double stack[MAX_STACK_SIZE];
    int top = -1;
    int i = 0;
    while (postfix[i])
    {
        if (isdigit(postfix[i]) || (postfix[i] == '-' && isdigit(postfix[i + 1])))
        {
            char *endptr;
            double num = strtod(&postfix[i], &endptr);
            i = endptr - postfix - 1;
            stack[++top] = num;
        }
        else if (postfix[i] == ' ')
        {
        }
        else
        {
            double operand2 = stack[top--];
            double operand1 = stack[top--];
            switch (postfix[i])
            {
            case '+':
                stack[++top] = operand1 + operand2;
                break;
            case '-':
                stack[++top] = operand1 - operand2;
                break;
            case '*':
                stack[++top] = operand1 * operand2;
                break;
            case '/':
                stack[++top] = operand1 / operand2;
                break;

            default:
                break;
            }
        }
        i++;
    }
    return stack[0];
}
void InfixtoPostfix(const char *infix, char *postfix)
{
    int i, j = 0;
    for (i = 0; infix[i]; i++)
    {
        if (isdigit(infix[i]))
        {
            while (isdigit(infix[i]) || infix[i] == '.')
            {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (infix[i] == '(')
        {
            pushoperator('(');
        }
        else if (infix[i] == ')')
        {
            while (top >= 0 && operatorstack[top] != '(')
            {
                postfix[j++] = popOp();
                postfix[j++] = ' ';
            }
            if (top >= 0 && operatorstack[top] == '(')
            {
                popOp();
            }
        }
        else
        {
            while (top >= 0 && precedence(operatorstack[top]) >= precedence(infix[i]))
            {
                postfix[j++] = popOp();
                postfix[j++] = ' ';
            }
            pushoperator(infix[i]);
        }
    }
    while (top >= 0)
    {
        postfix[j++] = popOp();
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}
void pushoperator(char op)
{
    if (top < MAX_STACK_SIZE - 1)
    {
        operatorstack[++top] = op;
    }
    else
    {
        printf("Stack overflow");
        exit(1);
    }
}
int popOp()
{
    if (top >= 0)
    {
        return operatorstack[top--];
    }
    else
    {
        printf("Stack underflow");
        exit(1);
    }
}
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}
int main()
{
    char infix[100];
    char postfix[100];
    printf("Enter an infix expression : ");
    gets(infix);
    InfixtoPostfix(infix, postfix);
    printf("\nPostfix Expression is %s\n", postfix);

    double result = EvaluatePostfix(postfix);
    printf("Result: %f\n", result);

    return 0;
}