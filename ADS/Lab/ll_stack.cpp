#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *next;
};
struct node *top = 0;

void push(int x){
    struct node *t;
    t = (struct node*)malloc(sizeof(struct node));
        t->data = x;
        t->next = top;
        top = t;
}

void pop(){
    if (top == NULL)
        printf("\n underflow");
    else
    {
        struct node *t;
        t = top;
        int pop = t->data;
        printf("\n %d",pop);
        top = top->next;
        free(t);
    }    
}

void peek(){
    if (top == NULL)
        printf("underflow");
    else
    printf("\n %d",top->data);
}

void display(){
    if (top == NULL)
        printf("underflow");
    else
    {
        struct node *t;
        t = top;
        while (t!=NULL)
        {
            printf("\n %d",t->data);
            t=t->next;
        }
    }
}

void sortStack() {
    if (top == NULL || top->next == NULL) {
        printf("Stack is empty or has one element only");
    }

    struct node *current, *nextNode;
    int temp;
    current = top;
    while (current != NULL) {
        nextNode = current->next;
        while (nextNode != NULL) {
            if (current->data > nextNode->data) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}


int main(){
    push(2);
    push(3);
    push(1);
    peek();
    display();
    sortStack();
    display();
    pop();
    peek();
    pop();
    pop();
    peek();
}