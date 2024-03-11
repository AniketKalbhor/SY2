#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node * next;
};
struct node *front, *rear;

int isEmpty()
{
    if(front == NULL && rear == NULL){
        printf("\nEmpty\n");
        return 1;
    }
    else
        return 0;
}

void enqueue(int data)
{
    struct node *temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = data;
    if(isEmpty())
    {
        front = temp;
        rear = temp;
    }
    else
    {
        rear->next = temp;
        rear=temp;
    }
    
}

void dequeue()
{
    if(isEmpty());
    else if (rear == front) 
    {
        struct node *temp;
        temp = (struct node*)malloc(sizeof(struct node));
        temp = front;
        free(temp);
        rear == NULL;
        front == NULL;
    }
    else
    {
        struct node *temp;
        temp = (struct node*)malloc(sizeof(struct node));
        temp = front;
        front = front->next;
        free(temp);
    }
}

void display()
{
    if (isEmpty());
    else
    {
        struct node *temp;
        temp = (struct node*)malloc(sizeof(struct node));
        temp = front;
        while (temp!=NULL)
        {
            printf("%d->",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
}

void peek()
{
    if(isEmpty());
    else
        printf("\nPeek=%d\n",front->data);
}

int main()
{
    display();
    enqueue(2);
    enqueue(6);
    enqueue(1);
    enqueue(5);
    display();
    peek();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
}