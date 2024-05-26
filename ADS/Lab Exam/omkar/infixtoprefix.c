#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 50

char operatorstack[MAX_STACK_SIZE];
int top = -1;
void pushOperator(char op);
int popOp();
int precedence(char op);
void InfixToPrefix(const char *infix, char *prefix);
double EvaluatePrefix(const char *prefix);
void ReverseString(char *str);

double EvaluatePrefix(const char *prefix)
{
    double stack[MAX_STACK_SIZE];
    int top = -1;
    int i = strlen(prefix) - 1;
    while (i >= 0)
    {
        if (isdigit(prefix[i]) || (prefix[i] == '.' && isdigit(prefix[i - 1])))
        {
            char *endptr;
            double num = strtod(&prefix[i], &endptr);
            i -= endptr - prefix - i;
            stack[++top] = num;
        }
        else if (prefix[i] == ' ')
        {
        }
        else
        {
            double operand2 = stack[top--];
            double operand1 = stack[top--]; // Switched the order of operands
            switch (prefix[i])
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
        i--;
    }
    return stack[0];
}

void InfixToPrefix(const char *infix, char *prefix)
{
    int i, j = 0;
    char reversedInfix[100];
    ReverseString(strcpy(reversedInfix, infix));

    for (i = 0; reversedInfix[i];)
    {
        if (reversedInfix[i] == '(')
        {
            reversedInfix[i] = ')';
            i++;
        }
        else if (reversedInfix[i] == ')')
        {
            reversedInfix[i] = '(';
            i++;
        }
        else if (isdigit(reversedInfix[i]) || isalpha(reversedInfix[i]))
        {
            while (isdigit(reversedInfix[i]) || reversedInfix[i] == '.' || isalpha(reversedInfix[i]))
            {
                prefix[j++] = reversedInfix[i++];
            }
            prefix[j++] = ' ';
        }
        else if (reversedInfix[i] == '(')
        {
            pushOperator('(');
            i++;
        }
        else if (reversedInfix[i] == ')')
        {
            while (top >= 0 && operatorstack[top] != '(')
            {
                prefix[j++] = popOp();
                prefix[j++] = ' ';
            }
            if (top >= 0 && operatorstack[top] == '(')
            {
                popOp();
            }
            i++;
        }
        else
        {
            while (top >= 0 && precedence(operatorstack[top]) > precedence(reversedInfix[i]))
            {
                prefix[j++] = popOp();
                prefix[j++] = ' ';
            }
            pushOperator(reversedInfix[i]);
            i++;
        }
    }

    while (top >= 0)
    {
        prefix[j++] = popOp();
        prefix[j++] = ' ';
    }
    prefix[j] = '\0';
    ReverseString(prefix);
}

void ReverseString(char *str)
{
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right)
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}
void pushOperator(char op)
{
    if (top < MAX_STACK_SIZE - 1)
    {
        operatorstack[++top] = op;
    }
    else
    {
        printf("Stack Overflow");
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
        printf("Stack undeflow");
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
    char prefix[100];
    printf("Enter the infix expression : ");
    gets(infix);
    InfixToPrefix(infix, prefix);
    printf("\nPrefix expression is %s\n", prefix);
    float result = EvaluatePrefix(prefix);
    printf("Result is %f\n", result);
    return 0;
}