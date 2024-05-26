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
int emptystack(struct stack *top);
struct node *create(int data);
struct node *insert(struct node *root, int data);
void preorder(struct node *T);
void inorder(struct node *T);
void postorder(struct node *T);
int findHeight(struct node *root);
struct node *image(struct node *root);

int main()
{
    struct node *root = NULL;
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    // root = insert(root, 25);
    // root = insert(root, 30);

    // printf("Preorder : ");
    // preorder(root);
    // printf("\nInorder : ");
    // inorder(root);
    // printf("\nPostorder : ");
    // postorder(root);
    printf("\n");
    int height = findHeight(root);
    printf("Height of tree is %d\n\n", height);

    root = image(root);
    findHeight(root);
    // inorder(root);
    return 0;
}

int findHeight(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    struct node *queue[20];
    int front = 0, rear = 0;
    int currentlev = 1;
    int nextLev = 0;
    int height = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        struct node *current = queue[front++];
        printf("%d ", current->data);
        currentlev--;
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
        if (currentlev == 0)
        {
            printf("\n");
            height++;
            currentlev = nextLev;
            nextLev = 0;
        }
    }
    return height - 1;
}
void preorder(struct node *T)
{
    while (T != NULL || !emptystack(top))
    {
        while (T != NULL)
        {
            printf("%d", T->data);
            push(T, &top);
            T = T->left;
        }
        if (!emptystack(top))
        {
            T = pop(&top);
            T = T->right;
        }
    }
}
void inorder(struct node *T)
{
    while (T != NULL || !emptystack(top))
    {
        while (T != NULL)
        {
            push(T, &top);
            T = T->left;
        }
        if (!emptystack(top))
        {
            T = pop(&top);
            printf("%d", T->data);
            T = T->right;
        }
    }
}
int emptystack(struct stack *top)
{
    return top == NULL;
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
struct node *create(int data)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = newnode->right = NULL;
    return newnode;
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
        while (T == NULL && !emptystack(top))
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

    } while (!emptystack(top));
}
struct node *image(struct node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    struct stack *s = NULL;
    push(root, &s);
    while (!emptystack(s))
    {
        struct node *current = pop(&s);
        struct node *temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left)
        {
            push(current->left, &s);
        }
        if (current->right)
        {
            push(current->right, &s);
        }
    }
    return root;
}