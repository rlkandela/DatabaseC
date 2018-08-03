#include "Node.h"
#include "DBDefines.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Node *createNode(void){
  Node* ret = new(Node,1);
  ret->key = nullptr;
  ret->val = nullptr;
  ret->next = nullptr;
  ret->isList = false;
}
