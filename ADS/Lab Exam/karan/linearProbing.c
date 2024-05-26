#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

int hashT[TABLE_SIZE] = {NULL};

void insert()
{
    int key, index, i, flag = 0, hkey;

    printf("Enter value to be inserted in hash table\n");
    scanf("%d",&key);

    hkey = key%TABLE_SIZE;

    for(i = 0;i < TABLE_SIZE;i++)
    {
        index = (hkey+i)%TABLE_SIZE;

        if (hashT[index] == NULL)
        {
            hashT[index] = key;
            printf("Element inserted at index %d\n", index);
            break;
        }
    }

    if (i == TABLE_SIZE)
    {
        printf("Element can't be inserted\n");
    }
}

void displayHashTable() {
    printf("Hash Table:\n");
    printf("Index\tValue\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t%d\n", i, hashT[i]);
    }
}

int main() {

    int choice;
    do {
        printf("\n1. Insert\n");
        printf("2. Display\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
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
