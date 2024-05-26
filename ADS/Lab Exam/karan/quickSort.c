#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while(i <= j)
    {
        while(i <= j && arr[i] < pivot)
        {
            i++;
        }

        while (i <= j && arr[j] > pivot)
        {
            j--;
        }

        if(i <= j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    int temp = arr[low];
    arr[low] = arr[j];
    arr[j] = temp;

    return j;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, 0, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main()
{
    int size;

    printf("Enter the size of the array\n");
    scanf("%d",&size);

    int arr[size];

    printf("Enter the elements of the array\n");

    for (int i = 0; i < size;i++)
    {
        scanf("%d",&arr[i]);
    }

    printf("Original array:\n");
    for (int i = 0;i < size;i++)
    {
        printf(" %d",arr[i]);
    }

    printf("\n");

    quickSort(arr, 0, size-1);

    printf("Sorted array:\n");
    for (int i = 0;i < size;i++)
    {
        printf(" %d",arr[i]);
    }
}
