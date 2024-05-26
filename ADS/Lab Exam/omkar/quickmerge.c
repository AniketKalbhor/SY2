#include <stdio.h>
#include <string.h>

struct Employee
{
    char employee_name[50];
    int emp_no;
    double emp_salary;
};
int quickSort(struct Employee arr[], int low, int high, int *swapCount)
{
    int i = low - 1;
    struct Employee pivot = arr[high];

    for (int j = low; j < high; j++)
    {
        if (arr[j].emp_no <= pivot.emp_no)
        {
            i++;
            struct Employee temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*swapCount)++;
        }
    }
    struct Employee temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    (*swapCount)++;

    return i + 1;
}

void quickSortRecursive(struct Employee arr[], int low, int high, int *swapCount)
{
    if (low < high)
    {
        int pivotIndex = quickSort(arr, low, high, swapCount);

        quickSortRecursive(arr, low, pivotIndex - 1, swapCount);
        quickSortRecursive(arr, pivotIndex + 1, high, swapCount);
    }
}
void merge(struct Employee arr[], int left, int mid, int right, int *swapCount)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Employee L[20], R[30];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].emp_no <= R[j].emp_no)
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
            (*swapCount) += (mid - left + 1) - i;
        }
    }

    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

void mergeSortRecursive(struct Employee arr[], int left, int right, int *swapCount)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid, swapCount);
        mergeSortRecursive(arr, mid + 1, right, swapCount);
        merge(arr, left, mid, right, swapCount);
    }
}

int main()
{
    int n;

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    struct Employee employees[30];
    for (int i = 0; i < n; i++)
    {
        printf("Enter details for Employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", employees[i].employee_name);
        printf("Employee Number: ");
        scanf("%d", &employees[i].emp_no);
        printf("Salary: ");
        scanf("%lf", &employees[i].emp_salary);
    }

    int quickSwapCount = 0, mergeSwapCount = 0;

    quickSortRecursive(employees, 0, n - 1, &quickSwapCount);

    printf("\nSorted array after Quick Sort:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %.2lf\n", employees[i].employee_name, employees[i].emp_no, employees[i].emp_salary);
    }
    printf("Number of swaps in Quick Sort: %d\n", quickSwapCount);

    mergeSortRecursive(employees, 0, n - 1, &mergeSwapCount);

    printf("\nSorted array after Merge Sort:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %.2lf\n", employees[i].employee_name, employees[i].emp_no, employees[i].emp_salary);
    }
    printf("Number of swaps in Merge Sort: %d\n", mergeSwapCount);

    return 0;
}
