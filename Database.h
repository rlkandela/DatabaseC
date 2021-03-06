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
      List **list;
  }DB;

  DB* createDB(void);
  void deleteDB(DB*);
  void prompt(DB*);
  void error(char*);
  void newDB(reff(DB*),Parameters*);
  void saveDB(DB*);
  int remove_directory(const char *path);
  bool DirCheck(char*,char*);
  void savecab(List*,char*);
  void listDB(DB*);
  void activeDB(reff(DB*),Parameters*);
  void newcab(DB*,Parameters*);
  void listcab(DB*);
  void activecab(DB*,Parameters*);
  void setkv(DB*,Parameters*);
  void getk(DB*,Parameters*);
  void delk(DB*,Parameters*);
  void rpushkv(DB*,Parameters*);
  void lpushkv(DB*,Parameters*);
  void rpopk(DB*,Parameters*);
  void lpopk(DB*,Parameters*);
  void rangek(DB*,Parameters*);
  void rangek1(DB*,Parameters*);
  void rangek3(DB*,Parameters*);
  void keypattern(DB*,Parameters*);
  void inck(DB*,Parameters*);
  void deck(DB*,Parameters*);
#endif
