// this file is to add file operations interface
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "list.h"

int list_filesave(List *list,char *filename) {
  Listnode *node = list->head;
  void *buffer;
  void *tmp;
  buffer=malloc(list->width * list->length);
  tmp = buffer;
  while(node != NULL ) {
    memcpy(tmp,node->value,list->width);
    tmp+=list->width;
    node=node->next;
  }
  FILE *fp;
  if((fp=fopen("file.bank","w"))==NULL) {
    fprintf(stderr,"Can't open the file.");
    fclose(fp);
    return -1;
  } else {
    fwrite(buffer,list->length,list->width,fp);
  }
  fclose(fp);
  free(buffer);
  return 0;
}

int main() {
  char i;
  List list;
  listInit(&list, sizeof(char), NULL);
  char *tmpvalue;
  for (i = 'a'; i <= 'z'; i++) {
    tmpvalue = malloc(sizeof(char));
    *tmpvalue = i;
    listAppend(&list, tmpvalue);
  }
  list_filesave(&list,"file.bank");
  return 0;

}

