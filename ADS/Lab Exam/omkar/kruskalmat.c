#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <limits.h>
#define vertices 5
#define MAX 100
int n;
void kruskals(int A[vertices][vertices], int n);
void unions(int i, int j);
int findpar(int i);
int par[10];
int main()
{
    int adj[vertices][vertices];
    int maxE, i, origin, destin, weight;
    printf("Enter the total number of vertices : ");
    scanf("%d", &n);
    maxE = n * (n - 1) / 2;
    for (i = 0; i < maxE; i++)
    {
        printf("\nEnter edge [ %d ] and ( -1 -1 to quit ) : ", i);
        scanf("%d %d", &origin, &destin);
        if ((origin == -1) && (destin == -1))
            break;
        if (origin >= n || destin >= n || origin < 0 || destin < 0)
        {
            printf("\nInvalid vertex!\n");
            i--;
        }
        else
        {
            printf("Enter weight :");
            scanf("%d", &weight);
            adj[origin][destin] = weight;
            adj[destin][origin] = weight;
        }
    }
    kruskals(adj, n);
    return 0;
}
void kruskals(int A[vertices][vertices], int n)
{
    int a, b, i, j, min = INT_MAX, ne = 0, cost = 0;
    for (i = 0; i < n; i++)
    {
        par[i] = i;
    }
    while (ne < n - 1)
    {
        min = INT_MAX;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (findpar(i) != findpar(j) && A[i][j] < min)
                {
                    min = A[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        unions(a, b);
        printf("Edge %d:(%d, %d) cost:%d \n", ne++, a, b, min);
        cost += min;
    }
}
int findpar(int i)
{
    while (par[i] != 1)
    {
        i = par[i];
        return i;
    }
}
void unions(int i, int j)
{
    int x, y;
    x = findpar(i);
    y = findpar(j);
    par[x] = y;
}