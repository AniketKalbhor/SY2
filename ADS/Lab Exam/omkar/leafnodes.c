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
int count = 0;
void push(struct node *root, struct stack **top);
struct node *pop(struct stack **top);
struct node *create(int data);
struct node *insert(struct node *root, int data);
int emptystack();
int emptystacks(struct stack *top);
void preorder(struct node *T);
void inorder(struct node *T);
void postorder(struct node *T);
int findHeight(struct node *);
void displayleaf(struct node *root);
void displayleaf(struct node *root)
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
            printf("%d ", current->data); // Add a space after printing the data
        }
        current = current->right;
    }
    printf("\n"); // Add a newline character after printing all leaf nodes
}

int findHeight(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    struct node *queue[30];
    int front = 0, rear = 0;
    int currentLev = 1;
    int nextLev = 0;
    int height = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        struct node *current = queue[front++];
        printf("%d ", current->data);
        currentLev--;
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
            nextLev++;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
            nextLev++;
        }
        if (currentLev == 0)
        {
            printf("\n");
            height++;
            currentLev = nextLev;
            nextLev = 0;
        }
    }
    return height - 1;
}
void preorder(struct node *T)
{
    while (T != NULL || !emptystack())
    {
        while (T != NULL)
        {
            printf("%d", T->data);
            push(T, &top);
            T = T->left;
        }

        if (!emptystack())
        {
            T = pop(&top);
            T = T->right;
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
    root = insert(root, 5);
    root = insert(root, 12);
    printf("\nPreorder Traversal : ");
    preorder(root);
    printf("\nInorder Traversal : ");
    inorder(root);
    printf("\nPostorder Traversal : ");
    postorder(root);
    printf("\n");
    int height = findHeight(root);
    printf("\nHeight of the tree is %d", height);
    printf("\nTotal number of nodes are %d", count);
    printf("\nLeaf nodes are :");
    displayleaf(root);
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
    count += 1;
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