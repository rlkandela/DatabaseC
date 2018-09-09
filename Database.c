#include "Database.h"
#include "List.h"
#include "date.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


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
  if(db != nullptr){
    if(db->name!=nullptr){
      delete(db->name);
    }
    if(db->list != nullptr){
      for(int i = 0;i<db->size;i++){
        makeNull(db->list[i]);
        deleteList(db->list[i]);
      }
      delete(db->list);
    }
    delete(db);
  }
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

void saveDB(DB* db){
  if(db != nullptr){
    if(!db->saved){
      mode_t mask = umask(0);
      umask(mask);
      if(!DirCheck(".",".DATA")){
        if(mkdir(".DATA/",0777-mask) == -1){
          perror("exe");
          exit(EXIT_FAILURE);
        }
      }
      char aux[500];
      strcpy(aux,"./.DATA/");
      strcat(aux,db->name);
      remove_directory(aux);
      if(mkdir(aux,0777-mask) == -1){
        perror("exe");
        exit(EXIT_FAILURE);
      }
      char aux2[500];
      for(int i=0;i<db->size && db->list[i]->name!=nullptr; i++){
        strcpy(aux2,aux);
        strcat(aux2,"/");
        strcat(aux2,db->list[i]->name);
        strcat(aux2,"/");
        if(mkdir(aux2,0777-mask) == -1){
          perror("exe");
          exit(EXIT_FAILURE);
        }
        savecab(db->list[i],aux2);
      }
      db->saved = true;
      prompt(db);
    }
  }
}

int remove_directory(const char *path)
{
 DIR *d = opendir(path);
 size_t path_len = strlen(path);
 int r = -1;
 if (d){
  struct dirent *p;
  r = 0;
  while(!r && (p=readdir(d))){
    int r2 = -1;
    char *buf;
    size_t len;
    if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")){
      continue;
    }
    len = path_len + strlen(p->d_name) + 2;
    buf = malloc(len);
    if (buf){
     struct stat statbuf;
     snprintf(buf, len, "%s/%s", path, p->d_name);
     if (!stat(buf, &statbuf)){
      if (S_ISDIR(statbuf.st_mode)){
        r2 = remove_directory(buf);
      }
      else{
        r2 = unlink(buf);
      }
    }
     free(buf);
    }
    r = r2;
  }
  closedir(d);
 }
 if(!r){
    r = rmdir(path);
 }
 return r;
}

bool DirCheck(char* path,char* name){
  DIR* d = opendir(path);
  if(d == NULL){
    printf("Could not open the path\n");
    return false;
  }
  bool ret=false;
  struct dirent* p;
  while((p = readdir(d)) != nullptr){
    if(!strcmp(p->d_name,name)){
      ret=true;
    }
  }
  closedir(d);
  return ret;
}

void savecab(List* l,char* path){
  char pathcopy[500];
  Node* n = l->head;
  while(n){
    strcpy(pathcopy,path);
    strcat(pathcopy,n->key);
    FILE* file;
    file = fopen(pathcopy,"w");
    if(file){
      fprintf(file,"%s",n->val);
      fclose(file);
    }else{
      perror("exe");
      exit(EXIT_FAILURE);
    }
    n=n->next;
  }
}

void listDB(DB* db){
  struct dirent* p;
  DIR* d = opendir("./.DATA/");
  if(d == NULL){
    printf("Could not open the directory, DATA folder is not created yet\n");
    prompt(db);
    return;
  }
  while((p = readdir(d)) != nullptr){
    if(p->d_name[0]!='.'){
      printf("%s\n", p->d_name);
    }
  }
  closedir(d);
  prompt(db);
}

