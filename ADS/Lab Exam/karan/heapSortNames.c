#include <stdio.h>
#include <stdlib.h>

struct student
{
    int rno;
    char names[20];
} arr[10], temp;

void accept_details(int n)
{
    printf("Enter the roll number followed by name\n");

    for (int i = 0;i < n;i++)
    {
        scanf("%d",&arr[i].rno);
        scanf("%s",&arr[i].names);
    }
}

void print_details(int n)
{
        for (int i = 0;i < n;i++)
    {
        printf("%d \n",arr[i].rno);
        printf("%s \n",arr[i].names);
    }
}
void create_maxheap_rno(struct student arr[10],int i,int n)
{
    int largest=i;
    int left=2*i+1;
    int right = 2*i+2;

    if (left<n &&  arr[left].rno>arr[largest].rno){
        largest=left;
    }

     if (right<n &&  arr[right].rno>arr[largest].rno){
        largest=right;
    }
    if(i != largest)
    {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        create_maxheap_rno(arr, largest, n);
    }
}

void heapsort_rno(struct student arr[10], int n){
    for(int i = n/2-1;i>=0;i--){
        create_maxheap_rno(arr,i,n);
    }

    for (int i = n -1;i > 0;i--)
    {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        create_maxheap_rno(arr, 0, i);
    }
}

int main()
{
    accept_details(5);
    printf("accepted details:\n\n");
    print_details(5);
    printf("\n\n");

    heapsort_rno(arr, 5);
    printf("sorted details:\n\n");
    print_details(5);
}
