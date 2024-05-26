#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    int lbit, rbit;
    struct node *left, *right;
};
struct node *TBTcreate(struct node *head, int data);
void preorderTBT(struct node *head);
void inorderTBT(struct node *head);
void postorderTBT(struct node *head);
struct node *inorder_succ(struct node *T);
int main()
{
    struct node *head;
    head = (struct node *)malloc(sizeof(struct node));
    int key, n;
    head->lbit = head->rbit = 1;
    head->left = head->right = head;
    head = TBTcreate(head, 10);
    head = TBTcreate(head, 6);
    head = TBTcreate(head, 15);
    head = TBTcreate(head, 20);
    head = TBTcreate(head, 17);
    printf("Prorder traversal : ");
    preorderTBT(head);
    printf("\ninrder traversal : ");
    inorderTBT(head);
    printf("\npostrder traversal : ");
    postorderTBT(head->left);
}
struct node *TBTcreate(struct node *head, int data)
{
    struct node *temp, *p, *q;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->lbit = temp->rbit = 0;
    if (head->left == head)
    {
        temp->left = head;
        temp->right = head;
        head->left = temp;
        return head;
    }
    p = head->left;
    while (1)
    {
        if (data < p->data && p->lbit == 1)
        {
            p = p->left;  
        }
        else if (data > p->data && p->rbit == 1)
        {
            p = p->right;
        }
        else
        {
            break;
        }
    }
    q = p;
    if (data > q->data)
    {
        temp->right = q->right;
        temp->left = q;
        q->right = temp;
        q->rbit = 1;
    }
    else
    {
        temp->left = q->left;
        temp->right = q;
        q->left = temp;
        q->lbit = 1;
    }
    return head;
}
void preorderTBT(struct node *head)
{
    struct node *T;
    T = head->left;
    while (T != head)
    {
        printf("%d ", T->data);
        if (T->lbit == 1)
        {
            T = T->left;
        }
        else if (T->rbit == 1)
        {
            T = T->right;
        }
        else
        {
            while (T->rbit == 0)
            {
                T = T->right;
            }
            T = T->right;
        }
    }
}
void inorderTBT(struct node *head)
{
    struct node *T;
    T = head->left;
    while (T->lbit == 1)
    {
        T = T->left;
    }
    while (T != head)
    {
        printf("%d ", T->data);
        T = inorder_succ(T);
    }
    return;
}
struct node *inorder_succ(struct node *T)
{
    if (T->rbit == 0)
    {
        return (T->right);
    }
    if (T->rbit == 1)
    {
        T = T->right;
        while (T->lbit == 1)
        {
            T = T->left;
        }
        return T;
    }
}
void postorderTBT(struct node *head)
{
    if (head->lbit == 1)
    {
        postorderTBT(head->left);
    }
    if (head->rbit == 1)
    {
        postorderTBT(head->right);
    }
    printf("%d ", head->data);
    return;
}