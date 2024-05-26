#include <stdio.h>
#include <stdlib.h>

void create_max_heap(int arr[], int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (i != largest) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        create_max_heap(arr, largest, n);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        create_max_heap(arr, i, n);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        create_max_heap(arr, 0, i);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size;
    printf("Enter the size of the array\n");
    scanf("%d", &size);
    int arr[size];

    printf("Enter the elements of the array\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array:\n");
    printArray(arr, size);

    heapSort(arr, size);

    printf("Sorted array:\n");
    printArray(arr, size);

    return 0;
}
