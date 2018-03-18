/////////////////////////////////////
// File name : DLObject.c
// Create date : 2015-07-18 01:08
// Modified date : 2018-01-31 06:43
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/dllog.h"
#include "../cpdlc/dlcpstring.h"
#include "DLObject.h"

DL_GET_CLASS_NAME_FUNC

int dlobject_malloc_count = 0;

static
void
_FreeMem(void **ptr){
    if (*ptr == NULL){
        return;
    }else{
        free(*ptr);
        *ptr = NULL;
    }
}

void
DLFreeMemory(void* ptr){
    if (NULL != ptr){
        dlobject_malloc_count--;
        _FreeMem(&ptr);
    }
}

void*
DLMallocMemory(const unsigned int size){
    void* p = malloc(size);
    if (NULL != p){
        dlobject_malloc_count++;
    }
    return p;
}

int
getDLObjectMallocCount(void){
    return dlobject_malloc_count;
}


static
const char*
getClassStack(void* obj){
    CLASS_TYPE* self = (CLASS_TYPE*)obj;
    return self->className;
}

static
void
Destroy(void* obj){
    CLASS_TYPE* self = (CLASS_TYPE*)obj;
    DEBUG_LOG("destroy self:%s", self->className);
    DLFreeMemory(self);
}

////////////////////////////////////////////////////
static struct DLObject_func class_func = {
    getClassName,
    getClassStack,
    Destroy,
};

CLASS_TYPE*
CLASS_NAME(){
    //CLASS_TYPE* self = (CLASS_TYPE*) malloc(sizeof(CLASS_TYPE));
    CLASS_TYPE* self = (CLASS_TYPE*) DLMallocMemory(sizeof(CLASS_TYPE));
    if (NULL == self){
        CONDITION_VALUE_IS_NULL;
        return NULL;
    }
    self->super = NULL;
    self->className = __FUNCTION__;
    self->func = &class_func;
    return self;
}

