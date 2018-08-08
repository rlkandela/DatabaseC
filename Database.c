#include "Database.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

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

void newDB(reff(DB*) db, Parameters* param){
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

void listDB(DB* db){
  char *path;
  getExecutablePath(refp(path));
  path=(char*)realloc(path,strlen(path)+6);
  strcat(path,"DATA/");
  DIR *d=opendir(path);
  if(d){
      struct dirent *p;
      p=readdir(d);
      while(p){
          if(p->d_name[0]!='.')
              printf("%s\n",p->d_name);
          p=readdir(d);
      }
  }
  delete(path);
  prompt(db);
}

void newcab(DB* db,Parameters* param){
  if(db != nullptr){
    bool already = false;
    bool full = true;
    for(short i=0;i<db->size;i++){
      if(db->list[i].name == nullptr && full){
        full=false;
      }
      if(db->list[i].name != nullptr && !already){
        if(!strcmp(db->list[i].name,param->param[0])){
          already=true;
          error("The database already has that cabinet");
        }
      }
    }
    if(full){
      error("The database is full");
    }else if(!already){
      bool done = false;
      for(short i=0;i<db->size && !done;i++){
        if(db->list[i].name == nullptr){
          db->list[i].name = new(char,strlen(param->param[0])+1);
          strcpy(db->list[i].name,param->param[0]);
          done=true;
        }
      }
    }
  }else{
    error("There is no active database");
  }
}

void getExecutablePath(reff(char*) path){
  char aux[1000];
  uint32_t s=1000;
  int tam=0;
  _NSGetExecutablePath(aux,refp(s));
  for(tam=strlen(aux)-1;tam>0;tam--){
      if(aux[tam]=='.'){
          aux[tam]='\0';
          tam=0;
      }
  }
  if(aux[strlen(aux)-1]!='/'){
      aux[strlen(aux)+1]='\0';
      aux[strlen(aux)]='/';
  }
  (*path)=new(char,strlen(aux)+1);
  strcpy(*path,aux);
}
