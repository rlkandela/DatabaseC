#ifndef __DATABASE__
#define __DATABASE__
#include <stdbool.h>
#include "List.h"
#include "DBDefines.h"
#include "parameters.h"

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
  void error(void);
  void newDB(reff(DB*),Parameters*);
  void saveDB(DB*);
  void listDB(DB*);
  void activeDB(reff(DB*),Parameters*);
  void newcab(DB*,Parameters*);
  void listcab(DB*);
  void activecab(DB*,Parameters*);
  void setkv(DB*,Parameters*);
#endif
