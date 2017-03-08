#ifndef LIB_H
#define LIB_H
#include "list.h"
#include "stData.h"

void cBalance(List *list,long index);

typedef struct Check {
    int year;
    int month;
    Decimal earn;
    Decimal expense;
}Check;
typedef struct Weekcheck {
    int week;
    Decimal earn;
    Decimal expense;
}Weekcheck;
int comparebytime(stData * stdata1,stData * stdata2);
int comparebyid(stData * stdata1,stData * stdata2);
int comparebyuserid(stData * stdata1,stData * stdata2);
int comparebyamount(stData * stdata1,stData * stdata2);
int comparebybalance(stData * stdata1,stData * stdata2);
List check(List * list);
List weekcheck(List * list);
int howmanyweeks(int y1,int m1,int d1,int y2,int m2,int d2);
int ifthesameweek(int y1,int m1,int d1,int y2,int m2,int d2);
int ifleapyear(int y);
int caculateweekday(int y,int m,int d);

char* SelectUserUsername(User *u);
#endif
