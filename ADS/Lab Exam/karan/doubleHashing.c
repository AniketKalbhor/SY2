#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

int hashT[TABLE_SIZE] = {0}; // Initialize all elements to 0

int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    // Choose a prime smaller than TABLE_SIZE for best results
    return 7 - (key % 7);
}

void insert(int key) {
    int index, step, i;

    index = hash1(key);
    step = hash2(key);

    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashT[index] == 0) {
            hashT[index] = key;
            printf("Element %d inserted at index %d\n", key, index);
            return;
        }
        index = (index + step) % TABLE_SIZE;
    }

    printf("Hash table is full. Element %d cannot be inserted.\n", key);
}

void displayHashTable() {
    printf("Hash Table:\n");
    printf("Index\tValue\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t%d\n", i, hashT[i]);
    }
}

int main() {
    int choice, key;
    do {
        printf("\n1. Insert\n");
        printf("2. Display\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to be inserted in hash table: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                displayHashTable();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}