void activeDB(DB** db,Parameters* param){
  if(DirCheck(".",".DATA")){
    if(DirCheck("./.DATA",param->param[0])){
      if((*db) != nullptr){
        delete(*db);
        (*db) = nullptr;
      }
      if((*db) == nullptr){
        (*db) = createDB();
        (*db)->name = new(char,strlen(param->param[0])+1);
        strcpy((*db)->name,param->param[0]);
        (*db)->list=new(List*,(*db)->size);
        for(int i=0;i<(*db)->size;i++){
          (*db)->list[i]=createList();
        }
        (*db)->saved = true;
        char aux [100];
        strcpy(aux,"./.DATA/");
        strcat(aux,param->param[0]);
        DIR* d = opendir(aux);
        struct dirent* p;
        int cont = 0;
        while((p = readdir(d)) != nullptr){
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")){
            continue;
          }
          if(p->d_name[0] == '.'){
            continue;
          }
          if(cont == 5){
            error("The directory has too many subdirectories");
            perror("exe");
            exit(EXIT_FAILURE);
          }
          (*db)->list[cont]->name = new(char,strlen(p->d_name)+1);
          strcpy((*db)->list[cont]->name,p->d_name);
          struct dirent* pp;
          char aux2[100];
          strcpy(aux2,aux);
          strcat(aux2,"/");
          strcat(aux2,p->d_name);
          DIR* dd = opendir(aux2);
          while((pp = readdir(dd)) != nullptr){
            if (!strcmp(pp->d_name, ".") || !strcmp(pp->d_name, "..")){
              continue;
            }
            if(pp->d_name[0]=='.'){
              continue;
            }
            char filename[200];
            strcpy(filename,aux2);
            strcat(filename,"/");
            strcat(filename,pp->d_name);
            Node* n = createNode();
            n->key = new(char,strlen(pp->d_name)+1);
            strcpy(n->key,pp->d_name);
            FILE *fil;
            fil=fopen(filename,"r");
            if(fil == nullptr){
              error("Could not open the file");
              perror("exe");
              exit(EXIT_FAILURE);
            }
            char filecont[1000];
            fscanf(fil,"%s",filecont);
            n->val = new(char,strlen(filecont)+1);
            strcpy(n->val,filecont);
            char lsprtr[2];
            char* checkList=nullptr;
            lsprtr[0]=LIST_SEPARATOR;
            lsprtr[1]=0;
            checkList=strstr(filecont,lsprtr);
            if(checkList!=nullptr){
              n->isList=true;
            }
            addNode((*db)->list[cont],n);
          }
          closedir(dd);
          cont++;
        }
        closedir(d);
      }
    }else{
      error("Database not found");
    }
  }else{
    error("DATA directory is not created yet");
  }
  prompt(*db);
}

