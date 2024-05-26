/*       Write a program to efficiently search a particular employee record by using Tree data structure. Also sort the data on emp-id in ascending order.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee{
    int id;
    char name[20];
    struct employee *l, *r;
}node;

node *create(int id, char name[]);
node *insert(int id, char name[], node *root);
node *search(int id, node *root);
void sortAscending(node *root);

int main(){

}

node *create(int id, char name[])
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->id = id;
    strcpy(name,newNode->name);
    newNode->l = NULL;
    newNode->r = NULL;
    return newNode;
}

node *insert(int id, char name[], node* root){
    if(root == NULL)
        return create(id, name);
    else if(id<root->id)
        root->l = insert(id, name, root->l);
    else
        root->r = insert(id, name, root->r);
}

node *search(int id, node *root){
    if(root == NULL || root->id == id)
        return root;
    else if (id<root->id)
        return search(id, root->l);
    else
        return search(id, root->r);    
}

void sortAscending(node *root){
    if (root != NULL)
    {
        sortAscending(root->l);
        printf("ID %d : Name %s\n",root->id, root->name);
        sortAscending(root->r);
    }   
}