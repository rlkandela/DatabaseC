#include "lecture.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int askForCommand(Parameters* param){
  char input[300];
  char* function;
  int ret=0;
  fseek(stdin,0,SEEK_END);
  gets(input);
  ret=ProcessInput(input, &function, param);
  if(ret){
    ret=NAN;
  }else{
    if(!strcmp(function,"quit")){
        ret=((param->size==0)? QUIT:NAN);
    }else if(!strcmp(function,"newdb")){
        ret=((param->size==1)? NEWDB:NAN);
    }else if(!strcmp(function,"savedb")){
        ret=((param->size==0)? SAVEDB:NAN);
    }else if(!strcmp(function,"listdb")){
        ret=((param->size==0)? LISTDB:NAN);
    }else if(!strcmp(function,"activedb")){
        ret=((param->size==1)? ACTIVEDB:NAN);
    }else if(!strcmp(function,"newcab")){
        ret=((param->size==1)? NEWCAB:NAN);
    }else if(!strcmp(function,"listcab")){
        ret=((param->size==0)? LISTCAB:NAN);
    }else if(!strcmp(function,"activecab")){
        ret=((param->size==1)? ACTIVECAB:NAN);
    }else if(!strcmp(function,"set")){
        ret=((param->size==2)? SET:NAN);
    }else if(!strcmp(function,"get")){
        ret=((param->size==1)? GET:NAN);
    }else if(!strcmp(function,"del")){
        ret=((param->size==1)? DEL:NAN);
    }else if(!strcmp(function,"rpush")){
        ret=((param->size==2)? RPUSH:NAN);
    }else if(!strcmp(function,"lpush")){
        ret=((param->size==2)? LPUSH:NAN);
    }else if(!strcmp(function,"rpop")){
        ret=((param->size==1)? RPOP:NAN);
    }else if(!strcmp(function,"lpop")){
        ret=((param->size==1)? LPOP:NAN);
    }else if(!strcmp(function,"range")){
        ret=(((param->size == 1)||(param->size == 3))? RANGE:NAN);
    }else if(!strcmp(function,"key")){
        ret=((param->size==1)? KEY:NAN);
    }else if(!strcmp(function,"inc")){
        ret=((param->size==1)? INC:NAN);
    }else if(!strcmp(function,"dec")){
        ret=((param->size==1)? DEC:NAN);
    }else ret=NAN;
  }
  delete(function);
  return ret;
}

int ProcessInput(char* input, char** function, Parameters* param){
  char cad [300];
  int cont = 0, cont2=0, inSize = strlen(input);
  while(input[cont++]==' ');
  cont--;
  while(cont<inSize && input[cont]!=' '){
    cad[cont2++] = input[cont++];
  }
  cad[cont2] = 0;
  (*function)=new(char,strlen(cad)+1);
  strcpy(*function,cad);
  cad[0] = 0;
  while(input[cont++]==' ');
  cont--;
  cont2=0;
  while(cont<inSize){
    cad[cont2++] = input[cont++];
  }
  cad[cont2] = 0;
  return ObtainParameters(cad, param);
}

int ObtainParameters(char* input, Parameters* param){
  short inSize = strlen(input);
  short comAmount = 0;
  bool emptyField = true;
  char cad[100];
  for(short cont = 0; cont<inSize; cont++){
    short cont2 = 0;
    if(input[cont] == '"'){
      cont++;
      while(input[cont]!='"' && cont<inSize){
        if(emptyField && input[cont]!=' '){
          emptyField = false;
        }
        cad[cont2++] = input[cont++];
      }
      if(input[cont]!='"' || emptyField){
        return -1;
      }else{
        cad[cont2] = 0;
        param->param = (char**)realloc(param->param,(param->size + 1) * sizeof(char*));
        param->size++;
        ProcessWord(cad,&(param->param[param->size-1]));
        do{
          cont++;
        }while(cont<inSize && input[cont]==' ');
        if(cont<inSize){
          cont--;
        }
        cad[0] = 0;
      }
    }else{
      while(input[cont]!=' ' && cont<inSize){
        cad[cont2++] = input[cont++];
      }
      cad[cont2] = 0;
      param->param = (char**)realloc(param->param,(param->size + 1) * sizeof(char*));
      param->size++;
      ProcessWord(cad,&(param->param[param->size-1]));
      do{
        cont++;
      }while(cont<inSize && input[cont]==' ');
      if(cont<inSize){
        cont--;
      }
      cad[0] = 0;
    }
    emptyField=true;
  }
  return 0;
}

void ProcessWord(char* input, char** output){
  short inSize = strlen(input);
  (*output) = new(char,inSize+1);
  strcpy(*output,input);
  return;
}
