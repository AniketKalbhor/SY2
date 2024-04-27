#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

int hashTable[TABLE_SIZE] = {0};


void displayHashTable() {
    printf("\n*******************************************\n");
    printf("Hash Table:\n");
    printf("Index\tValue\n");
    for (int i = 0; i < TABLE_SIZE; i++)
        printf("%d\t%d\n", i, hashTable[i]);
}

void insert()
{
    int key, index, i, flag = 0, hashkey;

    printf("Enter value to be inserted in hash table: ");
    scanf("%d",&key);

    hashkey = key%TABLE_SIZE;

    for(i = 0;i < TABLE_SIZE;i++)
    {
        index = (hashkey+i)%TABLE_SIZE;

        if (hashTable[index] == 0)
        {
            hashTable[index] = key;
            printf("Element inserted at index %d\n", index);
            break;
        }
    }

    if (i == TABLE_SIZE)
    {
        printf("Element can't be inserted\n");
    }
}

int main() {

    int choice;
    do {
        printf("\n1. Insert\t");
        printf("2. Display\t");
        printf("3. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert();
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
