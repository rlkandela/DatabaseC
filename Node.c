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

void deleteNode(Node* n){
  delete(n->val);
  delete(n->key);
  delete(n);
}

void rpush(char* toAdd,Node* n){
  n->isList = true;
  char aux [1000];
  strcpy(aux,n->val);
  int len = strlen(n->val);
  aux[len] = LIST_SEPARATOR;
  aux[len+1] = 0;
  strcat(aux,toAdd);
  len = strlen(n->val);
  delete(n->val);
  n->val = new(char,len+1);
  strcpy(n->val,aux);
  return;
}
