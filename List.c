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

bool addNodeOnPosition(List* l, Node* n, int p){
  if(p==1){
    n->next = l->head;
    l->head = n;
    return true;
  }else if(p>l->size+1){
    return addNodeOnPosition(l,n,l->size+1);
  }else if(p>1){
    Node* pn=retrieveNode(l,p-1);
    n->next = pn->next;
    pn->next = n;
    return true;
  }
  return false;
}

bool addNode(List* l, Node* n){
  return addNodeOnPosition(l,n,l->size+1);
}

Node* retrieveNode(List* l, int p){
  if(p>=1){
    Node *ret = l->head;
    for(int i=1;i<p;i++){
      if(ret != nullptr){
        ret = ret->next;
      }
    }
    return ret;
  }
  return nullptr;
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

Node* searchKey(List* l, char* str){
  Node* n=l->head;
  if(n!=nullptr){
    while(n!=nullptr){
      if(strcmp(n->key,str)==0){
        return n;
      }else{
        n=n->next;
      }
    }
  }
  return nullptr;
}

Node* previousNode(List* l, Node* nd){
  Node* n=l->head;
  if(n!=nullptr){
    Node* nn=l->head->next;
    while(nn != nullptr){
      if(nd==nn){
        return n;
      }else{
        nn=nn->next;
        n=n->next;
      }
    }
  }
  return nullptr;
}

bool quitNode(List* l, Node* n){
  if(n == l->head){
    l->head = l->head->next;
    deleteNode(n);
    return true;
  }else{
    Node* pn = previousNode(l,n);
    if(pn != nullptr){
      pn->next = n->next;
      deleteNode(n);
      return true;
    }
  }
  return false;
}

void makeNull(List* l){
  while(quitNode(l,l->head));
}
