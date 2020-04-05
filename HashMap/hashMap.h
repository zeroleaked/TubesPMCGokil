#ifndef HASHMAP_H
#define HASHMAP_H


#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    int val;
    struct node *next;
}node;
typedef struct table{
    int size;
    struct node **list;
}table;

table *createTable(int size);
int hashCode(table *t,int key);
void insert(table *t,int key,int val);

int lookup(table *t,int key);

#endif