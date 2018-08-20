#include "fdb.h"
#include "DBDefines.h"
#include <stdio.h>
#include <stdlib.h>

void startDB(void){
  Parameters* p= new(Parameters,1);
  DB* db = nullptr;
  prompt(db);
  int option=-2;
  do{
    initParam(p);
    option=askForCommand(p);
    executeCommand(&option,&db,p);
    deleteParam(p);
  }while(option!=0);
  deleteDB(db);
  delete(p);
}

void executeCommand(int* opt,DB** db,Parameters* p){
  switch (*opt) {
    case NAN:
      error("Not valid input");
      prompt(*db);
    break;
    case QUIT:
      {
        int sel=0;
        if((*db) != nullptr){
          if(!(*db)->saved){
            printf("All changes made will be lost, are you sure you want to quit? (y/n)\n");
            do{
              sel=getchar();
            }while(sel!='n' && sel!='y');
          }
          if((*db)->saved || sel=='y'){
            printf("Quitting the database. All memory was freed.\n");
          }else{
            printf("Quitting aborted\n");
            (*opt) = -1;
            prompt(*db);
          }
        }else{
          printf("Quitting the database. All memory was freed.\n");
        }
      }
    break;
    case NEWDB:
      newDB(db,p);
    break;
    case SAVEDB:
      saveDB(*db);
    break;
    case LISTDB:
      listDB(*db);
    break;
    case ACTIVEDB:
      activeDB(db,p);
    break;
    case NEWCAB:
      newcab(*db,p);
    break;
    case LISTCAB:
      listcab(*db);
    break;
    case ACTIVECAB:
      activecab(*db,p);
    break;
    case SET:
      setkv(*db,p);
    break;
    case GET:
      getk(*db,p);
    break;
    case DEL:
      delk(*db,p);
    break;
    case RPUSH:
      rpushkv(*db,p);
    break;
    case LPUSH:
      lpushkv(*db,p);
    break;
    case RPOP:
      rpopk(*db,p);
    break;
    case LPOP:
      lpopk(*db,p);
    break;
    case RANGE:
      rangek(*db,p);
    break;
    case KEY:
      keypattern(*db,p);
    break;
    case INC:
      inck(*db,p);
    break;
    case DEC:
      deck(*db,p);
    break;
  }
}
