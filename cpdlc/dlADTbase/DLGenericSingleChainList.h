/////////////////////////////////////
// File name : DLGenericSingleChainList.h
// Create date : 2015-07-18 14:08
// Modified date : 2018-01-31 10:46
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLGenericChainList_H
#define _DLGenericChainList_H

#include "../dlobject/DLObject.h"
#include "./DLADTBase.h"

#undef CLASS_NAME
#undef CLASS_TYPE
#undef SUPER_CLASS_NAME

#define CLASS_NAME DLGenericSingleChainList
#define CLASS_TYPE Class CLASS_NAME
#define SUPER_CLASS_NAME DLADTBase


CLASS_TYPE
{
    Class SUPER_CLASS_NAME* super;
    const char* className;
    char* name;
    struct CLASS_FUNC_LIST(CLASS_NAME)* func;
    unsigned int count;
    void** head;
    void** end;
};

struct CLASS_FUNC_LIST(CLASS_NAME){
    DL_BASE_FUNC_POINT
    unsigned int (*getCount)();
    int (*isEmpty)();
    void (*Insert)();
    void** (*Put)();
    void** (*Top)();
    void** (*Pop)();
    void (*Treav)();
    void (*Treaverse)();
    void (*TreaverseFind)();
    int (*Delete)();
    int (*Find)();
    void (*Push)();
    int (*freeSelf)();
    //to add function point list here
};

CLASS_TYPE* CreateDLGenericSingleChainList();
CLASS_TYPE* CLASS_NAME();
#endif
