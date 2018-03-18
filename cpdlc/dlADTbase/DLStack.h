/////////////////////////////////////
// File name : DLStack.h
// Create date : 2015-07-18 14:08
// Modified date : 2018-01-31 10:56
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLSTACK_H
#define _DLSTACK_H

#include "../dlobject/DLObject.h"
#include "./DLGenericSingleChainList.h"

#undef CLASS_NAME
#undef CLASS_TYPE
#undef SUPER_CLASS_NAME

#define CLASS_NAME DLStack
#define CLASS_TYPE Class CLASS_NAME
#define SUPER_CLASS_NAME DLGenericSingleChainList


CLASS_TYPE
{
    Class SUPER_CLASS_NAME* super;
    const char* className;
    char* name;
    struct CLASS_FUNC_LIST(CLASS_NAME)* func;
    void (*printCallBack)(void**);
};

struct CLASS_FUNC_LIST(CLASS_NAME){
    DL_BASE_FUNC_POINT
    int (*isEmpty)();
    unsigned int(*getCount)();
    void (*Push)();
    void** (*Top)();
    void** (*Pop)();
    void (*Treaverse)();
    int (*freeSelf)();
    //to add function point list here
};

CLASS_TYPE* CreateDLStack();
CLASS_TYPE* CLASS_NAME();
#endif
