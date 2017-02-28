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
    list->tail = node;
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

  return 0;
}
