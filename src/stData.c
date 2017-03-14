#include "stData.h"

stData *voidtostData(const void *source) { return (stData *)source; }
int *voidtoint(const void *source) { return (int *)source; }
User *voidtoUser(const void *source) { return (User *)source; };

DateTime tmToDatetime(struct tm *stdtm) {
  DateTime dt;
  dt.year = stdtm->tm_year;
  dt.month = stdtm->tm_mon;
  dt.day = stdtm->tm_mday;
  dt.hour = stdtm->tm_hour;
  dt.minute = stdtm->tm_min;
  dt.second = stdtm->tm_sec;
  return dt;
}

double DecimaltoDouble(const Decimal dnum) { return dnum / 100.0; }
Decimal DoubletoDecimal(const double dnum) { return (Decimal)(dnum * 100); }

DateTime DateTimeNow() {
    struct tm *stdtm;
  time_t now;
  time(&now);
  stdtm = localtime(&now);
  return tmToDatetime(stdtm);
}

// Return 0 if invalid, if if valid
int DateTimevalid(const DateTime dt) {
  if (dt.hour >= 23 || dt.hour < 0) {
    return 0;
  }
  if (dt.minute < 0 || dt.minute >= 60) {
    return 0;
  }
  if (dt.second < 0 || dt.second >= 60) {
    return 0;
  }
  if (dt.month < 1 || dt.month > 12) {
    return 0;
  }
  if (dt.year < 0) {
    return 0;
  }
  if (dt.day < 0) {
    return 0;
  }

  // big month , aka 1 3 5 7 8 10 12
  if ((dt.month <= 7 && dt.month % 2 == 1) ||
      (dt.month >= 8 && dt.month % 2 == 0)) {
    if (dt.day > 31)
      return 0;
  } else if (dt.month != 2) {
    if (dt.day > 30)
      return 0;
  } else if (dt.month == 2) {
    if ((dt.year % 4 == 0 && dt.year % 100 != 0) || dt.year % 400 == 0) {
      if (dt.day > 29) {
        return 0;
      }
    } else if (dt.day > 28) {
      return 0;
    }
  }
  return 1;
}
