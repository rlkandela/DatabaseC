#ifndef __NODE__
#define __NODE__
#include <stdbool.h>

  typedef struct Node{
      char* key;
      char* val;
      bool isList;
      struct Node* next;
  }Node;

  Node* createNode();
  void deleteNode(Node*);
  void rpush(char*,Node*);
  void lpush(char*,Node*);
  void rpop(Node*);
  void lpop(Node*);
#endif
