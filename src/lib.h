#ifndef LIB_H
#define LIB_H
#include "list.h"
#include "stData.h"

typedef struct Check {
    int year;
    int month;
    int earn;
    int expense;
}Check;
int comparebytime(stData * stdata1,stData * stdata2);
int comparebyid(stData * stdata1,stData * stdata2);
int comparebyuserid(stData * stdata1,stData * stdata2);
int comparebyamount(stData * stdata1,stData * stdata2);
int comparebybalance(stData * stdata1,stData * stdata2);
void check(List * list);

#endif
