#ifndef FILE_H
#define FILE_H
#include "list.h"
#include "stData.h"

typedef struct FileHead {
  long length;
  size_t width;
} FileHead;

int list_filesave(List *list, char *filename);
int list_fileread(List *list, char *filename);
int list_fileappend(List *list, char *filename);
#endif
