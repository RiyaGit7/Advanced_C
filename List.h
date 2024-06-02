#include "status.h"
#ifndef __LIST_H__
#define __LIST_H__

typedef struct Node {
    void *val;
    struct Node *next;
} Node;

typedef int (*compFun)(void *e1, void *e2);
typedef void (*prFun)(void *);

typedef struct List {
    int nelts;
    Node *head;
    compFun comp;
    prFun pr;
} List;

List *newList(compFun comp, prFun pr);
void delList(List *l);
status nthInList(List *l, int n, void *res);
status addListAt(List *l, int n, void *e);
status remFromListAt(List *l, int n, void *res);
status remFromList(List *l, void *e);
status displayList(List *l);
void forEach(List *l, void (*f)(void *));
int lengthList(List *l);
status addList(List *l, void *e);
Node *isInList(List *l, void *e);

#endif