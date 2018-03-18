/////////////////////////////////////
// File name : DLStack.c
// Create date : 2015-07-18 14:06
// Modified date : 2018-01-31 10:55
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include "../cpdlc/dllog.h"
#include "DLStack.h"

DL_BASE_FUNC_BODYS

typedef struct {
    void** data;
    void** next;
} Node;

static
void
_MakeEmpty(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        while(self->func->isEmpty(self) ){
            self->func->Pop(self);
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
        _MakeEmpty(self);
        DestorySelf(obj);
        return 0;
    }
    return -1;
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
    return -1;
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
                self->printCallBack(nd->data);
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
Push(void** node, void* obj){
    if (NULL == obj || NULL == node){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        Node* nd = (Node*)DLMallocMemory(sizeof(Node));
        nd->data = node;
        self->super->func->Push(&nd->next,(void*)self->super);
    }
}

static
void**
Top(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** ptr = self->super->func->Top((void*)self->super);

        if (NULL == ptr){
            CONDITION_VALUE_IS_NULL;
        }else{
            Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
            if (NULL == nd->data){
                CONDITION_VALUE_IS_NULL;
            }else{
                void** data = nd->data;
                return data;
            }
        }
    }
    return NULL;
}

static
void**
Pop(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** ptr = self->super->func->Pop((void*)self->super);

        if (NULL == ptr){
            CONDITION_VALUE_IS_NULL;
        }else{
            Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
            if (NULL == nd->data){
                CONDITION_VALUE_IS_NULL;
            }else{
                void** data = nd->data;
                //INFO_LOG("free :%p",nd);
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
    Push,
    Top,
    Pop,
    Treaverse,
    FreeSelf,
    //to add function list here
};

CLASS_TYPE*
CreateDLStack(){
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
