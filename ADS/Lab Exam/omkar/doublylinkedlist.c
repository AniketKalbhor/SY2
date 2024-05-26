#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node **head, int value)
{
    struct Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
    printf("Inserted %d at the beginning.\n", value);
}

void insertAtEnd(struct Node **head, int value)
{
    struct Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Node *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    printf("Inserted %d at the end.\n", value);
}

void insertAfter(struct Node *prevNode, int value)
{
    if (prevNode == NULL)
    {
        printf("Previous node cannot be NULL.\n");
        return;
    }

    struct Node *newNode = createNode(value);
    newNode->next = prevNode->next;
    newNode->prev = prevNode;
    prevNode->next = newNode;

    if (newNode->next != NULL)
    {
        newNode->next->prev = newNode;
    }

    printf("Inserted %d after the given node.\n", value);
}

void deleteNode(struct Node **head, int value)
{
    if (*head == NULL)
    {
        printf("Doubly linked list is empty.\n");
        return;
    }

    struct Node *current = *head;
    struct Node *prev = NULL;

    while (current != NULL && current->data != value)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Node with value %d not found.\n", value);
        return;
    }

    if (prev == NULL)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        prev->next = current->next;
        if (current->next != NULL)
        {
            current->next->prev = prev;
        }
    }

    free(current);
    printf("Deleted node with value %d.\n", value);
}

void display(struct Node *head)
{
    printf("Doubly linked list: ");
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(struct Node **head)
{
    struct Node *current = *head;
    while (current != NULL)
    {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

int main()
{
    struct Node *head = NULL;
    int choice, value;

    do
    {
        printf("\n--- Doubly Linked List Operations ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert After a Node\n");
        printf("4. Delete a Node\n");
        printf("5. Display List\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter the value to insert at the beginning: ");
            scanf("%d", &value);
            insertAtBeginning(&head, value);
            break;
        case 2:
            printf("Enter the value to insert at the end: ");
            scanf("%d", &value);
            insertAtEnd(&head, value);
            break;
        case 3:
            printf("Enter the value to insert after: ");
            scanf("%d", &value);
            struct Node *prevNode = head;
            while (prevNode != NULL && prevNode->data != value)
            {
                prevNode = prevNode->next;
            }
            if (prevNode == NULL)
            {
                printf("Node with value %d not found.\n", value);
            }
            else
            {
                printf("Enter the value to insert after %d: ", value);
                scanf("%d", &value);
                insertAfter(prevNode, value);
            }
            break;
        case 4:
            printf("Enter the value to delete: ");
            scanf("%d", &value);
            deleteNode(&head, value);
            break;
        case 5:
            display(head);
            break;
        case 0:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    // Free memory
    freeList(&head);

    return 0;
}
