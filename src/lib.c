// this file is to add algorithm for search and sort and filter
include "stData.h"
include <stdio.h>

include "lib.h"
include "list.h"
//日期排序是从最早的日期开始，最近的日期结束。因为周账单算法的缘故。
int comparebytime(stData * stdata1,stData * stdata2) {
    if(stdata1->time->year > stdata2->time->year) return 0;
    if(stdata1->time->year < stdata2->time->year) return 1;
    if(stdata1->time->month > stdata2->time->month) return 0;
    if(stdata1->time->month < stdata2->time->month) return 1;
    if(stdata1->time->day > stdata2->time->day) return 0;
    if(stdata1->time->day < stdata2->time->day) return 1;
    if(stdata1->time->hour > stdata2->time->hour) return 0;
    if(stdata1->time->hour < stdata2->time->hour) return 1;
    if(stdata1->time->minute > stdata2->time->minute) return 0;
    if(stdata1->time->minute < stdata2->time->minute) return 1;
    if(stdata1->time->second > stdata2->time->second) return 0;
    if(stdata1->time->second < stdata2->time->second) return 1;
    return 0;
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
    listsort(list,comparebytime);
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
        if(current->next->value->time.year==current->value->time.year&&current->next->value->time.month==current->value->time.month)
            current = current->next;
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

int caculateweekday(int y,int m,int d) {
	if(m == 1||m == 2) {
		m+=12;
		y--;
	}
	int iweek = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	switch(iweek)
	{
	case 0:return 2;
	case 1:return 3;
	case 2:return 4;
	case 3:return 5;
	case 4:return 6;
	case 5:return 7;
	case 6:return 1;       //周日，一周的第一天，用1表示
	}
}

int ifleapyear(int y) {
    if(y%400 == 0 || (y%100 != 0 && y%4 == 0)) return 1;
    else return 0;
}

int ifthesameweek(int y1,int m1,int d1,int y2,int m2,int d2) {
    int wd1 = caculateweekday(y1,m1,d1);
    int wd2 = caculateweekday(y2,m2,d2);
    if(y1 == y2 && m1 == m2 && wd2-wd1<=7-wd1) return 1;
    if(y1 == y2 && m1!=m2)
    {
        if(m2-m1>1) return 0;
        if(m1 == 2)
        {
            if(ifleapyear(y1) && 29-d1+d2<=7-wd1) return 1;
            if(!ifleapyear(y1) && 28-d1+d2<=7-wd1) return 1;
        }
        if((m1==1||m1==3||m1==5||m1==7||m1==8||m1==10) && 31-d1+d2<=7-wd1) return 1;
        if((m1==4||m1==6||m1==9||m1==11) && 30-d1+d2<=7-wd1) return 1;
    }
    if(y1 != y2)
    {
        if(y2-y1>1 || m2>1 || m1<12) return 0;
        if(31-d1+d2<=7-wd1) return 1;
    }
}

int howmanyweeks(int y1,int m1,int d1,int y2,int m2,int d2) {
    int wd1 = caculateweekday(y1,m1,d1);
    int wd2 = caculateweekday(y2,m2,d2);
    if(y1 == y2 && m1 == m2) return (d2-d1-(7-wd1)-wd2)/7;
    if(y1 == y2 && m1 != m2)
    {
        if(m2-m1 == 1)
        {
            if(m1==1||m1==3||m1==5||m1==7||m1==8||m1==10) return (d2+31-d1-(7-wd1)-wd2)/7;
            if(m1==4||m1==6||m1==9||m1==11) return (d2+31-d1-(7-wd1)-wd2)/7;
            if(ifleapyear(y1) && m1==2) return (d2+29-d1-(7-wd1)-wd2)/7;
            if(!ifleapyear(y1) && m1==2) return (d2+28-d1-(7-wd1)-wd2)/7;
        }
        if(m2-m1>1)
        {
            if(ifleapyear(y1) && m1==1 && (m2==3 || m2==4 || m2==5)) return (30*(m2-m1-1)+31-d1+d2-(7-wd1)-wd2)/7;
            if(ifleapyear(y1) && m1==1 && m2>5) return (30*(m2-m1-1)+31-d1+d2+7-(7-wd1)-wd2)/7;
            if(!ifleapyear(y1) && m1==1 && (m2==3 || m2==4 || m2==5 || m2==6 || m2==7)) return (30*(m2-m1-1)+31-d1+d2)/7;
            if(!ifleapyear(y1) && m1==1 && m2>7) return (30*(m2-m1-1)+31-d1+d2+7-(7-wd1)-wd2)/7;
            if(ifleapyear(y1) && m1==2) return (29-m1+m2+(m2-m1-1)*30-(7-wd1)-wd2+7)/7;
            if(!ifleapyear(y1) && m1==2) return (28-m1+m2+(m2-m1-1)*30-(7-wd1)-wd2+7)/7;
            if(m1==3 || m1==5 ||m1==7 || m1==8 || m1==10) return (31-m1+m2+(m2-m1-1)*30-(7-wd1)-wd2+7)/7;
            if(m1==4 || m1==6 ||m1==9) return (30-m1+m2+(m2-m1-1)*30-(7-wd1)-wd2+7)/7;
        }
    }
    if(y1!=y2)
    {
        int i = y2-y1-1,sum = 0;
        while(i--)
        {
            if(ifleapyear(y1+i+1)) sum += 366;
            else sum += 365;
        }
        if((12-m1+m2-1)%2 == 0) sum += (12-m1+m2-1)/2*31+(12-m1+m2-1)/2*30;
        else sum += (12-m1+m2-1)/2*30+((12-m1+m2-1)/2+1)*31;
        sum += 31-d1+d2-(7-wd1)-wd2;
        return sum/7;
    }
}

List weekcheck(List * list) {
    listsort(list,comparebytime);
    List listcheck;
    listInit(&listcheck,sizeof(Weekcheck),NULL);
    Weekcheck * temvalue;
    Listnode * current = list->head;
    Decimal earnings = 0,expense = 0;
    long i = list.length;
    int j = 1,k;
    for(;i>0;i--)
    {
        if(current->value->amount > 0) earnings +=amount;
        else expense -= amount;
        if(ifthesameweek(current->value->time.year,current->value->time.month,current->value->time.day,current->next->value->time.year,current->next->value->time.month,current->next->value->time.day))
        current = current->next;
        else
        {
            temvalue = (Check *)malloc(sizeof(Weekcheck));
            temvalue->week = j++;
            temvalue->earn = earnings;
            temvalue->expense = expense;
            earnings = 0;
            expense = 0;
            if((k=howmanyweeks(current->value->time.year,current->value->time.month,current->value->time.day,current->next->value->time.year,current->next->value->time.month,current->next->value->time.day))==0)
            {
                listAppend(&listcheck, tmpvalue);
                current = current->next;
            }
            else
            {
                while(k--)
                {
                    temvalue = (Check *)malloc(sizeof(Weekcheck));
                    temvalue->week = j++;
                    temvalue->earn = earnings;
                    temvalue->expense = expense;
                    listAppend(&listcheck, tmpvalue);
                    current = current->next;
                }
            }
        }
    }
    return listcheck;
}





