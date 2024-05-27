//       WAP to create doubly linked list and perform following operations on it. A) Insert (all cases) 2. Delete (all cases).
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* insertAtEnd(struct Node* head, int key)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));

    p->data = key;
    p->next = NULL;
    p->prev = NULL;

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
    p->next = NULL;
    p->prev = q;

    return head;
}

struct Node* insertAtFront(struct Node* head, int key)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));

    p->data = key;
    p->next = head;
    p->prev = NULL;

    if (head != NULL)
    {
        head->prev = p;
    }

    return p;
};

struct Node* insertAtIndex(struct Node* head, int index, int key)
{
    struct Node* p = (struct Node*)malloc(sizeof(struct Node));

    p->data = key;

    if (index == 0)
    {
        p->prev = NULL;
        p->next = head;
        return p;
    }

    struct Node* q = head;

    for (int i = 0;i < index;i++)
    {
        q = q->next;
    }

    if (q == NULL)
    {
        printf("Index not found\n");
        return head;
    }

    p->next = q->next;
    p->prev = q;

    if (q->next != NULL)
    {
        q->next->prev = p;
    }
    q->next = p;

    return head;

};

struct Node* deleteAtEnd(struct Node* head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }

    if (head->next == NULL)
    {
        printf("Deleted %d\n",head->data);
        free(head);
        return NULL;
    }

    struct Node* p = head;

    while(p->next != NULL)
    {
        p = p->next;
    }

    printf("Deleted %d\n",p->data);

    p->prev->next = NULL;
    free(p);
    return head;
};

struct Node* deleteAtFront(struct Node* head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }

    struct Node* p = head;

    printf("Delted %d\n",p->data);

    head = head->next;

    if (head != NULL)
    {
        head->prev = NULL;
    }

    free(p);
    return head;
};

struct Node* deleteAfterNode(struct Node* head, int key)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }

    struct Node* p = head;

    while (p->data != key)
    {
        p = p->next;
    }

    if (p == NULL)
    {
        printf("Node doesn't exist\n");
        return head;
    }

    struct Node* q = p->next;

    printf("Deleted %d\n",q->data);

    p->next = q->next;

    if (q->next != NULL)
    {
        q->next->prev = p;
    }

    free(q);
    return head;
};

void displayList(struct Node* head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct Node* p = head;

    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n\n");
}

int main()
{
    struct Node* head = NULL;
    int key;
    int n;

    while (1)
    {
        int choice;
        printf(" 1.Insert at end\n 2.Insert at beginning\n 3.Insert at index\n 4.Delete at end\n 5.Delete at front\n 6.Delete after node\n 7.Display\n 8.Exit\n\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter element to insert\n");
            scanf("%d",&key);
            head = insertAtEnd(head, key);
            break;
        case 2:
            printf("Enter element to insert\n");
            scanf("%d",&key);
            head = insertAtFront(head, key);
            break;
        case 3:
            printf("Enter index where you want to insert\n");
            scanf("%d",&n);
            printf("Enter element to insert\n");
            scanf("%d",&key);
            head = insertAtIndex(head, n, key);
            break;
        case 4:
            head = deleteAtEnd(head);
            break;
        case 5:
            head = deleteAtFront(head);
            break;
        case 6:
            printf("Enter node after which to delete\n");
            scanf("%d",&n);
            head = deleteAfterNode(head, n);
            break;
        case 7:
            displayList(head);
            break;
        case 8:
            exit(0);
            break;
        }
    }
}