void newcab(DB* db,Parameters* param){
  if(db != nullptr){
    bool already = false;
    bool full = true;
    for(short i=0;i<db->size;i++){
      if(db->list[i]->name == nullptr && full){
        full=false;
      }
      if(db->list[i]->name != nullptr && !already){
        if(!strcmp(db->list[i]->name,param->param[0])){
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
        if(db->list[i]->name == nullptr){
          db->list[i]->name = new(char,strlen(param->param[0])+1);
          strcpy(db->list[i]->name,param->param[0]);
          done=true;
          printf("The cabinet has been created\n");
          db->saved=false;
        }
      }
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void listcab(DB* db){
  if(db != nullptr){
    bool done=false;
    for(short i = 0;i<db->size && !done;i++){
      if(db->list[i]->name != nullptr){
        printf("%s\n",db->list[i]->name);
      }else{
        done = true;
      }
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void activecab(DB* db,Parameters* param){
  if(db != nullptr){
    bool done = false;
    for(short i=0;i<db->size && !done;i++){
      if(db->list[i]->name != nullptr){
        if(!strcmp(db->list[i]->name,param->param[0])){
          db->active=i;
          printf("The cabinet %s is active now\n",db->list[db->active]->name);
          done=true;
        }
      }
    }
    if(!done){
      printf("The database %s was not found\n",param->param[0]);
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void setkv(DB* db,Parameters *param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n){
          delete(n->val);
          n->val = new(char,strlen(param->param[1]+1));
          strcpy(n->val,param->param[1]);
          db->saved = false;
          printf("The value has been changed\n");
        }else{
          n=createNode();
          n->key = new(char,strlen(param->param[0])+1);
          n->val = new(char,strlen(param->param[1])+1);
          strcpy(n->key,param->param[0]);
          strcpy(n->val,param->param[1]);
          if(addNode(db->list[db->active],n)){
            db->saved=false;
            printf("The value was correctly added\n");
          }else{
            deleteNode(n);
            printf("Unable to set the value\n");
          }
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is no active cabinet");
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void getk(DB* db,Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n){
          if(!n->isList){
            printf("%s\n",n->val);
          }else{
            printf("%s is a list, use range to see the elements\n",n->key);
          }
        }else{
          error("Key not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is no active cabinet");
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void delk(DB* db,Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        if(quitNode(db->list[db->active],searchKey(db->list[db->active],param->param[0]))){
          printf("Key and value removed succesfuly\n");
          db->saved=false;
        }else{
          error("Key not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is no active cabinet");
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void rpushkv(DB* db, Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          rpush(param->param[1],n);
          db->saved=false;
        }else{
          error("Key not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is no active cabinet");
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void lpushkv(DB* db, Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          lpush(param->param[1],n);
          db->saved=false;
        }else{
          error("Key not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is no active cabinet");
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void rpopk(DB* db, Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          if(n->isList){
            rpop(n);
            db->saved=false;
          }else{
            error("The element is not a list");
          }
        }else{
          error("Key not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is no active cabinet");
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void lpopk(DB* db, Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          if(n->isList){
            lpop(n);
            db->saved=false;
          }else{
            error("The element is not a list");
          }
        }else{
          error("Key not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is no active cabinet");
    }
  }else{
    error("There is no active database");
  }
  prompt(db);
}

void rangek(DB* db, Parameters* param){
  if(param->size == 1){
    rangek1(db,param);
  }else if(param->size == 3){
    rangek3(db,param);
  }else{
    error("Unknown error");
  }
  prompt(db);
}

void rangek1(DB* db, Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          if(n->isList){
            Parameters* p = obtainValues(n);
            for(int i=0;i<p->size;i++){
              printf("%d: %s\n",i,p->param[i]);
            }
            deleteParam(p);
          }else{
            error("The element is not a list");
          }
        }else{
          error("Element not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is not active cabinet");
    }
  }else{
    error("There is not active database");
  }
}

void rangek3(DB* db, Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          if(n->isList){
            bool valid=true;
            for(int j=1;j<param->size;j++){
              for(int i=0;i<strlen(param->param[j]);i++){
                if(!isdigit(param->param[j][i])){
                  valid=false;
                }
              }
            }
            if(valid){
              int p1 = atoi(param->param[1]),p2 = atoi(param->param[2]),size=lsize(n);
              if(p1>=0 && p1<size && p2>=0 && p2<size && p1<=p2){
                Parameters* p = obtainValues(n);
                for(int i=p1;i<=p2;i++){
                  printf("%d: %s\n",i,p->param[i]);
                }
                deleteParam(p);
              }else{
                error("Not valid parameters");
              }
            }else{
              error("Not valid parameters");
            }
          }else{
            error("The element is not a list");
          }
        }else{
          error("Element not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is not active cabinet");
    }
  }else{
    error("There is not active database");
  }
}

void keypattern(DB* db,Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        int len = strlen(param->param[0]);
        if((len == 1)&&(param->param[0][0] == '*')){
          //ALL KEYS
          Node* n = db->list[db->active]->head;
          bool done=false;
          while(n){
            done=true;
            printf("%s: %s\n",n->key,(n->isList)? "<LIST>":n->val);
            n=n->next;
          }
          if(!done){
            printf("Not found any element\n");
          }
        }else if(param->param[0][0] == '*'){
          if(param->param[0][len-1] == '*'){
            //*SUBSTR*
            Node* n = db->list[db->active]->head;
            bool done=false;
            char aux[100];
            char* aux2=param->param[0];
            aux2++;
            strcpy(aux,aux2);
            aux[strlen(aux)-1]=0;
            while(n){
              char* ptr = strstr(n->key,aux);
              if(ptr != nullptr){
                done=true;
                printf("%s: %s\n",n->key,(n->isList)? "<LIST>":n->val);
              }
              n=n->next;
            }
            if(!done){
              printf("Not found any element\n");
            }
          }else{
            //*SUBSTR
            Node* n = db->list[db->active]->head;
            bool done=false;
            char aux[100];
            char* aux2=param->param[0];
            aux2++;
            strcpy(aux,aux2);
            while(n){
              char* ptr = strstr(n->key,aux);
              if((ptr != nullptr) && (strlen(ptr) == strlen(aux))){
                done=true;
                printf("%s: %s\n",n->key,(n->isList)? "<LIST>":n->val);
              }
              n=n->next;
            }
            if(!done){
              printf("Not found any element\n");
            }
          }
        }else if(param->param[0][len-1] == '*'){
          //SUBSTR*
          Node* n = db->list[db->active]->head;
          bool done=false;
          char aux[100];
          strcpy(aux,param->param[0]);
          aux[strlen(aux)-1]=0;
          while(n){
            char* ptr = strstr(n->key,aux);
            if((ptr != nullptr) && (strlen(ptr) == strlen(n->key))){
              done=true;
              printf("%s: %s\n",n->key,(n->isList)? "<LIST>":n->val);
            }
            n=n->next;
          }
          if(!done){
            printf("Not found any element\n");
          }
        }else{
          //KEY
          Node* n = searchKey(db->list[db->active],param->param[0]);
          if(n != nullptr){
            printf("%s: %s\n",n->key,(n->isList)? "<LIST>":n->val);
          }else{
            printf("Not found any element\n");
          }
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is not active cabinet");
    }
  }else{
    error("There is not active database");
  }
  prompt(db);
}

void inck(DB* db, Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          if(validStr(n->val)){
            Date* d = str2date(n->val);
            if(validDate(d)){
              d->day++;
              if(!validDate(d)){
                d->day=1;
                d->month++;
                if(!validDate(d)){
                  d->month=1;
                  d->year++;
                }
              }
              delete(n->val);
              n->val = date2str(d);
              db->saved=false;
            }else{
              error("Not valid date");
            }
            delete(d);
          }else{
            error("Not valid date");
          }
        }else{
          error("Element not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is not active cabinet");
    }
  }else{
    error("There is not active database");
  }
  prompt(db);
}

void deck(DB* db,Parameters* param){
  if(db != nullptr){
    if(db->active >= 0){
      if(db->list[db->active]->name != nullptr){
        Node* n = searchKey(db->list[db->active],param->param[0]);
        if(n != nullptr){
          if(validStr(n->val)){
            Date* d = str2date(n->val);
            if(validDate(d)){
              if(d->day>1){
                d->day--;
              }else{
                switch(d->month){
                  case 1:
                    d->day=31;
                    d->month=12;
                    d->year--;
                  break;
                  case 2:
                  case 4:
                  case 6:
                  case 8:
                  case 9:
                  case 11:
                    d->day=31;
                    d->month--;
                  break;
                  case 3:
                    d->day=28;
                    if(d->year%4 == 0){
                      d->day++;
                    }
                    d->month--;
                  break;
                  case 5:
                  case 7:
                  case 10:
                  case 12:
                  d->day=30;
                  d->month--;
                  break;
                }
              }
              delete(n->val);
              n->val = date2str(d);
              db->saved=false;
            }else{
              error("Not valid date");
            }
            delete(d);
          }else{
            error("Not valid date");
          }
        }else{
          error("Element not found");
        }
      }else{
        error("The cabinet does not exist");
      }
    }else{
      error("There is not active cabinet");
    }
  }else{
    error("There is not active database");
  }
  prompt(db);
}
