#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    struct node *left, *right;
    int height;
};
struct node *create(int key);
struct node *insert(struct node *root, int key);
int getHeight(struct node *root);
struct node *leftRotate(struct node *x);
struct node *rightRotate(struct node *y);
int getBalancefactor(struct node *n);
struct node *delete(struct node *root, int x);
int maxy(int a, int b);
void LevelDisplay(struct node *root);

void LevelDisplay(struct node *root)
{
    if (root == NULL)
    {
        return;
    }
    struct node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    int currentLev = 1;
    int nextLev = 0;

    while (front < rear)
    {
        struct node *current = queue[front++];
        printf("%d", current->key);
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
            currentLev = nextLev;
            nextLev = 0;
        }
    }
}
struct node *delete(struct node *root, int x)
{
    struct node *temp = NULL;
    if (root == NULL)
    {
        return NULL;
    }
    if (x > root->key)
    {
        root->right = delete (root->right, x);
        if (getBalancefactor(root) == 2)
        {
            if (getBalancefactor(root->left) >= 0)
            {
                root = rightRotate(root);
            }
            else
            {
                root->left = leftRotate(root->left);
                root = rightRotate(root);
            }
        }
    }
    else if (x < root->key)
    {
        root->left = delete (root->left, x);
        if (getBalancefactor(root) == -2)
        {
            if (getBalancefactor(root->right) <= 0)
            {
                root = leftRotate(root);
            }
            else
            {
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            }
        }
    }
    else
    {
        if (root->right != NULL)
        {
            temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->key = temp->key;
            root->right = delete (root->right, temp->key);
            if (getBalancefactor(root) == 2)
            {
                if (getBalancefactor(root->left) >= 0)
                {
                    root = rightRotate(root);
                }
                else
                {
                    root->left = leftRotate(root->left);
                    root = rightRotate(root);
                }
            }
        }
        else
        {
            return root->left;
        }
    }
    root->height = getHeight(root);
    return root;
}
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
    x->right = y;
    y->left = T2;
    x->height = maxy(getHeight(x->right), getHeight(x->left) + 1);
    y->height = maxy(getHeight(y->right), getHeight(y->left) + 1);
    return y;
}
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = maxy(getHeight(x->right), getHeight(x->left) + 1);
    y->height = maxy(getHeight(y->right), getHeight(y->left) + 1);
    return y;
}
int maxy(int a, int b)
{
    return (a > b ? a : b);
}
int getBalancefactor(struct node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    else
    {
        return (getHeight(n->left) - getHeight(n->right));
    }
}
int getHeight(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
        return root->height;
}
struct node *create(int key)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->key = key;
    new->left = new->right = NULL;
    new->height = 1;
    return new;
}
struct node *insert(struct node *root, int key)
{
    if (root == NULL)
    {
        return create(key);
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    if (key > root->key)
    {
        root->right = insert(root->right, key);
    }
    root->height = 1 + maxy(getHeight(root->left), getHeight(root->right));
    int bf = getBalancefactor(root);
    if (bf > 1 && key < root->left->key)
    {
        return rightRotate(root);
    }
    if (bf > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && key > root->right->key)
    {
        return leftRotate(root);
    }
    if (bf < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
int main()
{
    struct node *root = NULL;
    int data, n, ch;
    printf("Enter total number of nodes : ");
    scanf("%d", &n);
    do
    {
        printf("\nEnter choice 1.Insert 2.Delete 3.Display 4.exit : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            for (int i = 0; i < n; i++)
            {
                printf("\nEnter data : ");
                scanf("%d", &data);
                root = insert(root, data);
            }
            break;
        case 2:
            printf("\nEnter data :");
            scanf("%d", &data);
            root = delete (root, data);
            break;
        case 3:
            LevelDisplay(root);
            break;
        default:
            exit(0);
            break;
        }
    } while (ch != 4);
}