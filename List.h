#ifndef __LIST_STRUCT__
#define __LIST_STRUCT__
#include "Node.h"

typedef struct List{
  char* name;
  Node* head;
  int size;
}List;

#endif
