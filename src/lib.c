// this file is to add algorithm for search and sort and filter

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int howmanyweeks(int y1, int m1, int d1, int y2, int m2, int d2);
int ifthesameweek(int y1, int m1, int d1, int y2, int m2, int d2);
int ifleapyear(int y);
int calculateweekday(int y, int m, int d);
 int c_string[6][7];

void updateBalance(List *list,long index){
	Listnode *node;
	node=listIndexAt(list,index);
	Decimal n;
	n=voidtostData(node->value)->amount;
	node=node->next;
    while (node != NULL) {
        voidtostData(node->value)->balance -= n;
        node = node->next;
    }
}


MonthBalance * voidtoMonthBalance(void * source) {
    return (MonthBalance*)(source);
}

WeekBalance * voidtoWeekBalance(void * source) {
    return (WeekBalance*)(source);
}

//日期排序是从最早的日期开始，最近的日期结束。因为周账单算法的缘故。
int comparebytime(stData * stdata1,stData * stdata2) {
    if(stdata1->time.year > stdata2->time.year) return 0;
    else 
    if(stdata1->time.month > stdata2->time.month) return 0;
    else
    if(stdata1->time.day > stdata2->time.day) return 0;
    else
    if(stdata1->time.hour > stdata2->time.hour) return 0;
    else
    if(stdata1->time.minute > stdata2->time.minute) return 0;
    else
    if(stdata1->time.second > stdata2->time.second) return 0;
    else
    return 0;
}

int comparebyid(stData * stdata1,stData * stdata2) {
    if(stdata1->id > stdata2->id) return 0;
    else return 1;
}

int comparebyuserid(stData * stdata1,stData * stdata2) {
    if(stdata1->userid > stdata2->userid) return 0;
    else return 1;
}

int comparebyamount(stData * stdata1,stData * stdata2) {
    if(stdata1->amount > stdata2->amount) return 0;
    else return 1;
}

int comparebybalance(stData * stdata1,stData * stdata2) {
    if(stdata1->balance > stdata2->balance) return 0;
    else return 1;
}




List getMonthBalance(List * list) {
    listSort(list,comparebytime);
    List listcheck;
    listInit(&listcheck, sizeof(MonthBalance), NULL);
    MonthBalance * tmpvalue;
    Listnode *current = list->head;
    Decimal earnings = 0,expense = 0;
    while(current->next != NULL)
    {
        if(voidtostData(current->value)->amount > 0)
            earnings += voidtostData(current->value)->amount;
        else 
            expense -= voidtostData(current->value)->amount;
        if(voidtostData(current->next->value)->time.year==voidtostData(current->value)->time.year &&
            voidtostData(current->next->value)->time.month==voidtostData(current->value)->time.month)
            current = current->next;
        else {
            tmpvalue = (MonthBalance *)malloc(sizeof(MonthBalance));
            tmpvalue->year = voidtostData(current->value)->time.year;
            tmpvalue->month = voidtostData(current->value)->time.month;
            tmpvalue->earn = earnings;
            tmpvalue->expense = expense;
            listAppend(&listcheck, tmpvalue);
            current = current->next;
            earnings = 0;
            expense = 0;
        }
    }
    return listcheck;
}

int calculateweekday(int y,int m,int d) {
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
    return -1;
}

int ifleapyear(int y) {
    if(y%400 == 0 || (y%100 != 0 && y%4 == 0)) return 1;
    else return 0;
}

int ifthesameweek(int y1,int m1,int d1,int y2,int m2,int d2) {
    int wd1 = calculateweekday(y1,m1,d1);
    int wd2 = calculateweekday(y2,m2,d2);
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
    return 0;
}

int howmanyweeks(int y1,int m1,int d1,int y2,int m2,int d2) {
    int wd1 = calculateweekday(y1,m1,d1);
    int wd2 = calculateweekday(y2,m2,d2);
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
    return 0;
}

