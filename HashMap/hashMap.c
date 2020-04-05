#include <stdio.h>
#include <stdlib.h>
#include "hashMap.h"

table *createTable(int size){
    table *t = (table*)malloc(sizeof(table));
    t->size = size;
    t->list = (node**)malloc(sizeof(node*)*size);
    int i;
    for(i=0;i<size;i++)
        (t->list)[i] = NULL;
    return t;
}
int hashCode(table *t,int key){
    if(key<0)
        return -(key%t->size);
    return key%t->size;
}
void insert(table *t,int key,int val){
    int pos = hashCode(t,key);
    node *list = (t->list)[pos];
    node *temp = list;
    while(temp){
        if(temp->key==key){
            temp->val = val;
            return;
        }
        temp = temp->next;
    }
    node *newNode = (node*)malloc(sizeof(node));
    newNode->key = key;
    newNode->val = val;
    newNode->next = list;
    (t->list)[pos] = newNode;
}

int lookup(table *t,int key){
    int pos = hashCode(t,key);
    node *list = (t->list)[pos];
    node *temp = list;
    while(temp != NULL){
        if((temp->key)==key){
            return temp->val;
        }
        temp = temp->next;
    }
    return -1;
}