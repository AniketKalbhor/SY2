#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

int hashTable[TABLE_SIZE] = {0};

int hash(int key) {
    return key % TABLE_SIZE;
}

void insert(int key) {
    int index, step, i;

    index = hash(key);
    step = 1;

    for (i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[index] == 0) {
            hashTable[index] = key;
            printf("Element %d inserted at index %d\n", key, index);
            return;
        }
        index = (index + step * step) % TABLE_SIZE; 
        step++; 
    }

    printf("Hash table is full. Element %d cannot be inserted.\n", key);
}

void displayHashTable() {
    printf("\n******************************************\n");
    printf("Hash Table:\n");
    printf("Index\tValue\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("%d\t%d\n", i, hashTable[i]);
}

int main() {
    int choice, key;
    do {
        printf("\n1. Insert\t");
        printf("2. Display\t");
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
