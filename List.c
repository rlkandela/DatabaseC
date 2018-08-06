#include "List.h"
#include "DBDefines.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

List* createList(void){
  List* ret = new(List,1);
  ret->name = nullptr;
  ret->size = 0;
  ret->head = nullptr;
  return ret;
}

void deleteList(List* l){
  delete(l->name);
  delete(l);
  return;
}

Node* heap(List* l){
  Node* n = l->head;
  if(n!=nullptr){
    while(n->next!=nullptr){
      n=n->next;
    }
  }
  return n;
}
