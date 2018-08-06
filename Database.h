#ifndef __DATABASE__
#define __DATABASE__
  typedef struct DB{
      char *name;
      int size;
      int active;
      bool saved;
      List *list;
  }DB;
#endif
