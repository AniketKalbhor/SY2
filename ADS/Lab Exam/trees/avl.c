/*       Write a Program to implement AVL tree and perform different rotations on it and display it Levelwise.*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

int height(struct Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    return root->height;
}

int max(int a, int b)
{
    return(a > b)? a : b;
}

struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->data = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return(node);
};

struct Node* rightRotate(struct Node* y)
{
    struct Node* x = y->left;
    struct Node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;

    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
};

struct Node* leftRotate(struct Node* x)
{
    struct Node* y = x->right;
    struct Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left), height(x->right)) + 1;

    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
};

int getBalance(struct Node* root)
{
    if (root == NULL)
    {
        return 0;
    }

    return height(root->left) - height(root->right);
}

struct Node* insert(struct Node* root, int key)
{
    if (root == NULL)
    {
        root = newNode(key);
    }

    if (key < root->data)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = insert(root->right, key);
    }
    else
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->data)
    {
        return rightRotate(root);
    }

    if (balance < -1 && key > root->right->data)
    {
        return leftRotate(root);
    }

    if (balance > 1 && key > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
};

void levelDisplay(node *root) {
    node *queue[100];
    int front = 0, rear = 0;
    if (root == NULL)
        return;
    queue[rear++] = root;
    printf("\nLevel order traversal is:\n");
    while (front < rear) {
        int levelSize = rear - front;
        for (int i = 0; i < levelSize; i++) {
            node *temp = queue[front++];
            printf("%d ", temp->data);
            if (temp->l != NULL)
                queue[rear++] = temp->l;
            if (temp->r != NULL)
                queue[rear++] = temp->r;
        }
        printf("\n");
    }
}


void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(struct Node *root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

/* Driver program to test above function*/
int main()
{
  struct Node* root = NULL;

  int n;

  while (1)
  {
      printf("\n");
      printf("1. Insert \n2. Inorder \n3. Preorder \n4. Postorder \n5. Exit\n");

      int choice;
      printf("Enter your choice\n");
      scanf("%d",&choice);

      switch(choice)
      {
      case 1:
        printf("Enter value to insert\n");
        scanf("%d",&n);
        root = insert(root, n);
        break;
      case 2:
        inOrder(root);
        break;
      case 3:
        preOrder(root);
        break;
      case 4:
        postOrder(root);
        break;
      case 5:
        exit(0);
      }
  }
}
