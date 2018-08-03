#ifndef __NODE__
#define __NODE__
#include <stdbool.h>
  typedef struct Node{
      char *key;
      char *val;
      bool isList;
      struct Node *next;
  }Node;
#endif
