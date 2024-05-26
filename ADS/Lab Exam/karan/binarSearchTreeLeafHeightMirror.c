#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};

struct Queue
{
    struct Node* data;
    struct Queue* next;
};

struct Queue* front;
struct Queue* rear;

struct stack
{
    struct Node* t;
    struct stack* next;
};

void push(struct Node* root, struct stack** top)
{
    struct stack* temp = (struct stack*)malloc(sizeof(struct stack));

    temp->t = root;
    temp->next = (*top);
    (*top) = temp;
}

struct Node* pop(struct stack** top)
{
    struct stack* temp;
    struct Node* n;

    temp = (*top);
    (*top) = (*top)->next;
    n = temp->t;

    free(temp);
    return n;
};

int emptyStack(struct stack* top)
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

int isEmpty()
{
    if (front == NULL && rear == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Enqueue(struct Node* node)
{
    struct Queue* p = (struct Queue*)malloc(sizeof(struct Queue));

    if (p == NULL)
    {
        printf("Memory allocation failed\n");
    }

    p->data = node;
    p->next = NULL;

    if (isEmpty())
    {
        front = p;
        rear = p;
    }

    else
    {
        rear->next = p;
        rear = p;
    }
}

void Dequeue()
{
    if (isEmpty())
    {
        printf("Queue is empty\n");
        return;
    }

    struct Queue* temp = front;

    if (rear == front)
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        front = front->next;
    }

    free(temp);
}

struct Node*createNode(int key)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation failed\n");
    }

    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
};

struct Node* insert(struct Node* root, int key)
{
    if (root == NULL)
    {
        root = createNode(key);
    }

    else if(key > root->data)
    {
        root->right = insert(root->right, key);
    }

    else
    {
        root->left = insert(root->left, key);
        return root;
    }
};

int treeHeight(struct Node* root)
{
    if (root == NULL)
    {
        return -1;
    }

    else
    {
        int leftHeight = treeHeight(root->left);
        int rightHeight = treeHeight(root->right);
        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }
}

void mirror(struct Node* root)
{
    struct Node* temp;
    struct stack* top = NULL;

    push(root, &top);

    while(!emptyStack(top))
    {
        root = pop(&top);

        temp = root->left;
        root->left = root->right;
        root->right = temp;

        if (root->left != NULL)
        {
            push(root->left, &top);
        }

        if (root->right != NULL)
        {
            push(root->right, &top);
        }
    }
}

void leafNodes(struct Node* root)
{
    struct Node* temp;
    struct stack* top = NULL;

    push(root,&top);

    while(!emptyStack(top))
    {
        root = pop(&top);

        if (root->left == NULL && root->right == NULL)
        {
            printf("%d ",root->data);
        }

        if (root->left != NULL)
        {
            push(root->left,&top);
        }

        if (root->right != NULL)
        {
            push(root->right,&top);
        }
    }
}

void levelOrder(struct Node* root)
{
    Enqueue(root);
    Enqueue(NULL);

    while (!isEmpty())
    {
        struct Node* current = front->data;
        Dequeue();

        if (current == NULL)
        {
            printf("\n");

            if (!isEmpty())
            {
                Enqueue(NULL);
            }
        }

        else
        {
            printf("%d ", current->data);

            if (current->left != NULL)
            {
                Enqueue(current->left);
            }

            if (current->right != NULL)
            {
                Enqueue(current->right);
            }
        }
    }
}

void inOrder(struct Node* root)
{
    struct stack* top = NULL;

    while (root != NULL)
    {
        push(root, &top);
        root = root->left;
    }

    while(!emptyStack(top))
    {
        root = pop(&top);
        printf("%d ", root->data);
        root = root->right;

        while(root != NULL)
        {
            push(root, &top);
            root = root->left;
        }
    }
}


int main()
{
    struct Node* root = NULL;
    int n;
    int m;
    int first;

    while (1)
    {
        printf("\n");
        printf("1. Create BST \n2. Insert \n3. Inorder display \n4. Mirror tree \n5. Height \n6. Level order display \n7. Leaf nodes display \n8. Exit\n");

        int choice;
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter value\n");
            scanf("%d",&first);
            root = createNode(first);
            break;
        case 2:
            printf("Enter data to insert\n");
            scanf("%d",&n);
            root = insert(root, n);
            break;
        case 3:
            inOrder(root);
            break;
        case 4:
            mirror(root);
            break;
        case 5:
            printf("%d is the height of the tree\n", treeHeight(root));
            break;
        case 6:
            levelOrder(root);
            break;
        case 7:
            printf("Leaf nodes:\n");
            leafNodes(root);
            break;
        case 8:
            exit(0);
        }
    }
}
