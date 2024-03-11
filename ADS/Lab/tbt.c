#include <stdio.h>
#include <stdlib.h>

struct TBT{
    int data;
    int lbit;
    int rbit;
    struct TBT *l;
    struct TBT *r;
};

struct TBT *head;
struct TBT *insertTBT(struct TBT *head, int key){
    printf("inserting %d", key);
    struct TBT *temp, *p;
    temp = (struct TBT*)malloc(sizeof(struct TBT));
    p = head->l;
    while(1){
        if(key < p->data && p->lbit == 1)
            p=p->l;
        else if(key > p->data && p->rbit == 1)
            p=p->r;
        else
            break;
    }

    if(key < p->data){
        temp->r=p;
        temp->l=p->l;
        p->l=temp;
        p->lbit=1;
    }
    if (key > p->data){
        temp->l=p;
        temp->r=p->r;
        p->r=temp;
        p->rbit=1;
    }
    printf("done");
    
    return head;
}

void createTBT(){
    int key;
    int n;
    head = (struct TBT*)malloc(sizeof(struct TBT));
    head->rbit = 1;
    head->lbit = 0;
    head->l = head->r = head;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    n = 5;
    fflush(stdin);
    for(int i=0; i<n; i++){
        printf("iteration %d\n",i);
        printf("Enter the data:");
        fflush(stdin);
        scanf("%d", &key);
        head = insertTBT(head, key);
    }
}

void preOrder(struct TBT *head){
    struct TBT *temp;
    temp = head->l;
    while(temp != head){
        printf("%c ", temp->data);
        if(temp->lbit == 1)
            temp = temp->l;
        else if(temp->rbit == 1)
            temp = temp->r;
        else{
            while(temp->rbit == 0)
                temp = temp->r;
            temp = temp->r;
        }
    }
}

void inOrder(struct TBT *head){
    struct TBT *temp;
    temp = head->l;
    while(temp->lbit == 1)
        temp = temp->l;
    while(temp != head){
        printf("%c",temp->data);
        if(temp->rbit == 0)
            temp = temp->r;
        else{
            temp = temp->r;
            while(temp->rbit == 0)
                temp = temp->l;
        }
    }

}

void postOrder(struct TBT *head){
    struct TBT *temp;

}

int main(){
    int choice;
    do{
        printf("\n1. Create TBT\n2. Insert\n3. PreOrder\n4. InOrder\n5. PostOrder\n6. Exit\n");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                createTBT();
                printf("done");
                break;
            case 2: 
                int key;
                printf("Enter the data: ");
                scanf("%d", &key);
                head = insertTBT(head, key);
                break;
            case 3:
                preOrder(head);
                break;
            case 4:
                inOrder(head);
                break;
            case 5:
                postOrder(head);
                break;
            case 6: exit(0);
            default: printf("Invalid choice\n");
        }
    }while(1);
}