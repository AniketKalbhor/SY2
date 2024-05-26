#include <stdio.h>
#include <stdlib.h>
struct poly
{
    int coeff;
    int expon;
    struct poly *next;
};
typedef struct poly poly;
poly *create(int coefficient, int exponent);
void insertterm(poly **poly, int coefficient, int exponent);
poly *addpolynomials(poly *poly1, poly *poly2);
void displayPolynomial(poly *poly);
poly *create(int coefficient, int exponent)
{
    poly *poly = (struct poly *)malloc(sizeof(struct poly));
    poly->coeff = coefficient;
    poly->expon = exponent;
    poly->next = NULL;
    return poly;
}
void insertterm(poly **poly1, int coefficient, int exponent)
{
    poly *newpoly = create(coefficient, exponent);
    if (*poly1 == NULL)
    {
        *poly1 = newpoly;
    }
    else
    {
        poly *current = *poly1;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newpoly;
    }
}
poly *addpolynomials(poly *poly1, poly *poly2)
{
    poly *result = NULL;
    while (poly1 != NULL && poly2 != NULL)
    {
        if (poly1->expon > poly2->expon)
        {
            insertterm(&result, poly1->coeff, poly1->expon);
            poly1 = poly1->next;
        }
        else if (poly1->expon < poly2->expon)
        {
            insertterm(&result, poly2->coeff, poly2->expon);
            poly2 = poly2->next;
        }
        else
        {
            int sum_coeff = poly1->coeff + poly2->coeff;
            if (sum_coeff != 0)
            {
                insertterm(&result, sum_coeff, poly1->expon);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL)
    {
        insertterm(&result, poly1->coeff, poly1->expon);
        poly1 = poly1->next;
    }
    while (poly2 != NULL)
    {
        insertterm(&result, poly2->coeff, poly2->expon);
        poly2 = poly2->next;
    }
    return result;
}
void displayPolynomial(poly *poly)
{
    if (poly == NULL)
    {
        printf("0\n");
        return;
    }
    while (poly != NULL)
    {
        printf("%dx^%d", poly->coeff, poly->expon);
        poly = poly->next;
        if (poly != NULL)
        {
            printf("+");
        }
    }
    printf("\n");
}
int main()
{
    poly *poly1 = NULL;
    poly *poly2 = NULL;
    int n1, n2, coeff, exp;
    printf("Enter the number of terms for polynomial 1 :");
    scanf("%d", &n1);
    printf("Enter the terms for polynomial 1 (coefficient exponent):\n");
    for (int i = 0; i < n1; i++)
    {
        scanf("%d %d", &coeff, &exp);
        insertterm(&poly1, coeff, exp);
    }
    printf("Enter the number of terms for polynomial 2 :");
    scanf("%d", &n2);
    printf("Enter the terms for polynomial 2 (coefficient exponent):\n");
    for (int i = 0; i < n2; i++)
    {
        scanf("%d %d", &coeff, &exp);
        insertterm(&poly2, coeff, exp);
    }
    printf("\nPolynomial 1 :");
    displayPolynomial(poly1);
    printf("\nPolynomial 2 :");
    displayPolynomial(poly2);

    poly *result = addpolynomials(poly1, poly2);
    printf("\nResultant polynomial :");
    displayPolynomial(result);

    free(poly1);
    free(poly2);
    free(result);
    return 0;
}