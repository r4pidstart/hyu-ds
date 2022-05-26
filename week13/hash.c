#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define KEY_SIZE 10
#define TABLE_SIZE 5

typedef struct elem
{
    char key[KEY_SIZE];
}elem;

typedef struct node
{
    elem item;
    struct node *next;
}node;

node *hashtable[TABLE_SIZE];

void initTable(node *ht[])
{
    for(int i=0; i<TABLE_SIZE; i++)
        ht[i]=0;
}

int transform(char *key)
{
    int ret=0;
    while(*key)
        ret+=*(key++);
    return ret;
}

int hashFunction(char *key)
{
    return transform(key) % TABLE_SIZE;
}

void addHashTable(elem item, node *ht[])
{
    // find whether node exists
    int hash=hashFunction(item.key);

    node *cur=ht[hash];
    while(cur)
    {
        if(!strcmp(cur->item.key, item.key))
        {
            printf("중복 삽입\n");
            return;
        }
        cur=cur->next;
    }
    
    node *tmp=malloc(sizeof(node));
    tmp->item=item;
    tmp->next=ht[hash];
    ht[hash]=tmp;
}

void hashSearch(elem item, node *ht[])
{
    int hash=hashFunction(item.key);

    node *cur=ht[hash];
    while(cur)
    {
        if(!strcmp(cur->item.key, item.key))
        {
            printf("찾음\n");
            return;
        }
        cur=cur->next;
    }

    printf("못 찾음\n");
}

void printHashTable(node *ht[])
{
    for(int i=0; i<TABLE_SIZE; i++)
    {
        node *cur=ht[i];
        while(cur)
        {
            printf("%s ", cur->item.key);
            cur=cur->next;
        }
        printf("\n");
    }
}

int main(void)
{
    elem tmp;
    
    while(1)
    {
        printf("0: 추가, 1: 탐색, 2: 출력, 3: 종료 >> ");
        int cmd; scanf("%d", &cmd);

        switch (cmd)
        {
        case 0:
        case 1:
                printf("키 : ");
                scanf("%s", tmp.key);
                if(!cmd)
                    addHashTable(tmp, hashtable);
                else
                    hashSearch(tmp, hashtable);
            break;
        case 2:
            printHashTable(hashtable);
            break;
        default:
            return 0;
        }
        
    }
}
