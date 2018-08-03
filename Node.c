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

void rpush(char* toAdd, Node* n){
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

void lpush(char* toAdd, Node* n){
  n->isList = true;
  char aux [1000];
  strcpy(aux,toAdd);
  int len = strlen(aux);
  aux[len]=LIST_SEPARATOR;
  aux[len+1]=0;
  strcat(aux,n->val);
  delete(n->val);
  len = strlen(aux);
  n->val = new(char, len+1);
  strcpy(n->val,aux);
  return;
}

void rpop(Node* n){
  char aux [1000];
  bool done = false;
  for(int i = strlen(n->val)-1;i>=0 && !done; i--){
    if(n->val[i] == LIST_SEPARATOR){
      n->val[i] = 0;
      done=true;
    }
  }
  strcpy(aux,n->val);
  int len = strlen(aux);
  delete(n->val);
  n->val = new(char,len+1);
  strcpy(n->val,aux);
  return;
}
