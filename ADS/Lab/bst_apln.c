#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *l;
    struct node *r;
};
struct node *root = NULL;

struct node*createBST(int data)
{
    struct node *newNode= (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
        printf("Memory Allocation failed\n");
    newNode->data = data;
    newNode->l = NULL;
    newNode->r = NULL;

    return newNode;
}

struct node *insertNode(struct node* root, int newdata)
{
    if(root == NULL){
        root = createBST(newdata);
    }
    else if (newdata>root->data)
        root->r = insertNode(root->r, newdata);
    else
        root->l = insertNode(root->l, newdata);
    return root;
}

void RinOrder(struct node *root)
{
    if(root != NULL){
        RinOrder(root->l);
        printf("%d ", root->data);
        RinOrder(root->r);
    }
}

void mirrorImage(struct node *root)
{
    if(root != NULL){
        struct node *temp;
        mirrorImage(root->l);
        mirrorImage(root->r);
        temp = root->l;
        root->l = root->r;
        root->r = temp;
    }
}

void levelDisplay(struct node *root)
{
    struct node *queue[100];
    int front = 0, rear = 0;
    if(root == NULL)
        return;
    queue[rear++] = root;
    printf("\nLevel order traversal is: ");
    while(front < rear){
        struct node *temp = queue[front++];
        printf("%d ", temp->data);
        if (front == rear)
            printf("\n");
        if(temp->l != NULL)
            queue[rear++] = temp->l;
        if(temp->r != NULL)
            queue[rear++] = temp->r;
    }
}


int height(struct node *root)
{
    if(root == NULL)
        return 0;
    else{
        int lheight = height(root->l);
        int rheight = height(root->r);
        if(lheight > rheight)
            return lheight+1;
        else
            return rheight+1;
    }
}

void leafNodes(struct node *root)
{
    if(root != NULL){
        if(root->l == NULL && root->r == NULL)
            printf("%d ", root->data);
        leafNodes(root->l);
        leafNodes(root->r);
    }
}

struct node *minValueNode(struct node *node)
{
    if (node == NULL)
        return NULL;
    while(node->l != NULL)
        node = node->l;
    return node;
}

struct node *deleteNode(struct node *root, int key)
{
    struct node *dtemp;
    if(root==NULL)
        return root;
    else if (key<root->data)
        root->l = deleteNode(root->l, key);
    else if (key>root->data)
        root->r = deleteNode(root->r, key);
    else{
        if(root->l == NULL){
            dtemp = root->r;
            free(root);
            return dtemp;
        }
        else if(root->r == NULL){
            dtemp = root->l;
            free(root);
            return dtemp;
        }
        else{
            dtemp = minValueNode(root->r);
            root->data = dtemp->data;
            root->r = deleteNode(root->r, dtemp->data);
        }
    }
    return root;
}


int main()
{
    int choice;
    int createdata;
    int newdata;
    int deletedata;
    while(1){
        printf("\n1. Create BST\n2. Insert\n3. Delete\n4. InOrder\n5. Mirror Image\n6. Level displaay\n7. Height\n8. Leaf Nodes\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                printf("Enter the data: ");
                scanf("%d", &createdata);
                root = createBST(createdata);
                break;
            
            case 2:
                printf("Enter the data: ");
                scanf("%d", &newdata);
                root = insertNode(root, newdata);
                break;

            case 3:
                printf("Enter the data: ");
                scanf("%d", &deletedata);
                root = deleteNode(root, deletedata);
                break; 

            case 4:
                RinOrder(root);
                break;

            case 5:
                RinOrder(root);
                mirrorImage(root);
                printf("\nMirror Image is: ");
                RinOrder(root);
                break;
            
            case 6:
                levelDisplay(root);
                break;

            case 7:
                printf("\nHeight of the tree is: %d\n", height(root));
                break;
            
            case 8:
                printf("\nLeaf nodes are: ");
                leafNodes(root);
                break;
            
            case 9:
                exit(0);
                break;
        }
    }
}
// void levelOrderTraversal(struct node *root) {
//     if (root == NULL) {
//         return;
//     }

//     enqueue(root);
//     int currentLevel = 0;
//     int nextLevelNodes = 0;
//     int currentLevelNodes = 1;

//     printf("Level 0: ");

//     while (front != NULL) {
//         struct node *temp = dequeue();
//         currentLevelNodes--;

//         printf("%d ", temp->data);

//         if (temp->left != NULL) {
//             enqueue(temp->left);
//             nextLevelNodes++;
//         }
//         if (temp->right != NULL) {
//             enqueue(temp->right);
//             nextLevelNodes++;
//         }

//         if (currentLevelNodes == 0) {
//             printf("\nLevel %d: ", currentLevel+1);
//             currentLevel++;
//             currentLevelNodes = nextLevelNodes;
//             nextLevelNodes = 0;
//         }
        
//     }
// }