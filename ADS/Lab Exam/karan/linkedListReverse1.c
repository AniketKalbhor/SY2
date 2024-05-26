#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* insertAtEnd(struct Node* head, int key)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));

    p->data = key;
    p->next = NULL;

    if (head == NULL)
    {
        return p;
    }

    struct Node* q = head;

    while(q->next != NULL)
    {
        q = q->next;
    }

    q->next = p;

    return head;
};

struct Node* reverseList(struct Node* head)
{
    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* newNode = NULL;

    while (current != NULL)
    {
        newNode = current->next;
        current->next = prev;
        prev = current;
        current = newNode;
    }

    return prev;
};

int main()
{
    struct Node* head = NULL;

    head = insertAtEnd(head, 1);
    head = insertAtEnd(head, 2);
    head = insertAtEnd(head, 3);
    head = insertAtEnd(head, 4);
    head = insertAtEnd(head, 5);

    head = reverseList(head);

    struct Node* current = head;

    while(current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
}
