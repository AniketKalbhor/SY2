#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TBTNode
{
    int data;
    struct TBTNode *left;
    struct TBTNode *right;
    int lThread;
    int rThread;
};

struct TBTNode *TBTCreate(struct TBTNode *head, char key)
{
    struct TBTNode *temp,*p;
    temp = (struct TBTNode *)malloc(sizeof(struct TBTNode));
    p = (struct TBTNode *)malloc(sizeof(struct TBTNode));
    p = head->left;
    while(1){
        if(key<p->data && p->lThread==1)
            p = p->left;
        else if(key>p->data && p->rThread==1)
            p = p->right;
        else
            break;
    }
    if(key<p->data){
        temp->right = p;
        temp->left = p->left;
        p->left = temp;
        p->lThread = 1;
    }
    if(key>p->data){
        temp->left = p;
        temp->right = p->right;
        p->right = temp;
        p->rThread = 1;
    }
    return head;
}

void TBTPostOrder(struct TBTNode *head){
    struct TBTNode *temp = head->left;
    while(temp->lThread==1)
        temp = temp->left;
    while(temp!=head){
        if(temp->rThread==0){
            printf("%d ", temp->data);
            temp = temp->right;
        }
        else{
            temp = temp->right;
            while(temp->lThread==1)
                temp = temp->left;
        }
    }
}

int main(){
    struct TBTNode *head;
    char key;
    int n;
    head = (struct TBTNode *)malloc(sizeof(struct TBTNode));
    head->rThread = 1;
    head->lThread = 0;
    head->left = head->right = head;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the data: ");
        scanf("%c", &key);
        head = TBTCreate(head, key);
    }
}