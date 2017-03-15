#ifndef LIB_H
#define LIB_H
#include "list.h"
#include "stData.h"

void updateBalance(List *list, long userid);

typedef struct MonthBalance {
    int year;
    int month;
    Decimal earn;
    Decimal expense;
}MonthBalance;

typedef struct WeekBalance {
    int year;
    int month;
    int day;
    Decimal earn;
    Decimal expense;
}WeekBalance;
typedef struct coordinate{
	float x;
	float y;
}Coordinate;
MonthBalance* voidtoMonthBalance(void*);
WeekBalance* voidtoWeekBalance(void*);

int calculateweekindex(int y, int m, int d);

int comparebytime(stData * stdata1,stData * stdata2);
int comparebyid(stData * stdata1,stData * stdata2);
int comparebyuserid(stData * stdata1,stData * stdata2);
int comparebyamount(stData * stdata1,stData * stdata2);
int comparebybalance(stData * stdata1,stData * stdata2);
List getMonthBalance(List * list);
List getWeekBalance(List * list);
void  getcalendar(int year, int month, int array[6][7]);

void setFilterYear(int);
void setFilterYearMonth(int, int);
void setFilterYearMonthDay(int year, int month, int day);
int filterbyYear(Record*);
int filterbyYearMonth(Record*);
int filterbyYearMonthDay(Record* data);
char* getUserUsername(User *u);
#endif
