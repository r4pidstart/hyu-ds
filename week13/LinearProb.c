#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define KEY_SIZE 10
#define TABLE_SIZE 13

typedef struct elem
{
    char key[KEY_SIZE];
}elem;

elem hashtable[TABLE_SIZE];

void initTable(elem ht[])
{
    for(int i=0; i<TABLE_SIZE; i++)
        ht[i].key[0]=0;
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

void addHashTable(elem item, elem ht[])
{
    int hash=hashFunction(item.key);

    for(int i=hash, cnt=0; cnt < TABLE_SIZE; i=(i+1)%TABLE_SIZE, cnt++)
    {
        if(ht[i].key[0] == '\0')
        {
            ht[i]=item;
            return;
        }
        else if(!strcmp(ht[i].key, item.key))
        {
            printf("중복 삽입\n");
            return;
        }
    }
    printf("공간 부족\n");
}

void hashSearch(elem item, elem ht[])
{
    int hash=hashFunction(item.key);

    for(int i=hash, cnt=0; cnt < TABLE_SIZE; i=(i+1)%TABLE_SIZE, cnt++)
    {
        if(ht[i].key[0] == '\0')
            break;
        if(!strcmp(ht[i].key, item.key))
        {
            printf("찾음\n");
            return;
        }
    }
    printf("못 찾음\n");
}

void printHashTable(elem ht[])
{
    for(int i=0; i<TABLE_SIZE; i++)
        printf("[%d]    %s\n", i, ht[i].key);
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
