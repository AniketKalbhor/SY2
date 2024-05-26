
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct stack
{
    struct node *T;
    struct stack *next;
};
int count = 0;
struct stack *top;
struct node *insert(struct node *root, int data);
struct node *newnode(int data);
void preorder(struct node *T);
void inorder(struct node *T);
void postorder(struct node *T);
void push(struct node *root, struct stack **top);
struct node *pop(struct stack **top);
void displayLeafNodes(struct node *root);
int emptystack();
int main()
{
    struct node *root = NULL;
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    printf("\n Preorder Traversal : ");
    preorder(root);
    printf("\n Total nodes :");
    printf("%d", count);
    printf("\n Leaf nodes :");
    displayLeafNodes(root);
    return 0;
}
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        root = newnode(data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    else if (data <= root->data)
    {
        root->left = insert(root->left, data);
    }
    return root;
}
struct node *newnode(int data)
{
    count = count + 1;
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
void preorder(struct node *T)
{
    while (T != NULL)
    {
        printf("%d ", T->data);
        push(T, &top);
        T = T->left;
    }
    while (!emptystack())
    {
        T = pop(&top);
        T = T->right;
        while (T != NULL)
        {
            printf("%d ", T->data);
            push(T, &top);
            T = T->left;
        }
    }
}
void push(struct node *root, struct stack **top)
{
    struct stack *temp;
    temp = (struct stack *)malloc(sizeof(struct stack));
    temp->T = root;
    temp->next = *top;
    *top = temp;
}
struct node *pop(struct stack **top)
{
    struct node *p;
    struct stack *temp;
    if (*top == NULL)
    {
        return NULL;
    }
    else
    {
        temp = *top;
        *top = temp->next;
        p = temp->T;
        free(temp);
        return p;
    }
}
int emptystack()
{
    if (top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void displayLeafNodes(struct node *root)
{
    if (root == NULL)
        return;

    struct stack *stack = NULL;
    struct node *current = root;

    while (1)
    {
        while (current)
        {
            push(current, &stack);
            current = current->left;
        }

        if (!emptystack())
        {
            break;
        }

        current = pop(&stack);
        if (!current->left && !current->right)
        {
            printf("%d ", current->data);
        }

        current = current->right;
    }
}