#ifndef __DATE_STRUCT__
#define __DATE_STRUCT__
typedef struct Date{
  short day;
  short month;
  short year;
}Date;

Date* str2date(char*);
char* date2str(Date*);
#endif
