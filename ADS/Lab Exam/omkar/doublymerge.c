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
struct Node *mergeSortedLists(struct Node *list1, struct Node *list2)
{
    struct Node *result = NULL;
    struct Node *temp;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data < list2->data)
        {
            if (result == NULL)
            {
                result = createNode(list1->data);
                temp = result;
            }
            else
            {
                temp->next = createNode(list1->data);
                temp->next->prev = temp;
                temp = temp->next;
            }
            list1 = list1->next;
        }
        else
        {
            if (result == NULL)
            {
                result = createNode(list2->data);
                temp = result;
            }
            else
            {
                temp->next = createNode(list2->data);
                temp->next->prev = temp;
                temp = temp->next;
            }
            list2 = list2->next;
        }
    }
    while (list1 != NULL)
    {
        temp->next = createNode(list1->data);
        temp->next->prev = temp;
        temp = temp->next;
        list1 = list1->next;
    }

    while (list2 != NULL)
    {
        temp->next = createNode(list2->data);
        temp->next->prev = temp;
        temp = temp->next;
        list2 = list2->next;
    }

    return result;
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
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    struct Node *mergedList = NULL;

    insertAtEnd(&list1, 1);
    insertAtEnd(&list1, 3);
    insertAtEnd(&list1, 5);

    insertAtEnd(&list2, 2);
    insertAtEnd(&list2, 4);
    insertAtEnd(&list2, 6);
    printf("List 1: ");
    display(list1);

    printf("List 2: ");
    display(list2);
    mergedList = mergeSortedLists(list1, list2);
    printf("Merged List: ");
    display(mergedList);

    freeList(&list1);
    freeList(&list2);
    freeList(&mergedList);

    return 0;
}
