#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int rno;
    char names[20];
} arr[10], temp;

int swaps = 0;

void accept_details(int n)
{
    printf("Enter the roll number followed by name\n");

    arr[0].rno = 2;
    strcpy(arr[0].names, "Karan");
    arr[1].rno = 1;
    strcpy(arr[1].names, "Aniket");
    arr[2].rno = 3;
    strcpy(arr[2].names, "Jannu");

}

void print_details(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d \n", arr[i].rno);
        printf("%s \n", arr[i].names);
    }
}

void create_maxheap_rno(struct student arr[10], int i, int n)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].rno > arr[largest].rno)
    {
        largest = left;
    }

    if (right < n && arr[right].rno > arr[largest].rno)
    {
        largest = right;
    }
    if (i != largest)
    {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        swaps++;

        create_maxheap_rno(arr, largest, n);
    }
}

void heapsort_rno(struct student arr[10], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        create_maxheap_rno(arr, i, n);
    }

    for (int i = n - 1; i > 0; i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        swaps++;

        create_maxheap_rno(arr, 0, i);
    }
}

int main()
{
    accept_details(3);
    printf("accepted details:\n\n");
    print_details(5);
    printf("\n\n");

    heapsort_rno(arr, 3);
    printf("sorted details:\n\n");
    print_details(3);

    printf("\nNumber of swaps performed: %d\n", swaps);

    return 0;
}
