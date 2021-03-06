#ifndef __LIST_STRUCT__
#define __LIST_STRUCT__
#include "Node.h"
#include <stdbool.h>

typedef struct List{
  char* name;
  Node* head;
  int size;
}List;

List* createList(void);
void deleteList(List*);
bool addNodeOnPosition(List*, Node*, int);
bool addNode(List*, Node*);
Node* retrieveNode(List*, int);
Node* heap(List*);
Node* searchKey(List*, char*);
Node* previousNode(List*, Node*);
bool quitNode(List*, Node*);
void makeNull(List*);
#endif
