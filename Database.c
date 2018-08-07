#include "Database.h"

DB* createDB(){
  DB* ret = new(DB,1);
  ret->list=nullptr;
  ret->name=nullptr;
  ret->size=5;
  ret->active=-1;
  ret->saved=false;
  return ret;
}
