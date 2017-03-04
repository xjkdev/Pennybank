#include "file.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listInit(List *list, size_t width, void (*destroy)(void *)) {
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
  list->width = width;
  list->destroy = destroy;
}

int listAppend(List *list, void *value) {
  if (list->length == 0) {
    Listnode *node = (Listnode *)malloc(sizeof(Listnode));
    if (node == NULL)
      return -1;
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    list->head = list->tail = node;
    list->length++;
  } else {
    Listnode *node = (Listnode *)malloc(sizeof(Listnode));
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

int listRemoveAll(List *list) {
  Listnode *current = list->head; // This is the current version.
  while (current != NULL) {
    if (list->destroy != NULL) {
      list->destroy(current->value);
    }
    list->length--;
    free(current->value);
    free(current);
    current = current->next;
  }
  listInit(list, list->width, list->destroy);
  return 0;
}

int listRemoveAt(List *list, long index) {
  Listnode *node;
  if (list->length == 0 || !(index >= 0 && index < list->length))
    return -1;
  node = listIndexAt(list, index);

  if (node == list->head) {
    list->head = node->next;
  }
  if (node == list->tail) {
    list->tail = node->prev;
  }

  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }

  if (list->destroy != NULL) {
    list->destroy(node->value);
  }
  free(node->value);
  list->length--;
  free(node);
  return 1;
}

int listDestroy(List *list) { return listRemoveAll(list); }

void nodevalcpy(List *list, void *destiny, Listnode *source) {
  memcpy(destiny, source->value, list->width);
}

List listSublist(List *list, int begin, int end) {
  List result;
  listInit(&result, list->width, list->destroy);
  Listnode *current = listIndexAt(list, begin);
  while (current != NULL && begin < end) {
    void *value = malloc(list->width);
    if (value == NULL)
      continue;
    nodevalcpy(list, value, current);
    listAppend(&result, value);
    begin++;
    current = current->next;
  }
  return result;
}

List listFilter(List *list, int (*filter)(void *)) {
  List result;
  listInit(&result, list->width, list->destroy);
  Listnode *current = list->head;
  while (current != NULL) {
    if (filter(current->value)) {
      void *value = malloc(list->width);
      if (value == NULL)
        continue;
      nodevalcpy(list, value, current);
      listAppend(&result, value);
    }
    current = current->next;
  }
  return result;
}

long listSearch(List *list, int begin, void *value) {
  Listnode *current = listIndexAt(list, begin);
  while (current != NULL) {
    if (memcmp(current->value, value, list->width) == 0) {
      return begin;
    }
    begin++;
    current = current->next;
  }
  return -1;
}

// test main

int main() {
  int i;
  List list;
  listInit(&list, sizeof(int), NULL);
  int *tmpvalue;
  for (i = 0; i < 10; i++) {
    tmpvalue = (int *)malloc(sizeof(int));
    *tmpvalue = i;
    listAppend(&list, tmpvalue);
  }
  for (i = 0; i < 10; i++) {
    printf("%d\n", *(int *)(listIndexAt(&list, i)->value));
  }

  listRemoveAt(&list, 0);
  listRemoveAt(&list, 4);
  listRemoveAt(&list, 5);
  printf("length: %ld\n", list.length);
  for (i = 0; i < list.length; i++)
    printf("%d\n", *(int *)(listIndexAt(&list, i)->value));

  listRemoveAll(&list);
  printf("length: %ld\n", list.length);

  return 0;
}
