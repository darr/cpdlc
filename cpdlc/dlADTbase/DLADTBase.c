/////////////////////////////////////
// File name : DLADTBase.c
// Create date : 2015-07-18 14:06
// Modified date : 2018-01-29 06:35
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/dllog.h"
#include "DLADTBase.h"

DL_BASE_FUNC_BODYS

static
int
FreeSelf(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        DestorySelf(obj);
    }
    return 0;
}

/////////////////////////////////////////////////////////////

static struct CLASS_FUNC_LIST(CLASS_NAME) class_funcs= {
    DL_BASE_FUNC
    FreeSelf,
    //to add function list here
};

CLASS_TYPE*
CLASS_NAME(char* name) {
    CLASS_TYPE* self= (CLASS_TYPE*) DLMallocMemory(sizeof(CLASS_TYPE));
    if (NULL == self){
        CONDITION_VALUE_IS_NULL;
        return NULL;
    }
    self->super = SUPER_CLASS_NAME();
    self->className= __FUNCTION__;
    self->name = name;
    self->func = &class_funcs;
    return self;
}

