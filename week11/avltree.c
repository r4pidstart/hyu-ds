#include<stdio.h>
#include<stdlib.h>

#define max(a,b) (a)<(b) ? (b):(a)

typedef struct node
{
    int data, h;
    struct node* left,*right;
}node;

int get_height(node* now)
{
    if(!now) return -1;
    else return now->h;
}

node* rotate_l(node* now)
{
    node* next=now->left;
    now->left=next->right;
    next->right=now;

    next->h=max(next->left->h, next->right->h);
    now->h=max(now->left->h, now->right->h);
    return next;
}

node* rotate_r(node* now)
{
    node* next=now->right;
    now->right=next->left;
    next->left=now;
    
    next->h=max(next->left->h, next->right->h);
    now->h=max(now->left->h, now->right->h);
    return next;
}

node* rotate_rl(node* now)
{
    return rotate_l(rotate_r(now->right));
}

node* rotate_lr(node* now)
{
    return rotate_r(rotate_l(now->left));
}

node* new_node(int data)
{
    node* ret=(node*)malloc(sizeof(node));
    if(!ret)
        exit(1);
    ret->data=data, ret->h=0, ret->left=0, ret->right=0;
    return ret;
}

node* insert(node* root, int data)
{
    if(root)
    {
        if(data < root->data)
        {
            root->left=insert(root->left, data);
            if(get_height(root->left)-get_height(root->right) == 2)
            {
                if(data < root->left->data)
                    root=rotate_l(root);
                else
                    root=rotate_lr(root);
            }
        }
        else if(root->data < data)
        {
            root->right=insert(root->right, data);
            if(get_height(root->left)-get_height(root->right) == 2)
            {
                if(data < root->left->data)
                    root=rotate_rl(root);
                else
                    root=rotate_r(root);
            }
        }
        else
            exit(!!printf("중복키\n"));
    }
    else
        root=new_node(data);

    root->h=max(get_height(root->left), get_height(root->right))+1;
    return root;
}

node* find(node* root, int data)
{
    if(!root)
        return 0;
    if(root->data < data)
        return find(root->right, data);
    else if(data < root->data)
        return find(root->left, data);
    else
        return root;
}

void inorder_traverse(node* now)
{
    if(now)
    {
        inorder_traverse(now->left);
        printf("%d ", now->data);
        inorder_traverse(now->right);
    }
}

int main(void)
{
    node* root=0;

    root=insert(root, 7);
    root=insert(root, 8);
    root=insert(root, 9);
    root=insert(root, 2);
    root=insert(root, 1);
    root=insert(root, 5);
    root=insert(root, 3);
    root=insert(root, 6);
    root=insert(root, 4);
    
    printf("find: %d\n", find(root, 4)->data);
    inorder_traverse(root);
}
