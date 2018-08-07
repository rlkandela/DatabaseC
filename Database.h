#ifndef __DATABASE__
#define __DATABASE__
#include <stdbool.h>
#include "List.h"

  typedef struct DB{
      char *name;
      int size;
      int active;
      bool saved;
      List *list;
  }DB;

  DB* createDB(void);
  void deleteDB(DB*);
  void prompt(DB*);
#endif
