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

typedef long Decimal;

typedef struct stData {
  long long id;
  wchar_t event[100];
  long userid;
  DateTime time;
  Decimal amount;
  Decimal balance;
} stData;

typedef struct User {
  char username[25];
  char password[25];
  wchar_t nickname[25];
  wchar_t question[50];
  wchar_t answer[50];
  long id;
} User;

double DecimaltoDouble(const Decimal dnum);
Decimal DoubletoDecimal(const double dnum);

int DateTimevalid(const DateTime dt);
DateTime tmToDatetime(struct tm *stdtm);
DateTime DateTimeNow();

stData *voidtostData(const void *source);
int *voidtoint(const void *source);
#endif
