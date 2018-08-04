#include "List.h"
#include "DBDefines.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

List* createList(void){
  List* ret = new(List,1);
  ret->name = nullptr;
  ret->size = 0;
  ret->head = nullptr;
  return ret;
}
