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
};

struct Node* mergeLists(struct Node* head1, struct Node* head2)
{
    if (head1 == NULL)
    {
        return head2;
    }

    if (head2 == NULL)
    {
        return head1;
    }

    struct Node* mergedHead = NULL;
    struct Node* tail = NULL;

    if (head1->data <= head2->data)
    {
        mergedHead = head1;
        head1 = head1->next;
    }

    else
    {
        mergedHead = head2;
        head2 = head2->next;
    }

    tail = mergedHead;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data <= head2->data)
        {
            tail->next = head1;
            head1->prev = tail;
            head1 = head1->next;
        }

        else
        {
            tail->next = head2;
            head2->prev = tail;
            head2 = head2->next;
        }

        tail = tail->next;
    }

    while (head1 != NULL)
    {
        tail->next = head1;
        head1->prev = tail;
        head1 = head1->next;
        tail = tail->next;
    }

    while (head2 != NULL)
    {
        tail->next = head2;
        head2->prev = tail;
        head2 = head2->next;
        tail = tail->next;
    }

    return mergedHead;
};

void displayList(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* p = head;

    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    struct Node* mergedHead = NULL;

    head1 = insertAtEnd(head1, 1);
    head1 = insertAtEnd(head1, 3);
    head1 = insertAtEnd(head1, 5);

    displayList(head1);

    head2 = insertAtEnd(head2, 2);
    head2 = insertAtEnd(head2, 4);
    head2 = insertAtEnd(head2, 6);

    displayList(head2);

    mergedHead = mergeLists(head1, head2);

    displayList(mergedHead);
}
