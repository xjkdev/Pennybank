#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void listInit(List *list, size_t width, void (*destroy)(void *)) {
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
  list->width = width;
  list->destroy = destroy;
}

int listAppend(List *list, void *value) {
  if (list->length == 0) {
    Listnode *node = malloc(sizeof(Listnode));
    if (node == NULL)
      return -1;
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    list->head = list->tail = node;
    list->length++;
  } else {
    Listnode *node = malloc(sizeof(Listnode));
    if (node == NULL)
      return -1;
    node->value = value;
    node->prev = list->tail;
    node->next = NULL;
    list->tail->next = node;
    list->tail = node;//先把原来node所开辟出来的空间的next指向现在的node,相当于链表的链接功能。
    list->length++;
  }
  return 0;
}

Listnode *listIndexAt(List *list, long index) {
  if (index < list->length) {
    Listnode *current = list->head;
    while (index > 0) {
      current = current->next;
      index--;
    }
    return current;
  }
  return NULL;
}

int listRemoveAll(List *list) {
  Listnode *current=list->head;
  while(list->head!=NULL) {
    current=current->next;
    free(list->head);
    list->head=current;
    list->length--;
  }
  return 1;
}

int listRemoveAt(List *list, long index) {
  Listnode *node, *pt,*pf;
  if(list->length==0)
    return (-1);
  node = listIndexAt(list,index);
  pt=node->prev;
  pf=listIndexAt(list,index)->next;
  if(list->destroy != NULL) {
    list->destroy(listIndexAt(list,index)->value);
  }
  
  if(node == list->head) {
    
    list->head = pf;
  }
  if(node == list->tail) {

    free(listIndexAt(list,index));
    list->length--;
    list->tail=pt;
  }
  if(pt!=NULL && pf!=NULL) {
    if(list->destroy != NULL) {
      list->destroy(listIndexAt(list,index)->value);
    }
    free(listIndexAt(list,index));
    pt->next=pf;
    pt=pf;
    list->length--;
  }
  list->length--;
  free(node);
  return 1;
}

// test main
int main() {
  int i;
  List list;
  listInit(&list, sizeof(int), NULL);
  int *tmpvalue;
  for (i = 0; i < 10; i++) {
    tmpvalue = malloc(sizeof(int));
    *tmpvalue = i;
    listAppend(&list, tmpvalue);
  }
  for (i = 0; i < 10; i++) {
    printf("%d\n", *(int *)(listIndexAt(&list, i)->value));
  }



  listRemoveAt(&list,4);
  listRemoveAt(&list,5);
  printf("%d\n",list.length);
  for(i=0; i<8; i++)
    printf("%d\n", *(int *)(listIndexAt(&list, i)->value));
  return 0;
}
