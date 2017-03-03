// this file is to add file operations interface
#include "file.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int list_filesave(List *list, char *filename) {
  Listnode *node = list->head;
  void *buffer;
  void *tmp;
  buffer = (void *)malloc(list->width * list->length);
  tmp = buffer;
  while (node != NULL) {
    memcpy(tmp, node->value, list->width);
    tmp += list->width;
    node = node->next;
  }
  FILE *fp;
  if ((fp = fopen("file.bank", "w")) == NULL) {
    fprintf(stderr, "Can't open the file.");
    fclose(fp);
    return -1;
  } else {
    fwrite(buffer, list->length, list->width, fp);
  }
  fclose(fp);
  free(buffer);
  return 0;
}

int list_fileread(List *list, char *filename) {
  FILE *fp;
  if ((fp = fopen("file.bank", "rb")) == NULL) {
    fprintf(stderr, "Can't open the file.");
    return -1;
  }

  while (feof(fp) == 0) {
    void *value;
    value = malloc(list->width);
    fread(value, list->width, 1, fp);
    listAppend(list, value);
  }
  return 0;
}

int list_fileappend(List *list, char *filename, void *value) {
  FILE *fp;
  Listnode *scan = list->head;
  while (scan != list->tail)
    scan = scan->next;
  listAppend(list, value);
  scan = scan->next;
  if ((fp = fopen("file.bank", "a")) == NULL) {
    fprintf(stderr, "Can't open the file.");
    return -1;
  }
  fwrite(scan->value, list->width, 1, fp);
  return 0;
}

int main() {
  char i;
  List list;
  listInit(&list, sizeof(char), NULL);
  char *tmpvalue;
  for (i = 'a'; i <= 'z'; i++) {
    tmpvalue = (void *)malloc(sizeof(char));
    *tmpvalue = i;
    listAppend(&list, tmpvalue);
  }
  list_filesave(&list, "file.bank");
  return 0;
}
