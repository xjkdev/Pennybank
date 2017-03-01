// this file is to define data struct
#ifndef STDATA_H
#define STDATA_H

#include "list.h"
#include <time.h>

typedef struct DateTime {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
} DateTime;

typedef struct chstring {
  char *string;
  long length;
} chstring;

typedef long Decimal;

typedef struct stData {
  chstring id;
  chstring event;
  DateTime time;
  Decimal amount;
  Decimal balance;
} stData;

double DecimaltoDouble(Decimal dnum);

int DateTimevalid(DateTime dt);
DateTime tmToDatatime(struct tm *stdtm);
DateTime DateTimeNow();

void chstringInit(chstring *str);
void chstringChange(chstring *str, char *string, long length);
void chstringDestroy(chstring *str);

stData *voidtostData(void *source);
int *voidtoint(void *source);
#endif
