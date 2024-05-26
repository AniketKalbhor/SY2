#include <stdio.h>
#include <stdlib.h>

struct student
{
    int rno;
    char names[20];
};

void accept_details(struct student arr[], int n)
{
    printf("Enter the roll number followed by name:\n");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &arr[i].rno);
        scanf("%s", arr[i].names);
    }
}

void print_details(const struct student arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d %s\n", arr[i].rno, arr[i].names);
    }
}

int partition(struct student arr[], int low, int high)
{
    int pivot = arr[low].rno;
    int left = low + 1;
    int right = high;

    while (left <= right)
    {
        while (left <= right && arr[left].rno < pivot)
            left++;
        while (left <= right && arr[right].rno > pivot)
            right--;

        if (left < right)
        {
            struct student temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }

    struct student temp = arr[low];
    arr[low] = arr[right];
    arr[right] = temp;

    return right;
}

void quickSort(struct student arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main()
{
    int n = 5;
    struct student arr[n];

    accept_details(arr, n);
    printf("\nStudent details before sorting:\n");
    print_details(arr, n);

    quickSort(arr, 0, n - 1);

    printf("\nStudent details after sorting:\n");
    print_details(arr, n);

    return 0;
}
