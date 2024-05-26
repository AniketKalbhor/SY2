#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *left, *right;
};
struct stack
{
    struct node *T;
    struct stack *next;
};
struct stack *top;
void push(struct node *root, struct stack **top);
struct node *pop(struct stack **top);
struct node *create(int data);
struct node *insert(struct node *root, int data);
struct node *delete(struct node *root, int data);
int emptystack();
void preorder(struct node *T);
void inorder(struct node *T);
void postorder(struct node *T);

struct node *delete(struct node *root, int data)
{
    struct node *current = root;
    struct node *parent = NULL;
    struct stack *p = NULL;
    while (current != NULL && current->data != data)
    {
        push(current, &p);
        parent = current;
        if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    if (current == NULL)
    {
        return root;
    }
    if (current->left == NULL || current->right == NULL)
    {
        struct node *temp = current->left ? current->left : current->right;
        if (temp == NULL)
        {
            temp = current;
            current = NULL;
        }
        else
        {
            current->data = temp->data;
        }
        free(temp);
    }
    else
    {
        struct node *succesor = current->right;
        while (succesor->left != NULL)
        {
            push(succesor, &p);
            parent = succesor;
            succesor = succesor->left;
        }
        current->data = succesor->data;
        if (parent != current)
        {
            parent->left = succesor->right;
        }
        else
        {
            parent->right = succesor->right;
        }
        free(succesor);
    }
    while (!emptystack())
    {
        parent = pop(&p);
        if (parent->left && parent->left->data == data)
        {
            parent->left = current;
        }
        else
        {
            parent->right = current;
        }
    }
    return root;
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
void inorder(struct node *T)
{
    while (T != NULL || !emptystack())
    {
        while (T != NULL)
        {
            push(T, &top);
            T = T->left;
        }

        if (!emptystack())
        {
            T = pop(&top);
            printf("%d", T->data);
            T = T->right;
        }
    }
}

void postorder(struct node *T)
{
    struct node *prev = NULL;
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
                printf("%d", T->data);
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
int main()
{
    struct node *root = NULL;
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 25);
    // root = insert(root, 28);
    printf("\nPreorder Traversal : ");
    preorder(root);
    printf("\nInorder Traversal : ");
    inorder(root);
    printf("\nPostorder Traversal : ");
    postorder(root);
    printf("\n");
    root = delete (root, 25);
    printf("\nPreorder Traversal : ");
    preorder(root);
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
    return top == NULL;
}
struct node *create(int data)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = data;
    new->left = new->right = NULL;
    return new;
}
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        root = create(data);
    }
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    return root;
}