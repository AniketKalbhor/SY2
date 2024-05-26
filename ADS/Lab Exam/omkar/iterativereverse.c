#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
void Reverse(struct node **head);
void insert(struct node **head, int data);
void PrintList(struct node *head);

void insert(struct node **head, int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = *head;
    *head = newnode;
}
void Reverse(struct node **head)
{
    struct node *prev = NULL;
    struct node *current = *head;
    struct node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}
void PrintList(struct node *head)
{
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
int main()
{
    struct node *head = NULL;
    insert(&head, 5);
    insert(&head, 4);
    insert(&head, 3);
    insert(&head, 2);
    insert(&head, 1);
    printf("Original linked list:\n");
    PrintList(head);
    Reverse(&head);
    printf("\nReversed linked list:\n");
    PrintList(head);

    return 0;
}