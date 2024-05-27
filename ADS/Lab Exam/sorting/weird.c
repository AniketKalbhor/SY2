/*Assume that an array A with n elements was sorted in an ascending order, but two of its elements swapped their positions by a mistake while maintaining the array. 
Write a code to identify the swapped pair of elements and their positions in the asymptotically best possible time. [Assume that all given elements are distinct integers.*/

#include <stdio.h>

void findSwappedElements(int arr[], int n) {
    int first = -1, second = -1;
    int firstPos = -1, secondPos = -1;

    // Traverse the array to find the two swapped elements
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (first == -1) {
                first = arr[i];
                firstPos = i;
            } else {
                second = arr[i + 1];
                secondPos = i + 1;
                break;
            }
        }
    }

    // Print the results
    if (first != -1 && second != -1) {
        printf("The swapped elements are %d and %d\n", first, second);
        printf("Their positions are %d and %d\n", firstPos, secondPos);
    } else {
        printf("No swapped elements found or input array is not sorted with exactly two elements swapped.\n");
    }
}

int main() {
    int arr[] = {1, 2, 6, 4, 5, 3, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    findSwappedElements(arr, n);

    return 0;
}
