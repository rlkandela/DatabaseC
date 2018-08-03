#include "lecture.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ObtainParameters(char* input, Parameters* param){
  short inSize = strlen(input);
  short comAmount = 0;
  bool emptyField = true;
  char cad[100];
  for(short cont = 0; cont<inSize; cont++){
    if(input[cont] == '"'){
      comAmount++;
      cont++;
    }
    if(comAmount%2 != 0){
      short cont2 = 0;
      while(cont<inSize && (input[cont] != '"')){
        if(input[cont] != ' '){
          emptyField = false;
        }
        cad[cont2] = input[cont];
        cont2++;
        cont++;
      }
      if(input[cont] == '"'){
        cad[cont2] = 0;
      }
    }
    emptyField=true;
  }
  return;
}

int ObtainParameters(char* input, Parameters* param){
  short inSize = strlen(input);
  short comAmount = 0;
  bool emptyField = true;
  char cad[100];
  for(short cont = 0; cont<inSize; cont++){
    short cont2 = 0;
    if(input[cont] == '"'){
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
