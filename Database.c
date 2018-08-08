#include "Database.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>

DB* createDB(){
  DB* ret = new(DB,1);
  ret->list=nullptr;
  ret->name=nullptr;
  ret->size=5;
  ret->active=-1;
  ret->saved=false;
  return ret;
}

void deleteDB(DB* db){
  if(db->name!=nullptr){
    delete(db->name);
  }
  if(db->list != nullptr){
    for(int i = 0;i<db->size;i++){
      makeNull(db->list[i]);
      deleteList(db->list[i]);
    }
  }
  delete(db);
}

void prompt(DB* db){
  if(db != nullptr){
    if(db->saved){
      printf("[%s]>> ",db->name);
    }else{
      printf("[%s]*>> ",db->name);
    }
  }else{
    printf("[.]>> ");
  }
}

void error(char* type){
  printf("Error. %s\n",type);
}

void newDB(reff(DB*) db, Parameters* param{
  if((*db)!=nullptr){
    deleteDB(*db);
    (*db)=nullptr;
  }
  if((*db)==nullptr){
    (*db)=createDB();
    (*db)->name=new(char,strlen(param->param[0])+1);
    strcpy((*db)->name,param->param[0]);
    (*db)->list=new(List*,(*db)->size);
    for(int i=0;i<(*db)->size;i++){
      (*db)->list[i]=createList();
    }
    prompt(*db);
  }
}
