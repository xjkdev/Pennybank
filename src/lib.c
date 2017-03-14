// this file is to add algorithm for search and sort and filter

#include <stdio.h>
#include <stdlib.h>
#include "stData.h"
#include "lib.h"
#include "list.h"

int howmanyweeks(int y1, int m1, int d1, int y2, int m2, int d2);
int ifthesameweek(int y1, int m1, int d1, int y2, int m2, int d2);
int ifleapyear(int y);
int calculateweekday(int y, int m, int d);
 int c_string[6][7];

void updateBalance(List *list,long index){
	Listnode *node;
	Decimal n;
	node=listIndexAt(list,index);

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

//���������Ǵ���������ڿ�ʼ����������ڽ�������Ϊ���˵��㷨��Ե�ʡ�
int comparebytime(stData * stdata1,stData * stdata2) {
    if(stdata1->time.year != stdata2->time.year) return (stdata1->time.year-stdata2->time.year);
    if(stdata1->time.month != stdata2->time.month) return (stdata1->time.month-stdata2->time.month);
    if(stdata1->time.day != stdata2->time.day) return (stdata1->time.day-stdata2->time.day);
    if(stdata1->time.hour != stdata2->time.hour) return (stdata1->time.hour-stdata2->time.hour);
    if(stdata1->time.minute != stdata2->time.minute) return (stdata1->time.minute-stdata2->time.minute);
    if(stdata1->time.second != stdata2->time.second) return (stdata1->time.second-stdata2->time.second);
    return 0;
}

int comparebyid(stData * stdata1,stData * stdata2) {
    return (stdata1->id-stdata2->id);
}

int comparebyuserid(stData * stdata1,stData * stdata2) {
    return (stdata1->userid-stdata2->userid);
}

int comparebyamount(stData * stdata1,stData * stdata2) {
    Decimal a1 = stdata1->amount;
    Decimal a2 = stdata2->amount;
    if(a1 < 0) a1 = -a1;
    if(a2 < 0) a2 = -a2;
    return (a1-a2);
}

int comparebybalance(stData * stdata1,stData * stdata2) {
    return (stdata1->balance-stdata2->balance);
}




List getMonthBalance(List * list) {
    listSort(list,(int(*)(void*,void*))comparebytime);
    List listcheck;
    listInit(&listcheck, sizeof(MonthBalance), NULL);
    MonthBalance * tmpvalue;
    Listnode *current = list->head;
    Decimal earnings = 0,expense = 0;

    if(current->next == NULL)
    {
        if(voidtostData(current->value)->amount > 0)
            earnings += voidtostData(current->value)->amount;
        else
            expense -= voidtostData(current->value)->amount;
        tmpvalue = (MonthBalance *)malloc(sizeof(MonthBalance));
        tmpvalue->year = voidtostData(current->value)->time.year;
        tmpvalue->month = voidtostData(current->value)->time.month;
        tmpvalue->earn = earnings;
        tmpvalue->expense = expense;
        listAppend(&listcheck, tmpvalue);
        return listcheck;
    }
    else {

    while(current != NULL)
    {
        if(voidtostData(current->value)->amount > 0)
            earnings += voidtostData(current->value)->amount;
        else
            expense -= voidtostData(current->value)->amount;
        if(current->next != NULL){

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
        else {
            tmpvalue = (MonthBalance *)malloc(sizeof(MonthBalance));
            tmpvalue->year = voidtostData(current->value)->time.year;
            tmpvalue->month = voidtostData(current->value)->time.month;
            tmpvalue->earn = earnings;
            tmpvalue->expense = expense;
            listAppend(&listcheck, tmpvalue);
            current = current->next;
        }
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
	case 6:return 1;       //���գ�һ�ܵĵ�һ�죬��1��ʾ
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
    if(y1 == y2 && m1 == m2 && d2-d1<=7-wd1) return 1;
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

void solvesunday(WeekBalance * tmp,int y,int m,int d)
{
    int wd = calculateweekday(y,m,d);
    if(d >= wd)
    {
        tmp->year = y;
        tmp->month = m;
        tmp->day = d-wd+1;
    }
    else
    {
        if(m == 1)
        {
            tmp->year = y-1;
            tmp->month = 12;
            tmp->day = 32-wd+d;
        }
        else
        {
            if(m==2 || m==4 || m==6 || m==8 || m==9 || m==11)
            {
                tmp->year = y;
                tmp->month = m-1;
                tmp->day = 32-wd+d;
            }
            else if(m==5 || m==7 || m==10 || m==12)
            {
                tmp->year = y;
                tmp->month = m-1;
                tmp->day = 31-wd+d;
            }
            else if(ifleapyear(y))
            {
                tmp->year = y;
                tmp->month = m-1;
                tmp->day = 30-wd+d;
            }
            else
            {
                tmp->year = y;
                tmp->month = m-1;
                tmp->day = 29-wd+d;
            }
        }
    }
}

List getWeekBalance(List * list) {
    listSort(list,(int(*)(void*,void*))comparebytime);
    List listcheck;
    listInit(&listcheck,sizeof(WeekBalance),NULL);
    WeekBalance * tmpvalue;
    Listnode * current = list->head;
    Decimal earnings = 0,expense = 0;
    int j = 1,k;

    if(current->next == NULL)
    {
        Decimal amount = voidtostData(current->value)->amount;
        if(amount > 0) earnings +=amount;
        else expense -= amount;
        DateTime currenttime = voidtostData(current->value)->time;
        tmpvalue = (WeekBalance *)malloc(sizeof(WeekBalance));
        solvesunday(tmpvalue,currenttime.year,currenttime.month,currenttime.day);
        tmpvalue->earn = earnings;
        tmpvalue->expense = expense;
        listAppend(&listcheck, tmpvalue);
        return listcheck;
    }

    else {

    while (current != NULL)
    {
        Decimal amount = voidtostData(current->value)->amount;
        if(amount > 0) earnings +=amount;
        else expense -= amount;

        if(current->next != NULL) {

            DateTime currenttime = voidtostData(current->value)->time;
            DateTime nexttime = voidtostData(current->next->value)->time;
            if(ifthesameweek(currenttime.year,currenttime.month,currenttime.day,nexttime.year,nexttime.month,nexttime.day))
            current = current->next;
            else
            {
                tmpvalue = (WeekBalance *)malloc(sizeof(WeekBalance));
                solvesunday(tmpvalue,currenttime.year,currenttime.month,currenttime.day);
                tmpvalue->earn = earnings;
                tmpvalue->expense = expense;
                earnings = 0;
                expense = 0;
                listAppend(&listcheck, tmpvalue);
                current = current->next;
            }
        }
        else {
            tmpvalue = (WeekBalance *)malloc(sizeof(WeekBalance));
            DateTime currenttime = voidtostData(current->value)->time;
            solvesunday(tmpvalue,currenttime.year,currenttime.month,currenttime.day);
            tmpvalue->earn = earnings;
            tmpvalue->expense = expense;
            earnings = 0;
            expense = 0;
            listAppend(&listcheck, tmpvalue);
            current = current->next;
        }
    }

    }
    return listcheck;
}

void  calendar(int year,int month,int array[6][7]){
	int n=calculateweekday(year,month,1);
    int i,j;
    int count=1;
    int d;
    int fmonth=month-1;
	int t,b;
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
       d=31;
    else if(month!=2)
       d=30;
    else{
    	 if((year%4 == 0&& year%100 != 0)||(year%400 == 0))
    	   d=29;
    	else
    	   d=28;
	}
	for(i=0;i<6;i++){
		for(j=i==0?n-1:0;j<7;j++){
			array[i][j]=count<=d ? count : -(count-d);
			count++;
		}
	}
    count=1;
    t=i;
	b=j;
    for(;i<6;i++){
    	if(i==t){
           for(j=b;j<7;j++)
		     array[i][j]=-count;
			 count++;
		}
		else {
			for(j=0;j<7;j++)
			  array[i][j]=-count;
			  count++;
		}
	}

	if(fmonth==1||fmonth==3||fmonth==5||fmonth==7||fmonth==8||fmonth==10||month==12)
       d=31;
    else if(fmonth!=2)
       d=30;
    else{
        if((year%4 == 0&&year%100 != 0)||(year%400 == 0))
        d=29;
        else
         d=28;
	}
	if(fmonth!=0&&array[0][0]!=1){
		for(j=n-2;j>=0;j--){
			array[0][j]=-(d--);
		}
	}
	else{
		fmonth=12;
		d=31;
		for(j=n-2;j>=0;j--){
			array[0][j]=-(d--);
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


// test main

//int main() {
//    int i;
//    List list;
//    listInit(&list, sizeof(stData), NULL);
//    stData *tmpvalue;
//    int d=2012;
//    for (i = 1; i <= 6; i++) {
//       tmpvalue = (stData *)malloc(sizeof(stData));
//       tmpvalue->time.year=d++;
//       tmpvalue->time.month=11;                             //��������ʽ�Ļ��ͳ����ˣ�Ŀǰֻ�����ֶ��ĵ���ʽ
//       tmpvalue->time.day=8;
//       tmpvalue->amount=10;
//       listAppend(&list, tmpvalue);
//    }
//	List listcheck = getMonthBalance(&list);
//	Listnode * current1 = listcheck.head;
//    if(current1->next == NULL)
//		printf("%d %d %ld %ld\n",((MonthBalance *)(current1->value))->year,((MonthBalance *)(current1->value))->month,
//		((MonthBalance *)(current1->value))->earn,((MonthBalance *)(current1->value))->expense);
//	else
//	{
//		while(current1 != NULL)
//		{
//			printf("%d %d %ld %ld\n",((MonthBalance *)(current1->value))->year,((MonthBalance *)(current1->value))->month,
//			((MonthBalance *)(current1->value))->earn,((MonthBalance *)(current1->value))->expense);
//			current1 = current1->next;
//		 }
//	 }
//    List weeklistcheck = getWeekBalance(&list);
//	Listnode * current2 = weeklistcheck.head;
//	if(current2->next == NULL)
//		printf("%d %d %d %ld %ld\n",((WeekBalance *)(current2->value))->year,((WeekBalance *)(current2->value))->month,
//         ((WeekBalance *)(current2->value))->day,((WeekBalance *)(current2->value))->earn,((WeekBalance *)(current2->value))->expense);
//	else
//	{
//		while(current2 != NULL)
//		{
//			printf("%d %d %d %ld %ld\n",((WeekBalance *)(current2->value))->year,((WeekBalance *)(current2->value))->month,
//            ((WeekBalance *)(current2->value))->day,((WeekBalance *)(current2->value))->earn,((WeekBalance *)(current2->value))->expense);
//			current2 = current2->next;
//		}
//	}
//    return 0;
//}

/*int main( ){
	int array[6][7];
	int i,j;
	calendar(2017,2,array);
	printf("������     ����һ     ���ڶ�     ������     ������     ������     ������\n");
	for(i=0;i<6;i++){
		for(j=0;j<7;j++)
			printf("%4d       ",array[i][j]);
	printf("\n");
	}

	return 0;
}*/

