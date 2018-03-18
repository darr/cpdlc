/////////////////////////////////////
// File name : DLQueue.h
// Create date : 2015-07-18 14:08
// Modified date : 2018-01-31 10:54
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLQueue_H
#define _DLQueue_H

#include "../dlobject/DLObject.h"
#include "./DLGenericSingleChainList.h"

#undef CLASS_NAME
#undef CLASS_TYPE
#undef SUPER_CLASS_NAME

#define CLASS_NAME DLQueue
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
    void (*Enqueue)();
    void** (*Dequeue)();
    void (*Treaverse)();
    int (*freeSelf)();
    //to add function point list here
};

CLASS_TYPE* CreateDLQueue();
CLASS_TYPE* CLASS_NAME();
#endif
