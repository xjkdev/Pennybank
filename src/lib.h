#ifndef LIB_H
#define LIB_H
#include "list.h"
#include "stData.h"
<<<<<<< HEAD
void cBalance(List *list,long index);
=======

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

>>>>>>> 6bfe7c5ab4c94f8f9729b1600166c573db1369f6
#endif
