#ifndef LIST_H
#define LIST_H
#include <stdlib.h>

typedef struct Listnode {
  void *value;
  struct Listnode *next;
  struct Listnode *prev;
} Listnode;

typedef struct List {
  struct Listnode *head;
  struct Listnode *tail;
  long length;
  size_t width;
  void (*destroy)(void *);
} List;

void listInit(List *list, size_t width, void (*destroy)(void *));
int listAppend(List *list, void *value);
int listRemoveAll(List *list);
int listRemoveAt(List *list, long index);
Listnode *listIndexAt(List *list, long index);

void listSearch(List *list, void *value);
void listSort(List *list);
#endif