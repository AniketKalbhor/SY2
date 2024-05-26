/*Write a Program to create Inorder Threaded Binary Tree and Traverse it in :Preorder, Inorder*/

#include <stdio.h>
#include <stdlib.h>

typedef struct tbt
{
    struct tbt *left;
    int lthread;
    int data;
    int rthread;
    struct tbt *right;
}node;

node *tbtCreate(node *head, int data);
void preOrder(node *head);
void inOrder(node *head);

int main(){
    node *head;
    head = (node*)malloc(sizeof(node));
    head->lthread = head->rthread = 1;
    head-> left = head->right = head;
}

node *tbtCreate(node *head, int data){
    node *temp, *root;
    temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->lthread = temp->rthread = 0;
    if (head->left == head){
        temp->left = head;
        temp->right = head;
        head->left = temp;
        return head;
    }

    root = head->left;
    while (1)
    {
        if (data < root->data && root->lthread == 1)
            root = root->left;
        else if (data > root->data && root->rthread == 1)
            root = root->right;
        else
            break;        
    }

    if (data < root->data){
        temp->left = root->left;
        temp->right = root;
        root->left = temp;
        root->lthread = 1;
    }    
    else{
        temp->left = root;
        temp->right = root->right;
        root->right = temp;
        root->rthread = 1;
    }
    return head;
}

void preOrder (node *head){
    node *traversal = head->left;
    while(traversal != head){
        printf("%d ", traversal->data);
        if(traversal->lthread == 1)
            traversal = traversal->left;
        else if (traversal->rthread == 1)
            traversal = traversal->right;
        else{
            while (traversal->rthread == 0)
                traversal = traversal->right;
            traversal = traversal->right;
        }        
    }
}

void inOrder (node *head){
    node *traversal = head->left;
    while (traversal->lthread == 1)
        traversal = traversal->left;
    while (traversal != head){
        printf("%d ", traversal->data);
        if(traversal->rthread == 0)
            traversal = traversal->right;
        else{
            traversal = traversal->right;
            while (traversal->lthread == 1)
                traversal = traversal->left;   
        }
    }
}