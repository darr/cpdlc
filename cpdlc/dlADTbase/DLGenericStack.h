/////////////////////////////////////
// File name : DLGenericStack.h
// Create date : 2015-07-18 14:08
// Modified date : 2018-01-31 10:47
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLGenericStack_H
#define _DLGenericStack_H

#include "../dlobject/DLObject.h"
#include "../dlADTbase/DLADTBase.h"

#undef CLASS_NAME
#undef CLASS_TYPE
#undef SUPER_CLASS_NAME

#define CLASS_NAME DLGenericStack
#define CLASS_TYPE Class CLASS_NAME
#define SUPER_CLASS_NAME DLADTBase


CLASS_TYPE
{
    Class SUPER_CLASS_NAME* super;
    const char* className;
    char* name;
    struct CLASS_FUNC_LIST(CLASS_NAME)* func;
    int count;
    void** Next;
};

struct CLASS_FUNC_LIST(CLASS_NAME){
    DL_BASE_FUNC_POINT
    int (*IsEmpty)();
    void (*Push)();
    void** (*Top)();
    void (*Pop)();
    int (*freeSelf)();
    //to add function pointer list here
};

CLASS_TYPE* CreateDLGenericStack();
CLASS_TYPE* CLASS_NAME();
#endif
