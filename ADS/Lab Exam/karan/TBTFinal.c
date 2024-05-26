#include <stdio.h>
#include <stdlib.h>

struct TBTNode
{
    int data;
    int lbit;
    int rbit;
    struct TBTNode* left;
    struct TBTNode* right;
};

struct TBTNode* create(struct TBTNode* head, int key)
{
    struct TBTNode* temp;
    struct TBTNode* p;

    temp = (struct TBTNode*)malloc(sizeof(struct TBTNode));

    temp->lbit = temp->rbit = 0;
    temp->data = key;

    if (head->lbit == 0)
    {
        head->left = temp;
        head->lbit = 1;
        temp->left = temp->right = head;

        return head;
    }

    p = head->left;

    while (1)
    {
        if (key < p->data && p->lbit == 1)
        {
            p = p->left;
        }

        else if (key > p->data && p->rbit == 1)
        {
            p = p->right;
        }

        else
        {
            break;
        }
    }

    if (key < p->data)
    {
        temp->right = p;
        temp->left = p->left;
        p->left = temp;
        p->lbit = 1;
    }

    if (key > p->data)
    {
        temp->left = p;
        temp->right = p->right;
        p->right = temp;
        p->rbit = 1;
    }

    return head;
};

void inOrder(struct TBTNode* head)
{
    struct TBTNode* temp = head->left;

    while(temp->lbit == 1)
    {
        temp = temp->left;
    }

    while(temp != head)
    {
        printf("%d ",temp->data);

        if (temp->rbit == 0)
        {
            temp = temp->right;
        }
        else if (temp->rbit == 1)
        {
            temp = temp->right;

            while (temp->lbit == 1)
            {
                temp = temp->left;
            }
        }
    }
}

void preOrder(struct TBTNode* head)
{
    struct TBTNode* temp = head->left;

    while(temp != head)
    {
        printf("%d ",temp->data);

        if(temp->lbit == 1)
        {
            temp = temp->left;
        }

        else if (temp->rbit == 1)
        {
            temp = temp->right;
        }

        else if (temp->rbit == 0)
        {
            while(temp->rbit == 0)
            {
                temp = temp->right;
            }

            temp = temp->right;
        }
    }
}

struct TBTNode* findParent(struct TBTNode* p)
{
    struct TBTNode* child = p;
    // ancestor of child
    while (p->rbit == 1)
        p = p->right;
    p = p->right;

    if (p->left == child)
        return p;

    p = p->left;
    while (p->right != child)
    {
        p = p->right;
    }
    return p;
}

struct TBTNode* postSuccessor(struct TBTNode *p)
{
    struct TBTNode* cur = p;
    struct TBTNode* parent = findParent(cur);

    if (parent->right == cur)
        return parent;

    else
    {
        while (p->rbit == 1)
            p = p->right;
        p = p->right;

        if (p->rbit == 1)
        {
            p = p->right;
            while (!(p->rbit == 0 && p->lbit == 0))
            {
                if (p->lbit == 1)
                    p = p->left;
                else if (p->rbit == 1)
                    p = p->right;
            }
        }
    }
    return p;
}

void postOrder(struct TBTNode* head)
{
    struct TBTNode *p = head->left;
    struct TBTNode *temp = p;
    while (!(p->rbit == 0 && p->lbit == 0))
    {
        if (p->lbit == 1)
        {
            p = p->left;
        }
        else if (p->rbit == 1)
            p = p->right;
    }
    printf("%d ", p->data);

    while (p != head->left)
    {
        // printf(" hello\n");
        p = postSuccessor(p);
        printf("%d ", p->data);
    }
}

int main()
{
    struct TBTNode* head = NULL;

    int n;
    int key;

    head = (struct TBTNode*)malloc(sizeof(struct TBTNode));
    head->rbit = 1;
    head->lbit = 0;
    head->left = head->right = head;

    while (1)
    {
        printf("\n");
        int choice;
        printf("1. Create TBT \n2. Inorder display \n3. Preorder display \n4. Postorder display\n5. Exit\n");
        printf("Enter your choice\n");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            printf("Enter the number of nodes\n");
            scanf("%d",&n);

            for (int i = 0;i < n;i++)
            {
                printf("Enter data\n");
                scanf("%d",&key);
                head =  create(head, key);
            }
            break;
        case 2:
            inOrder(head);
            break;
        case 3:
            preOrder(head);
            break;
        case 4:
            postOrder(head);
            break;
        case 5:
            exit(0);
        }
    }
}

