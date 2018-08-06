#ifndef __DATABASE__
#define __DATABASE__
#include <stdbool.h>

  typedef struct DB{
      char *name;
      int size;
      int active;
      bool saved;
      List *list;
  }DB;

  DB* createDB(void);
  void deleteDN();
#endif
