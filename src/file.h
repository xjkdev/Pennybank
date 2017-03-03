#ifndef FILE_H
#define FILE_H
#include "list.h"
#include "stData.h"

int list_filesave(List *list, char *filename);
int list_fileread(List *list, char *filename);
int list_fileappend(List *list, char *filename, void *value);
int list_fileexit(char *filename);
#endif
