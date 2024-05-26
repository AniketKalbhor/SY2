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
struct stack *top;
struct node *insert(struct node *root, int data);
struct node *newnode(int data);
void push(struct node *root, struct stack **top);
struct node *pop(struct stack **top);
void postorder(struct node *T);
struct node *delete(struct node *root, int data);
int emptystack();
int main()
{
    struct node *root = NULL;
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 35);
    root = insert(root, 5);
    root = insert(root, 17);
    postorder(root);
    root = delete (root, 15);
    printf("\n");
    postorder(root);
    return 0;
}
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        root = newnode(data);
    }
    else
    {
        if (data <= root->data)
        {
            root->left = insert(root->left, data);
        }
        else if (data > root->data)
        {
            root->right = insert(root->right, data);
        }
    }
    return root;
}
struct node *newnode(int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
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
void postorder(struct node *T)
{
    struct node *prev;
    do
    {
        while (T != NULL)
        {
            push(T, &top);
            T = T->left;
        }
        while (T == NULL && !emptystack())
        {
            T = top->T;
            if (T->right == NULL || T->right == prev)
            {
                printf("%d ", T->data);
                prev = T;
                pop(&top);
                T = NULL;
            }
            else
            {
                T = T->right;
            }
        }
    } while (!emptystack());
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
struct node *delete(struct node *root, int data)
{
    struct node *current = root;
    struct node *parent = NULL;
    struct stack *path = NULL; // Create a stack to keep track of the path to the node to delete

    // Search for the node to delete
    while (current != NULL && current->data != data)
    {
        push(current, &path);
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
    {
        return root;
    }

    if (current->left == NULL || current->right == NULL)
    {
        struct node *temp = current->left ? current->left : current->right;

        // No child case
        if (temp == NULL)
        {
            temp = current;
            current = NULL;
        }
        else // One child case
        {
            *current = *temp; // Copy the contents of the non-empty child
        }

        free(temp);
    }
    else // Node with two children
    {
        // Find the in-order successor (smallest node in the right subtree)
        struct node *successor = current->right;
        while (successor->left != NULL)
        {
            push(successor, &path);
            parent = successor;
            successor = successor->left;
        }
        current->data = successor->data;
        if (parent != current)
            parent->left = successor->right;
        else
            current->right = successor->right;

        free(successor);
    }

    while (!emptystack())
    {
        parent = pop(&path);
        if (parent->left && parent->left->data == data)
            parent->left = current;
        else
            parent->right = current;
    }

    return root;
}
