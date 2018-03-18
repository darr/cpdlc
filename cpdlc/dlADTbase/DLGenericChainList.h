/////////////////////////////////////
// File name : DLGenericChainList.h
// Create date : 2015-07-18 14:08
// Modified date : 2018-01-31 10:36
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

#define CLASS_NAME DLGenericChainList
#define CLASS_TYPE Class CLASS_NAME
#define SUPER_CLASS_NAME DLADTBase

#define ElementType int

typedef struct generic_chain_list_node{
    struct generic_chain_list_node* prev;
    struct generic_chain_list_node* next;
} GenericChainListNode;

CLASS_TYPE
{
    Class SUPER_CLASS_NAME* super;
    const char* className;
    char* name;
    struct CLASS_FUNC_LIST(CLASS_NAME)* func;
    int count;
    GenericChainListNode head;
};

struct CLASS_FUNC_LIST(CLASS_NAME){
    DL_BASE_FUNC_POINT
    void (*Insert)();
    GenericChainListNode* (*Put)();
    void (*Treaverse)();
    int (*Delete)();
    int (*Find)();
    int (*freeSelf)();
    //to add function point list here
};

CLASS_TYPE* CreateDLGenericChainList();
CLASS_TYPE* CLASS_NAME();
#endif
