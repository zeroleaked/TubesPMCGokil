#ifndef HASHMAP_H
#define HASHMAP_H


#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    int val;
    struct node *next;
};
struct table{
    int size;
    struct node **list;
};
struct table *createTable(int size);
int hashCode(struct table *t,int key);
void insert(struct table *t,int key,int val);

int lookup(struct table *t,int key);

#endif