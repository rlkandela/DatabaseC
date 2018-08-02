#include "lecture.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ProcessWord(char* input, char** output){
  short inSize=strlen(input);
  (*output) = new(char,inSize+1);
  strcpy(*output,input);
  return;
}
