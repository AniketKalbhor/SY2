#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char student_name[50];
    int student_roll_no;
    int total_marks;
};

void heapify(struct Student arr[], int n, int i, int *swapCount)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no)
    {
        largest = left;
    }

    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no)
    {
        largest = right;
    }

    if (largest != i)
    {
        struct Student temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        (*swapCount)++;

        heapify(arr, n, largest, swapCount);
    }
}
void heapSort(struct Student arr[], int n, int *swapCount)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, swapCount);
    }

    for (int i = n - 1; i > 0; i--)
    {
        struct Student temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        (*swapCount)++;

        heapify(arr, i, 0, swapCount);
    }
}

void merge(struct Student arr[], int left, int middle, int right, int *swapCount)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    struct Student *leftArray = (struct Student *)malloc(n1 * sizeof(struct Student));
    struct Student *rightArray = (struct Student *)malloc(n2 * sizeof(struct Student));

    for (i = 0; i < n1; i++)
    {
        leftArray[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++)
    {
        rightArray[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (leftArray[i].student_roll_no <= rightArray[j].student_roll_no)
        {
            arr[k] = leftArray[i];
            i++;
        }
        else
        {
            arr[k] = rightArray[j];
            j++;
            (*swapCount) += (middle - left + 1 - i);
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
    free(leftArray);
    free(rightArray);
}
void mergeSort(struct Student arr[], int left, int right, int *swapCount)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSort(arr, left, middle, swapCount);
        mergeSort(arr, middle + 1, right, swapCount);

        merge(arr, left, middle, right, swapCount);
    }
}
void displayArray(struct Student arr[], int n)
{
    printf("Roll No\t\tName\t\tTotal Marks\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%s\t\t%d\n", arr[i].student_roll_no, arr[i].student_name, arr[i].total_marks);
    }
}

int main()
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));

    printf("Enter student details:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Student %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &students[i].student_roll_no);
        printf("Name: ");
        scanf("%s", students[i].student_name);
        printf("Total Marks: ");
        scanf("%d", &students[i].total_marks);
    }

    struct Student *heapSortArray = (struct Student *)malloc(n * sizeof(struct Student));
    struct Student *mergeSortArray = (struct Student *)malloc(n * sizeof(struct Student));
    memcpy(heapSortArray, students, n * sizeof(struct Student));
    memcpy(mergeSortArray, students, n * sizeof(struct Student));

    int heapSortSwapCount = 0;
    int mergeSortSwapCount = 0;

    heapSort(heapSortArray, n, &heapSortSwapCount);
    printf("\nSorted array using Heap Sort:\n");
    displayArray(heapSortArray, n);
    printf("Number of swaps in Heap Sort: %d\n", heapSortSwapCount);

    mergeSort(mergeSortArray, 0, n - 1, &mergeSortSwapCount);
    printf("\nSorted array using Merge Sort:\n");
    displayArray(mergeSortArray, n);
    printf("Number of swaps in Merge Sort: %d\n", mergeSortSwapCount);

    free(students);
    free(heapSortArray);
    free(mergeSortArray);

    return 0;
}
