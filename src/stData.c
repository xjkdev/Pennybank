#include "stData.h"

inline stData *voidtostData(void *source) { return (stData *)source; }
inline int *voidtoint(void *source) { return (int *)source; }

DateTime tmToDatatime(struct tm *stdtm) {
  DateTime dt;
  dt.year = stdtm->tm_year;
  dt.month = stdtm->tm_mon;
  dt.day = stdtm->tm_mday;
  dt.hour = stdtm->tm_hour;
  dt.minute = stdtm->tm_min;
  dt.second = stdtm->tm_sec;
  return dt;
}
