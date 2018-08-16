#include "Node.h"
#include "DBDefines.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

Node *createNode(void){
  Node* ret = new(Node,1);
  ret->key = nullptr;
  ret->val = nullptr;
  ret->next = nullptr;
  ret->isList = false;
  return ret;
}

void deleteNode(Node* n){
  if(n != nullptr){
    if(n->val){
      delete(n->val);
    }
    if(n->key){
      delete(n->key);
    }
    delete(n);
  }
}

void rpush(char* toAdd, Node* n){
  n->isList = true;
  char aux [1000];
  strcpy(aux,n->val);
  int len = strlen(n->val);
  aux[len] = LIST_SEPARATOR;
  aux[len+1] = 0;
  strcat(aux,toAdd);
  len = strlen(aux);
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
  bool stiList=false;
  for(int i=0;!stiList && i<strlen(n->val);i++){
    if(n->val[i]==LIST_SEPARATOR){
      stiList=true;
    }
  }
  n->isList=stiList;
  return;
}

void lpop(Node* n){
  int i,len=strlen(n->val);
  char aux [1000];
  for(i=0;i<len && n->val[i]!=LIST_SEPARATOR;i++);
  i++;
  int j;
  for(j=0;i<=len;i++,j++){
    aux[j]=n->val[i];
  }
  len = strlen(aux);
  delete(n->val);
  n->val = new(char,len+1);
  strcpy(n->val,aux);
  bool stiList=false;
  for(int i=0;!stiList && i<strlen(n->val);i++){
    if(n->val[i]==LIST_SEPARATOR){
      stiList=true;
    }
  }
  n->isList=stiList;
  return;
}

int lsize(Node* n){
  int ret=0;
  for(int i=0;i<strlen(n->val);i++){
    if(n->val[i]==LIST_SEPARATOR){
      ret++;
    }
  }
  return ++ret;
}

Parameters* obtainValues(Node* n){
  char aux[100];
  Parameters* ret = new(Parameters,1);
  initParam(ret);
  ret->size = lsize(n);
  ret->param = new(char*,ret->size);
  for(int i=0,j=0,k=0;i<=strlen(n->val);i++,j++){
    if((n->val[i] == LIST_SEPARATOR) || (n->val[i] == '\0')){
      aux[j]=0;
      j=-1;
      ret->param[k] = new(char,strlen(aux)+1);
      strcpy(ret->param[k],aux);
      k++;
    }else{
      aux[j]=n->val[i];
    }
  }
  return ret;
}
