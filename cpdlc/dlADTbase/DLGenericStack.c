/////////////////////////////////////
// File name : DLGenericStack.c
// Create date : 2015-07-18 14:06
// Modified date : 2018-01-31 10:47
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/dllog.h"
#include "DLGenericStack.h"

DL_BASE_FUNC_BODYS

static
int
IsEmpty(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        return self->Next == NULL;
    }
}

static
void
Push(void** node, void* obj){
    if (NULL == node || NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        *node = self->Next;
        self->Next = node;
        self->count += 1;
    }
}

static
void**
Top(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        if (!IsEmpty(self))
            return self->Next;
    }
    return NULL;
}

static
void
Pop(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        if (!IsEmpty(self)){
            self->Next =*self->Next;
            self->count -= 1;
        }
    }
}

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

static struct CLASS_FUNC_LIST(CLASS_NAME) class_funcs = {
    DL_BASE_FUNC
    IsEmpty,
    Push,
    Top,
    Pop,
    FreeSelf,
    //to add function list here
};

CLASS_TYPE*
CreateDLGenericStack(){
    CLASS_TYPE* statckTop = CLASS_NAME(0);
//    statckTop->Next = NULL;
    return statckTop;
}

CLASS_TYPE*
CLASS_NAME(int cnt){
    CLASS_TYPE* self= (CLASS_TYPE*) DLMallocMemory(sizeof(CLASS_TYPE));
    if (NULL == self){
        CONDITION_VALUE_IS_NULL;
        return NULL;
    }

    self->super = SUPER_CLASS_NAME();
    self->className = __FUNCTION__;
    self->func = &class_funcs;
    self->name = "dlstack";
    self->count = cnt;

    self->Next = NULL;
    return self;
}
