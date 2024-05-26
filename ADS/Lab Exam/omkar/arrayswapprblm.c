#include <stdio.h>

void findSwappedPair(int arr[], int n)
{
    int first, second;

    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            first = i;
            break;
        }
    }

    for (int i = n - 1; i > 0; i--)
    {
        if (arr[i] < arr[i - 1])
        {
            second = i;
            break;
        }
    }

    printf("Swapped elements: %d and %d\n", arr[first], arr[second]);
    printf("Positions: %d and %d\n", first + 1, second + 1);
}

int main()
{
    int arr[] = {0, 1, 2, 9, 4, 5, 6, 7, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    findSwappedPair(arr, n);

    return 0;
}
