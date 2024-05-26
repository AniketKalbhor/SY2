//  WAP to implement following by using stack A. Factorial of a given number B. Generation of Fibonacci series
#include <stdio.h>
#include <stdlib.h>

int main(){
    int choice, n, i, j, k, top = -1;
    long long int fact = 1, fib[100], stack[100];
    printf("1. Factorial of a given number\n2. Generation of Fibonacci series\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice){
        case 1:
            printf("Enter the number: ");
            scanf("%d", &n);
            for (i = 1; i <= n; i++){
                fact *= i;
            }
            printf("Factorial of %d is %lld\n", n, fact);
            break;
        case 2:
            printf("Enter the number of terms: ");
            scanf("%d", &n);
            fib[0] = 0;
            fib[1] = 1;
            for (i = 2; i < n; i++){
                fib[i] = fib[i - 1] + fib[i - 2];
            }
            printf("Fibonacci series: ");
            for (i = 0; i < n; i++){
                printf("%lld ", fib[i]);
            }
            printf("\n");
            break;
        default:
            printf("Invalid choice\n");
    }
    return 0;
}