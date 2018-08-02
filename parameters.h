#ifndef __PARAMETER__
#define __PARAMETER__
    typedef struct Parameters{
        int size;
        char **param;
    }Parameters;
    void initParam(Parameters*);
    void deleteParam(Parameters*);
#endif
