#include "date.h"
#include "DBDefines.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Date* str2date(char* str){
  Date* ret = new(Date,1);
  char sday[3];
  char smonth[3];
  char syear[5];
  for(int i=0;i<2;i++){
    sday[i]=str[i];
  }
  sday[2]=0;
  for(int i=3;i<5;i++){
    smonth[i-3]=str[i];
  }
  smonth[2]=0;
  for(int i=6;i<10;i++){
    syear[i-6]=str[i];
  }
  syear[4]=0;
  ret->day=atoi(sday);
  ret->month=atoi(smonth);
  ret->year=atoi(syear);
  return ret;
}
