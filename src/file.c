// this file is to add file operations interface
#include "file.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int list_filesave(List *list, char *filename) {
  Listnode *node = list->head;
  FileHead filehead;
  void *buffer;
  char *tmp; // sizeof char is 1
  buffer = (void *)malloc(list->width * list->length);
  tmp = buffer;
  while (node != NULL) {
    memcpy(tmp, node->value, list->width);
    tmp += list->width;
    node = node->next;
  }
  FILE *fp;
  if ((fp = fopen("file.bank", "wb")) == NULL) {
    fprintf(stderr, "Can't open the file.");
    fclose(fp);
    return -1;
  } else {
    filehead.length = list->length;
    filehead.width = list->width;
    fwrite(&filehead, sizeof(filehead), 1, fp);
    fwrite(buffer, list->length, list->width, fp);
  }
  fclose(fp);
  free(buffer);
  return 0;
}

int list_fileread(List *list, char *filename) {
  FILE *fp;
  FileHead fhead;
  if ((fp = fopen("file.bank", "rb")) == NULL) {
    fprintf(stderr, "Can't open the file.");
    return -1;
  }

  while (fread(&fhead, sizeof(FileHead), 1, fp) == 1) {
    int i;
    for (i = 0; i < fhead.length; i++) {
      void *value;
      value = malloc(fhead.width);
      fread(value, fhead.width, 1, fp);
      listAppend(list, value);
    }
  }
  return 0;
}

int list_fileappend(List *list, char *filename) {
  Listnode *node = list->head;
  FileHead filehead;
  void *buffer;
  char *tmp;
  buffer = (void *)malloc(list->width * list->length);
  tmp = buffer;
  while (node != NULL) {
    memcpy(tmp, node->value, list->width);
    tmp += list->width;
    node = node->next;
  }
  FILE *fp;
  if ((fp = fopen("file.bank", "ab")) == NULL) {
    fprintf(stderr, "Can't open the file.");
    fclose(fp);
    return -1;
  } else {
    filehead.length = list->length;
    filehead.width = list->width;
    fwrite(&filehead, sizeof(filehead), 1, fp);
    fwrite(buffer, list->length, list->width, fp);
  }
  fclose(fp);
  free(buffer);
  return 0;
}

//int main() {
//  char i;
//  List list;
//  listInit(&list, sizeof(char), NULL);
//  char *tmpvalue;
//  for (i = 'a'; i <= 'z'; i++) {
//    tmpvalue = (void *)malloc(sizeof(char));
//    *tmpvalue = i;
//    listAppend(&list, tmpvalue);
//  }
//  list_filesave(&list, "file.bank");
//  return 0;
//}
