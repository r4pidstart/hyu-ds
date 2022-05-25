#include<stdio.h>
#include<stdlib.h>

#define M_WAY 3

typedef struct BTNode
{
    int n, isLeaf, isRoot, keys[M_WAY];
    struct BTNode *childs[M_WAY+1];
}BTNode;

BTNode *initBTNode(void)
{
    BTNode *new;
    new = malloc(sizeof(BTNode));
    new->n=0;
    new->isLeaf=1;
    new->isRoot=0;

    for(int i=0; i<M_WAY+1; i++)
        new->childs[i]=NULL;
    
    return new;
}

BTNode *splitChild(BTNode *root)
{
    BTNode *newParent, *newSibling;

    newParent=initBTNode();
    newParent->isLeaf=0;
    newParent->isRoot=root->isRoot;
    root->isRoot=0;

    newSibling=initBTNode();
    newSibling->isLeaf=root->isLeaf;

    int mid=(M_WAY-1)/2; // -1이 꼭 필요한가?
    for(int i=mid+1; i<M_WAY; i++)
    {
        newSibling->childs[i-mid-1]=root->childs[i];
        newSibling->keys[i-mid-1]=root->keys[i];
        newSibling->n++;

        root->childs[i]=0;
        root->keys[i]=0;
        root->n--;
    }
    newSibling->childs[M_WAY-mid-1]=root->childs[M_WAY];
    root->childs[M_WAY]=0;

    newParent->keys[0]=root->keys[mid];
    newParent->n++;
    root->keys[mid]=0;
    root->n--;

    newParent->childs[0]=root;
    newParent->childs[1]=newSibling;

    return newParent;
}

BTNode *BTInsert(BTNode *root, int key)
{
    BTNode *split;
    int pos;

    if(root->isLeaf)
    {
        for(pos=0; pos < root->n; pos++)
            if(root->keys[pos] > key) break;

        for(int i=root->n; i>pos; i--)
            root->keys[i]=root->keys[i-1];
        
        root->keys[pos]=key;
        root->n++;

        if(root->n == M_WAY && root->isRoot)
            return splitChild(root);
        return root;
    }
    else
    {
        for(pos=0; pos < root->n; pos++)
            if(root->keys[pos] > key) break;
        
        BTInsert(root->childs[pos], key);

        if(root->childs[pos]->n == M_WAY)
        {
            split = splitChild(root->childs[pos]);
            for(int i=root->n; i>pos; i--)
            {
                root->keys[i]=root->keys[i-1];
                root->childs[i+1]=root->childs[i];
            }
            root->childs[pos+1]=root->childs[pos];

            root->keys[pos]=split->keys[0];
            root->childs[pos]=split->childs[0];
            root->childs[pos+1]=split->childs[1];
            root->n++;
        }

        if(root->n == M_WAY && root->isRoot)
            return splitChild(root);
        return root;
    }
}

void inorderTraversal(BTNode *root)
{
    printf("\n");
    for(int i=0; i<root->n; i++)
    {
        if(!root->isLeaf)
        {
            inorderTraversal(root->childs[i]);
            printf("   ");
        }
        printf("%d ", root->keys[i]);
    }

    if(!root->isLeaf)
        inorderTraversal(root->childs[root->n]);
    printf("\n");
}


int main(void)
{
    BTNode *root;
    int n,t;

    root = initBTNode();
    root->isRoot=1;

    printf("cnt: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++)
    {
        printf("data: ");
        scanf("%d", &t);
        root = BTInsert(root, t);
    }
    printf("print:\n");
    inorderTraversal(root);
}
