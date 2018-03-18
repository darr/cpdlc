/////////////////////////////////////
// File name : DLObject.h
// Create date : 2015-07-18 01:08
// Modified date : 2018-01-31 06:43
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLOBJECT_H
#define _DLOBJECT_H

#ifndef Class
#define Class struct
#endif

#include "DLObject_macro.h"


CLASS_TYPE
{
    void* super;
    const char* className;
    struct DLObject_func *func;
};

struct DLObject_func{
    const char* (*getClassName)(void*);
    const char* (*getClassStack)(void*);
    void (*freeSelf)(void*);
} ;

CLASS_TYPE* CLASS_NAME();
void DLFreeMemory(void*);
void* DLMallocMemory(const unsigned int);
int getDLObjectMallocCount(void);
#endif


