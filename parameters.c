#include <stdio.h>
#include <stdlib.h>
#include "parameters.h"

void initParam(Parameters *param){
    param->size=0;
    param->param=NULL;
}
void deleteParam(Parameters *param){
    if(param->size!=0){
        for(int cont=0;cont<param->size;cont++){
            free(param->param[cont]);
        }
        free(param->param);
        param->size=0;
    }
    return;
}