List getWeekBalance(List * list) {
    listSort(list,comparebytime);
    List listcheck;
    listInit(&listcheck,sizeof(WeekBalance),NULL);
    WeekBalance * tmpvalue;
    Listnode * current = list->head;
    Decimal earnings = 0,expense = 0;
    int j = 1,k;
    while (current->next != NULL)
    {
        Decimal amount = voidtostData(current->value)->amount;
        if(amount > 0) earnings +=amount;
        else expense -= amount;
        DateTime currenttime = voidtostData(current->value)->time;
        DateTime nexttime = voidtostData(current->next->value)->time;
        if(ifthesameweek(currenttime.year,currenttime.month,currenttime.day,nexttime.year,nexttime.month,nexttime.day))
        current = current->next;
        else
        {
            tmpvalue = (WeekBalance *)malloc(sizeof(WeekBalance));
            tmpvalue->week = j++;
            tmpvalue->earn = earnings;
            tmpvalue->expense = expense;
            earnings = 0;
            expense = 0;
            if((k=howmanyweeks(currenttime.year, currenttime.month, currenttime.day, nexttime.year, nexttime.month, nexttime.day))==0)
            {
                listAppend(&listcheck, tmpvalue);
                current = current->next;
            }
            else
            {
                while(k--)
                {
                    tmpvalue = (WeekBalance *)malloc(sizeof(WeekBalance));
                    tmpvalue->week = j++;
                    tmpvalue->earn = earnings;
                    tmpvalue->expense = expense;
                    listAppend(&listcheck, tmpvalue);
                    current = current->next;
                }
            }
        }
    }
    return listcheck;
}

void  calendar(int year,int month,int a[][7]){
	int n=calculateweekday(year,month,1);
    int i,j;
    int count=1;
    int d;
    int fmonth=month-1;
	int a,b;
	if(month==1&&month==3&&month==5&&month==7&&month==8&&month==10&&month==12)
       d=31;
    else if(month!=2)
       d=30;
    else{
    	if(year%100==0)
    	  if(n%400==0)
    	    d=29;
    	  else
    	    d=28;
    	else
    	 if(n%4==0)
    	   d=29;
    	 else
    	   d=28;  
	}
	for(i=0;(i<6)&&(count<d);i++){
		for(j=0;j<7;j++){
			if(i==0){
				j=n-1;
				a[i][j]=count;
			}
			else{
			  a[i][j]=count;
			}
			count++;
			if(count>=d)
			  break;
		}
	}
    count=1;
    a=i;
    b=j;
    for(i=a;i<6;i++){
    	if(i==a){
           for(j=b;j<7;j++)
		     a[i][j]=-count;
			 count++;		
		}
		else {
			for(j=0;j<7;j++)
			  a[i][j]=-count;
			  count++;
		}
	}
	
	if(fmonth==1&&fmonth==3&&fmonth==5&&fmonth==7&&fmonth==8&&fmonth==10&&month==12)
       d=31;
    else if(fmonth!=2)
       d=30;
    else{
    	if(year%100==0)
    	  if(n%400==0)
    	    d=29;
    	  else
    	    d=28;
    	else
    	 if(n%4==0)
    	   d=29;
    	 else
    	   d=28;  
	}
	if(fmonth!=0&&a[0][0]!=1){
		for(j=n-1;j>=0;j--){
			a[0][j]=-(d--);
		}
	}
	else{
		fmonth=12;
		d=31;
		for(j=n-1;j>=0;j--){
			a[0][j]=-(d--);
		}
		
	}

}

char* getUserUsername(User *u) {
    return u->username;
}

static int filteryear;
static int filtermonth;

void setFilterYear(int year) {
    filteryear = year;
}
void setFilterYearMonth(int year, int month) {
    filteryear = year;
    filtermonth = month;
}
int filterbyYear(Record* data) {
    return (filteryear == data->time.year);
}
int filterbyYearMonth(Record* data) {
    return (filteryear == data->time.year && filtermonth == data->time.month);
}
