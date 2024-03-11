#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int rno;
    char names[20];
};

void accept_details(struct student arr[], int n)
{
    printf("Enter the roll number followed by name\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i].rno);
        scanf("%s", arr[i].names);
    }
}

void print_details(struct student arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i].rno);
        printf("%s\n", arr[i].names);
    }
}

void create_maxheap_rno(struct student arr[], int i, int n)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].rno > arr[largest].rno)
        largest = left;

    if (right < n && arr[right].rno > arr[largest].rno)
        largest = right;

    if (i != largest)
    {
        struct student temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        create_maxheap_rno(arr, largest, n);
    }
}

void heapsort_rno(struct student arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        create_maxheap_rno(arr, i, n);

    for (int i = n - 1; i > 0; i--)
    {
        struct student temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        create_maxheap_rno(arr, 0, i);
    }
}

int main()
{
    struct student arr[10];
    int n = 5;

    accept_details(arr, n);
    printf("Accepted details:\n\n");
    print_details(arr, n);
    printf("\n\n");

    heapsort_rno(arr, n);
    printf("Sorted details:\n\n");
    print_details(arr, n);

    return 0;
}