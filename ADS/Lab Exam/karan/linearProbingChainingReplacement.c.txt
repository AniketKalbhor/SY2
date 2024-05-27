#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int hashTable[SIZE];
int chain[SIZE];

int hashFunction(int key)
{
    return key%SIZE;
}

int insert(int key)
{
    int hashIndex = hashFunction(key);
    int originalIndex = hashIndex;
    int collisions = 0;

    if (hashTable[hashIndex] == -1)
    {
        hashTable[hashIndex] = key;
    }

    else
    {
        collisions++;

        while (hashTable[hashIndex] != -1)
        {
            int temp = hashTable[hashIndex];
            hashTable[hashIndex] = key;
            key = temp;

            hashIndex = (hashIndex + 1)%SIZE;

            if (hashIndex == originalIndex)
            {
                printf("Hash table is full\n");
                return -1;
            }
            collisions++;
        }

        hashTable[hashIndex] = key;

        while (chain[originalIndex] != -1)
        {
            originalIndex = chain[originalIndex];
        }
        chain[originalIndex] = hashIndex;
    }

    return collisions;
}

void printHashTable() {
    for (int i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);
        if (hashTable[i] != 0) {
            printf("%d", hashTable[i]);
        } else {
            printf("NULL");
        }

        if (chain[i] != -1) {
            printf(" -> %d", chain[i]);
        }
        printf("\n");
    }
}

int main() {
    // Initialize hash table and chain array
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = -1;
        chain[i] = -1;
    }

    int choice, key, collisions;

    while (1) {
        printf("\n1. Insert a key");
        printf("\n2. Display Hash Table");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                collisions = insert(key);
                if (collisions == -1) {
                    printf("Unable to insert key %d. Table might be full.\n", key);
                } else {
                    printf("Inserted %d with %d collisions.\n", key, collisions);
                }
                break;
            case 2:
                printf("\nHash Table:\n");
                printHashTable();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}
