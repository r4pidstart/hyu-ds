#include<stdio.h>
#include<stdlib.h>

typedef struct StackNode
{
    int data;
    struct StackNode* next;
}   StackNode;

int s_isEmpty(StackNode* top)
{
    return top==0;
}

void pushLinkedStack(StackNode** top, int data)
{
    StackNode *new=(StackNode *)malloc(sizeof(StackNode));
    new->data=data;
    new->next=0;

    if(s_isEmpty(*top))
        *top = new;
    else
    {
        new->next = *top;
        *top = new;
    }
}

StackNode* PopLinkedStack(StackNode** top)
{
    if(s_isEmpty(*top))
        return 0;
    StackNode *ret=*top;
    *top = (*top)->next;
    return ret;
}

void showLinkedStack(StackNode* top)
{
    StackNode *pNode=0;
    if(s_isEmpty(top))
    {
        printf("the Stack is empty\n");
        return;
    }

    pNode=top;
    printf("====Show Stack====\n");
    while(pNode)
    {
        printf("[%d]\n", pNode->data);
        pNode=pNode->next;
    }
    printf("==================\n");
}

StackNode* topLinkedStack(StackNode* top)
{
    if(!s_isEmpty(top))
        return top;
    return 0;
}

void deleteLinkedStack(StackNode** top)
{
    StackNode *pNode=*top, *pDelNode=0;

    while(pNode)
    {
        pDelNode=pNode;
        pNode=pNode->next;
        free(pDelNode);
    }
    *top=0;
}

typedef struct Node
{
    int data;
    struct Node* nextNode;
}   Node;

typedef struct LinkedList
{
    int curCount;
    Node headNode;
}   LinkedList;

int isEmpty(LinkedList* pList)
{
    if(!pList)
        return -(!!printf("isEmpty() error\n"));
    if(!(pList->curCount))
        return 1;
    return 0;
}

int addNode(LinkedList* pList, int pos, int data)
{
    if(!pList)
        return -(!!printf("addNode() error\n"));
    else if(pos < 0 || pos > pList->curCount)
        return -(!!printf("addNode() error2\n"));

    Node* new=(Node *)malloc(sizeof(Node));
    if(!new)
        return -(!!printf("addNode() error3\n"));
    new->data=data;
    new->nextNode=0;

    Node* cur=&(pList->headNode);
    for(int i=0; i<pos; i++)
        cur=cur->nextNode;
    
    new->nextNode=cur->nextNode;
    cur->nextNode=new;
    pList->curCount++;
    return 0;
}

int removeNode(LinkedList* pList, int pos)
{
    if(!pList)
        return -(!!printf("removeNode() error\n"));
    else if(pos < 0 || pos > pList->curCount)
        return -(!!printf("removeNode() error2\n"));

    Node* cur=&(pList->headNode);
    for(int i=0; i<pos; i++)
        cur=cur->nextNode;

    Node* tmp=cur->nextNode;
    cur->nextNode=cur->nextNode->nextNode;
    free(tmp);
    pList->curCount--;
    return 0;
}

void showNode(LinkedList *pList)
{
    if(!pList)
    {
        printf("showNode() error\n");
        return;
    }

    Node *cur=pList->headNode.nextNode;
    printf("node cnt: %d\n", pList->curCount);
    while(cur)
    {
        printf("[%d]\n", cur->data);
        cur=cur->nextNode;
    }
    printf("---------------\n");
}

void makeEmpty(LinkedList* pList)
{
    if(!pList)
        return;
    
    Node* cur=pList->headNode.nextNode;
    while(cur)
    {
        Node* tmp=cur;
        cur=cur->nextNode;
        free(tmp);
    }
    pList->curCount=0;
    pList->headNode.nextNode=0;
}

void reverseList(LinkedList* ll, StackNode** top)
{
    printf("Reverse Linked List\n");
    Node *cur=ll->headNode.nextNode;

    while(cur)
    {
        pushLinkedStack(top, cur->data);
        cur=cur->nextNode;
    }

    makeEmpty(ll);
    for(int i=0; !s_isEmpty(*top); i++)
        addNode(ll, i, PopLinkedStack(top)->data);
}

int main()
{
    // int pos;
    LinkedList* linkedlist=(LinkedList *)malloc(sizeof(LinkedList));
    linkedlist->curCount=0;
    linkedlist->headNode.nextNode=0;

    StackNode* top=0;
    // StackNode* pNode;

    addNode(linkedlist, 0, 10);
    addNode(linkedlist, 5, 100);
    addNode(linkedlist, 1, 20);
    addNode(linkedlist, 2, 30);
    addNode(linkedlist, 1, 50);
    addNode(linkedlist, 1, 70);
    addNode(linkedlist, 1, 40);

    showNode(linkedlist);

    reverseList(linkedlist, &top);

    showNode(linkedlist);

    makeEmpty(linkedlist);
    showNode(linkedlist);
}
