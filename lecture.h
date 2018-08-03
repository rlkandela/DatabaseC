#ifndef __LECTURE__
#define __LECTURE__
#include "parameters.h"
#include "DBDefines.h"
    int askForCommand(Parameters*);
    int ProcessInput(char*,char**,Parameters*);
    int ObtainParameters(char*,Parameters*);
    void ProcessWord(char*, char**);
#endif
