#include <stdio.h>
#include <stdlib.h>
#include "List.h"

static Node* available = 0;
List *newList (compFun comp, prFun pr) {
  List *l;
  l = (List*) malloc(sizeof(List));
  if (! l) return 0;
  l->nelts	= 0;
  l->head	= 0;
  l->comp 	= comp;
  l->pr     = pr;
  return l;
}

void delList (List* l) {
  Node *tmp = l->head;
  while (tmp) {
	l->head = tmp->next;
    tmp->next = available;
    available = tmp;
    tmp = l->head;
  }

  l->head = 0;
  l->nelts = 0;
  free(l);
}

status nthInList (List *l, int n, void *res) {
  Node *tmp = l->head;
  if (n <= 0 || n > l->nelts)
    return ERRINDEX;
  while (n-- > 1) tmp = tmp->next;
  *(void **)res = tmp->val;
  return OK;
}

status addListAt (List* l, int pos, void* elt) {
  if (pos <= 0 || pos > l->nelts+1)
    return ERRINDEX;
  else {
    Node *toAdd = available;
    if (!toAdd) toAdd = (Node*) malloc(sizeof(Node));
    else available = available->next;
    if (!toAdd) return ERRALLOC;
    l->nelts++;
    toAdd->val = elt;

    if (pos == 1) {
      toAdd->next = l->head;
      l->head = toAdd;
    }

    else {
      Node *tmp = l->head;
      while (pos-- > 2) tmp = tmp->next;
      toAdd->next = tmp->next;
      tmp->next = toAdd;
    }
    return OK;
  }
}

status remFromListAt	(List *l,int n, void *res) {
  Node *toRem = l->head;

  if (n <= 0 || n > l->nelts) return ERRINDEX;

  if (n == 1)
    l->head = toRem->next;
  else {
    Node *prec = toRem;
    while (n-- > 2) prec = prec->next;
    toRem = prec->next;
    prec->next = toRem->next;
  }

  *(void **)res = toRem->val;
  toRem->next = available;
  available = toRem;
  l->nelts--;
  return OK;
}

status remFromList (List* l, void* elt) {
  Node *prec = l->head;

  if (l->comp == 0) return ERRUNABLE;
  if (l->nelts == 0) return ERRABSENT;
  if (!(l->comp)(elt,prec->val)) return remFromListAt(l,1,&(prec->val));

  while (prec->next &&  (l->comp)(elt,prec->next->val))
    {
      prec = prec->next;
    }

  if (! prec->next)
    return ERRABSENT;
  else {
    Node *toRem = prec->next;
    prec->next = toRem->next;
    toRem->next = available;
    available = toRem;
    l->nelts--;
    return OK;
  }
}

status displayList (List * l ) {
  Node *tmp = l->head;
  if (l->pr == 0) return ERRUNABLE;
  printf("[ ");
  while (tmp) {
    (l->pr)(tmp->val);
    putchar(' ');
    tmp = tmp->next;
  }
  putchar(']');
  return OK;
}

void forEach (List* l, void(*f)(void*)) {
  Node *tmp = l->head;
  while (tmp) {
    (*f)(tmp->val);
    tmp = tmp->next;
  }
}

int lengthList (List* l) { return l->nelts; }

static Node* previous(List* l, void* e) {
  Node *prec = l->head;
  if (l->nelts == 0) return 0;
  if (!(l->comp)(e,prec->val)) return (Node*)1;

  while (prec->next && (l->comp)(e,prec->next->val))
    prec = prec->next;

  return prec;
}
status addList (List* l, void* e) {
  Node *prec = l->head, *toAdd;

  if (l->comp == 0) return ERRUNABLE;

  if (l->nelts == 0 || (l->comp)(e,l->head->val)<0)
    return addListAt(l,1,e);
  while (prec && prec->next && (l->comp)(prec->next->val,e)<0)
	  prec = prec->next;

  toAdd = available;
  if (!toAdd) toAdd = (Node*) malloc(sizeof(Node));
  else available = available->next;
  if (!toAdd) return ERRALLOC;
  toAdd->next = prec->next;
  toAdd->val = e;
  prec->next = toAdd;
  l->nelts++;
  return OK;
}
Node* isInList (List* l, void* e) {
  Node *prec = previous(l,e);
  if (!prec) return 0;
  if (prec == (Node*) 1) return (Node*)1;
  if (prec->next == 0) return 0;
  if (!(l->comp)(e,prec->next->val))
    return prec;
  return 0;
}