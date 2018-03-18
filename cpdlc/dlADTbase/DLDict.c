/////////////////////////////////////
// File name : DLDict.c
// Create date : 2015-07-18 14:06
// Modified date : 2018-01-31 10:33
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include "../cpdlc/dllog.h"
#include "DLDict.h"

DL_BASE_FUNC_BODYS

typedef struct {
    void** key;
    void** value;
    void** next;
} Node;

static
int
_find(void** ptr,void* obj,void* pvalue)
{
    if (NULL == obj || NULL == ptr){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
        if (nd == NULL){
            CONDITION_VALUE_IS_NULL;
        }else{
            char* value = (char*)pvalue;
            if (strcmp((const char*)value, (const char*)nd->key) == 0){
                return 1;
            }
        }
    }
    return 0;
}

static
void**
_Pop(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** ptr = self->super->func->Pop((void*)self->super);

        if (NULL == ptr){
            CONDITION_VALUE_IS_NULL;
        }else{
            Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
            if (NULL == nd->value){
                CONDITION_VALUE_IS_NULL;
            }else{
                void** value_data = nd->value;
                DLFreeMemory(nd);
                return value_data;
            }
        }
    }
    return NULL;
}

static
void
_MakeEmpty(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        while (self->func->isEmpty(self)){
            _Pop(self);
        }
    }
    return ;
}

static
int
FreeSelf(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _MakeEmpty(self);
        DestorySelf(obj);
    }
    return 0;
}

static
int
isEmpty(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        return self->super->func->isEmpty(self->super);
    }
    return 0;
}

static
unsigned int
getCount(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        return self->super->func->getCount(self->super);
    }
    return 0;
}

static
void
_print(void** ptr,void* obj){
    if (NULL == obj || NULL == ptr){
        CONDITION_VALUE_IS_NULL;
    }else{
        Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
        if (NULL == nd){
            CONDITION_VALUE_IS_NULL;
        }else{
            CLASS_TYPE* self = (CLASS_TYPE*)obj;
            if(NULL == self->printCallBack){
                CONDITION_VALUE_IS_NULL;
            }else{
                self->printCallBack(nd->value);
            }
        }
    }
}

static
void
Treaverse(void* obj, void (*pfunc)(void** node)){
    if (NULL == obj || NULL == pfunc){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        self->printCallBack = pfunc;
        self->super->func->Treav(self->super,self,_print);
    }
}

static
void
Add(void** key, void** value, void* obj){
    if (NULL == obj || NULL == value){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        Node* nd = (Node*)DLMallocMemory(sizeof(Node));
        nd->key = key;
        nd->value = value;
        self->super->func->Push(&nd->next,(void*)self->super);
    }
}

static
void**
Get(void** key,void** default_value, void* obj){
    if (NULL == key || NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** ptr;
        int ret = self->super->func->Find(&ptr,(void*)self->super,_find,key);
        if (1 == ret && ptr != NULL){
            Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
            void** value = nd->value;
            return value;
        }
    }
    return default_value;
}

static
void**
Remove(void** key, void* obj){
    if (NULL == key || NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** ptr;
        int ret = self->super->func->Find(&ptr,(void*)self->super,_find,key);

        if (1 == ret && ptr != NULL){
            Node* nd = DL_GET_LIST_ENTRY(ptr,Node,next);
            int r = self->super->func->Delete(&nd->next,(void*)self->super);
            if (r < 0){
                CONDITION_VALUE_IS_NULL;
            }else{
                void** data = nd->value;
                DLFreeMemory(nd);
                return data;
            }
        }
    }
    return NULL;
}

/////////////////////////////////////////////////////////////

static struct CLASS_FUNC_LIST(CLASS_NAME) class_funcs = {
    DL_BASE_FUNC
    isEmpty,
    getCount,
    Add,
    Get,
    Remove,
    Treaverse,
    FreeSelf,
    //to add function list here
};

CLASS_TYPE*
CreateDLDict(){
    CLASS_TYPE* statckTop = CLASS_NAME(0);
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
    self->printCallBack = NULL;

    return self;
}
