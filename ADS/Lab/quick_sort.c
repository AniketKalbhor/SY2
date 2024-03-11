#include <stdio.h>

struct student
{
    int rno;
    char names[20];
};

void accept_details(struct student arr[], int n)
{
    printf("Enter the roll number followed by name\n");

    for (int i = 0; i < n+1; i++)
    {
        scanf("%d", &arr[i].rno);
        scanf("%s", arr[i].names);
    }
}

void print_details(struct student arr[], int n)
{
    for (int i = 0; i < n+1; i++)
    {
        printf("%d ", arr[i].rno);
        printf("%s\n", arr[i].names);
    }
}

void swap(struct student x, struct student y){
    struct student temp = x;
    x = y;
    y = temp;
}

int partition(struct student arr[], int low, int high){
    int pivot = low;
    int i = low+1;
    int j = high;
    while (i<high)
    {
        while (i<=j)
            if(arr[i].rno<arr[pivot].rno)
                i++;
        while (i<=j)
            if(arr[j].rno>arr[pivot].rno)
                j--;   
        if(i<j)
            swap(arr[i], arr[j]);
    }
    swap(arr[j], arr[low]);
    return j;
}

void quick_sort(struct student arr[], int low, int high){
    if (low != high)
    {
        int x = partition(arr, low, high);
        quick_sort(arr, low, x-1);
        quick_sort(arr, x+1, high);
    }
}


int main(){

    struct student arr[5];
    int n = 4;

    accept_details(arr, n);
    printf("\nAccepted details:\n");
    print_details(arr, n);
    printf("\n\n");

    quick_sort(arr, 0, n);
    printf("\nSorted details:\n");
    print_details(arr, n);

    return 0;
}