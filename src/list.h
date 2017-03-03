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
int listInsert(List *list, void *value, long index);
int listRemoveAll(List *list);
int listRemoveAt(List *list, long index);
Listnode *listIndexAt(List *list, long index);
int listDestroy(List *list);

// Return a List that contains elements from begin to end
// (include begin and NOT include end)
// elements will be copy in memory
List listSublist(List *list, int begin, int end);
// Copy value from source to destiny by width of list
void nodevalcpy(List *list, void *destiny, Listnode *source);

long listSearch(List *list, int begin, void *value);
void listSort(List *list, int (*compare)(void *, void *));
// Return a List in which all elements' value fit fileter
List listFilter(List *list, int (*filter)(void *));
#endif
