#include "date.h"
#include "DBDefines.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

Date* str2date(char* str){
  Date* ret = new(Date,1);
  char sday[3];
  char smonth[3];
  char syear[5];
  for(int i=0;i<4;i++){
    syear[i]=str[i];
  }
  syear[4]=0;
  for(int i=5;i<7;i++){
    smonth[i-5]=str[i];
  }
  smonth[2]=0;
  for(int i=8;i<10;i++){
    sday[i-8]=str[i];
  }
  sday[2]=0;
  ret->day=atoi(sday);
  ret->month=atoi(smonth);
  ret->year=atoi(syear);
  return ret;
}

char* date2str(Date* date){
  char* ret=new(char,11);
  ret[0]=(date->year/1000)+'0';
  ret[1]=((date->year/100)%10)+'0';
  ret[2]=((date->year/10)%10)+'0';
  ret[3]=(date->year%10)+'0';
  ret[4]='/';
  ret[5]=(date->month/10)+'0';
  ret[6]=(date->month%10)+'0';
  ret[7]='/';
  ret[8]=(date->day/10)+'0';
  ret[9]=(date->day%10)+'0';
  ret[10]=0;
  return ret;
}

bool validStr(char* str){
  if(strlen(str)==10){
    for(int i=0;i<10;i++){
      if(i==4 || i==7){
        i++;
      }
      if(!isdigit(str[i])){
        return false;
      }
    }
    if((str[4]!='/' && str[4]!='-') || (str[7]!='/' && str[7]!='-')){
      return false;
    }
    return true;
  }
  return false;
}

bool validDate(Date* date){
  switch (date->month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      if(date->day>=1 && date->day<=31){
        return true;
      }else{
        return false;
      }
    break;
    case 4:
    case 6:
    case 9:
    case 11:
      if(date->day>=1 && date->day<=30){
        return true;
      }else{
        return false;
      }
    break;
    case 2:
     if(date->year%4==0){
       if(date->day>=1 && date->day<=29){
         return true;
       }else{
         return false;
       }
     }else{
       if(date->day>=1 && date->day<=28){
         return true;
       }else{
         return false;
       }
     }
    break;
    default:
      return false;
  }
}
