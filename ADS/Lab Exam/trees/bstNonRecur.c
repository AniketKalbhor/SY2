/* Write a Program to create a Binary Tree and perform following non-recursive operations on it. 
0. Insert
1. Delete
a. Preorder Traversal 
b. Inorder Traversal 
c. Postorder Traversal
d. Count and Display Leaf Nodes 
e. Display height of a tree.
f. Count total no. of nodes 
g. Mirror Image without disturbing original tree
h. Mirror Image with disturbing original tree
i. Level-wise Traversal */

#include <stdio.h>
#include <stdlib.h>

typedef struct nodeee {
    int data;
    struct nodeee *l, *r;
} node;

typedef struct stackkk {
    struct nodeee *node;
    struct stackkk *next;
} stack;

void push(node *root, stack **top) {
    stack *temp = (stack *)malloc(sizeof(stack));
    temp->node = root;
    temp->next = *top;
    *top = temp;
}

node *pop(stack **top) {
    stack *temp;
    node *n;
    if (*top == NULL)
        return NULL;
    else {
        temp = *top;
        *top = (*top)->next;
        n = temp->node;
        free(temp);
        return n;
    
    }
}

int emptyStack(stack *top) {
    return top == NULL;
}

node *topStack(stack **top) {
    return ((*top)->node);
}

node *create(int data) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->l = NULL;
    newNode->r = NULL;
    return newNode;
}

node *insert(node *root, int data) {
    if (root == NULL)
        root = create(data);
    else if (data > root->data)
        root->r = insert(root->r, data);
    else
        root->l = insert(root->l, data);

    return root;
}

void preOrder(node *root) {
    stack *top = NULL;
    while (root != NULL) {
        printf("%d ", root->data);
        push(root, &top);
        root = root->l;
    }

    while (!emptyStack(top)) {
        root = pop(&top);
        root = root->r;

        while (root != NULL) {
            printf("%d ", root->data);
            push(root, &top);
            root = root->l;
        }
    }
}

void inOrder(node *root) {
    stack *top = NULL;
    while (root != NULL) {
        push(root, &top);
        root = root->l;
    }

    while (!emptyStack(top)) {
        printf("%d ", topStack(&top)->data);
        root = pop(&top);
        root = root->r;
        while (root != NULL) {
            push(root, &top);
            root = root->l;
        }
    }
}

void postOrder(node *root) {
    stack *top = NULL;
    node *prev = NULL;
    while (root != NULL) {
        push(root, &top);
        root = root->l;
    }

    while (!emptyStack(top)) {
        root = topStack(&top);
        if (root->r == NULL || root->r == prev) {
            printf("%d ", root->data);
            pop(&top);
            prev = root;
        } else {
            root = root->r;
            while (root != NULL) {
                push(root, &top);
                root = root->l;
            }
        }
    }
}

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

node *mirrorImageWithoutDisturbing(node *root) {
    if (root == NULL) return NULL;

    node *newRoot = create(root->data);
    if (root->l != NULL) newRoot->r = mirrorImageWithoutDisturbing(root->l);
    if (root->r != NULL) newRoot->l = mirrorImageWithoutDisturbing(root->r);

    return newRoot;
}

node *mirrorImageWithDisturbing(node *root) {
    if (root == NULL) return NULL;

    stack *top = NULL;
    push(root, &top);
    while (!emptyStack(top)) {
        node *current = pop(&top);
        node *temp = current->l;
        current->l = current->r;
        current->r = temp;

        if (current->l) push(current->l, &top);
        if (current->r) push(current->r, &top);
    }

    return root;
}

struct node *findMin(node *root) {
    while (root->l != NULL)
        root = root->l;
    return root;
}

node *deleteNode(node *root, int data) {
    if (root == NULL) return root;
    else if (data < root->data) root->l = deleteNode(root->l, data);
    else if (data > root->data) root->r = deleteNode(root->r, data);
    else {
        if (root->l == NULL) {
            node *temp = root->r;
            free(root);
            return temp;
        } else if (root->r == NULL) {
            node *temp = root->l;
            free(root);
            return temp;
        } else {
            node *temp = findMin(root->r);
            root->data = temp->data;
            root->r = deleteNode(root->r, temp->data);
        }
    }         
    return root;
}

int main() {
    node *root = NULL;
    int choice, data;
    do {
        printf("\n\n1. Insert\n2. Delete\n3. Preorder Traversal\n4. Inorder Traversal\n5. Postorder Traversal\n6. Count and Display Leaf Nodes\n7. Display Height of a Tree\n8. Count Total Number of Nodes\n9. Mirror Image without Disturbing Original Tree\n10. Mirror Image with Disturbing Original Tree\n11. Level-wise Traversal\n0. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                printf("Preorder Traversal: ");
                preOrder(root);
                break;
            case 4:
                printf("Inorder Traversal: ");
                inOrder(root);
                break;
            case 5:
                printf("Postorder Traversal: ");
                postOrder(root);
                break;
            case 6:
                printf("Leaf Nodes: ");
                displayLeaf(root);
                break;
            case 7:
                printf("Height of the Tree: %d", findHeight(root));
                break;
            case 8:
                printf("Total Number of Nodes: %d", countNodes(root));
                break;
            case 9:
                printf("Mirror Image without Disturbing Original Tree: ");
                node *mirrorRoot = mirrorImageWithoutDisturbing(root);
                inOrder(mirrorRoot);
                break;
            case 10:
                printf("Mirror Image with Disturbing Original Tree: ");
                root = mirrorImageWithDisturbing(root);
                inOrder(root);
                break;
            case 11:
                printf("Level-wise Traversal: ");
                levelDisplay(root);
                break;
            case 0:
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice! Please try again.");
        }
    } while (choice != 0);
    return 0;
}
