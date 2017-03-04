// this file is to add algorithm for search and sort and filter
include "stData.h"
include <stdio.h>

include "lib.h"
include "list.h"
int compare by time(stData * stdata1,stData * stdata2) {
    if(stdata1->time->year > stdata2->time->year) return 1;
    if(stdata1->time->year < stdata2->time->year) return 0;
    if(stdata1->time->month > stdata2->time->month) return 1;
    if(stdata1->time->month < stdata2->time->month) return 0;
    if(stdata1->time->day > stdata2->time->day) return 1;
    if(stdata1->time->day < stdata2->time->day) return 0;
    if(stdata1->time->hour > stdata2->time->hour) return 1;
    if(stdata1->time->hour < stdata2->time->hour) return 0;
    if(stdata1->time->minute > stdata2->time->minute) return 1;
    if(stdata1->time->minute < stdata2->time->minute) return 0;
    if(stdata1->time->second > stdata2->time->second) return 1;
    if(stdata1->time->second < stdata2->time->second) return 0;
    return 1;
}

int comparebyid(stData * stdata1,stData * stdata2) {
    if(stData1->id > stData2->id) return 0;
    else return 1;
}

int comparebyuserid(stData * stdata1,stData * stdata2) {
    if(stData1->userid > stData2->userid) return 0;
    else return 1;
}

int comparebyamount(stData * stdata1,stData * stdata2) {
    if(stData1->amount > stData2->amount) return 0;
    else return 1;
}

int comparebybalance(stData * stdata1,stData * stdata2) {
    if(stData1->balance > stData2->balance) return 0;
    else return 1;
}


void listSort(List *list, void (*compare)(void * a, void * b)) {
    int j;
    long p;
    void * tmp;
    Listnode * current;
    for(p=1;p < list->length;p++)
    {
        current = listIndexAt(list, p);
        tmp = current->value;
        for(j=p;j>0 && (*compare)(current->value,current->prev->value);j--)
        {
            current->value = current->prev->value;
            current = current->prev;
        }
        current->value = tmp;
    }
}

List check(List * list) {
    List listcheck;
    listInit(&listcheck, sizeof(Check), NULL);
    Check * temvalue;
    Listnode * current = list->head;
    Decimal earnings = 0,expense = 0;
    long i = list.length;
    for(;i>0;i--)
    {
        if(current->value->amount > 0) earnings +=amount;
        else expense -= amount;
        if(current->next->value->time.year==current->value->time.year&&current->next->value->time.month==current->value->time.month) {
            current = current->next;
        }
        else {
            temvalue = (Check *)malloc(sizeof(Check));
            temvalue->year = current->value->time.year;
            temvalue->month = current->value->time.month;
            temvalue->earn = earnings;
            temvalue->expense = expense;
            listAppend(&listcheck, tmpvalue);
            current = current->next;
            earnings = 0;
            expense = 0;
        }
    }
    return listcheck;
}





