/////////////////////////////////////
// File name : DLGenericSingleChainList.c
// Create date : 2015-07-18 14:06
// Modified date : 2018-02-06 20:58
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/dllog.h"
#include "DLGenericSingleChainList.h"

DL_BASE_FUNC_BODYS

static
int
FreeSelf(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        DestorySelf(obj);
        return 0;
    }
    return -1;
}

static
void
_setCount(unsigned int c, void* obj){
    if(NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        self->count = c;
    }
}

static
unsigned int
getCount(void* obj){
    if(NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        return self->count;
    }
    return 0;
}

static
void
_addCount(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
            unsigned int count = getCount(self);
            count = count + 1;
            _setCount(count,self);
    }
}

static
void
_reduceCount(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
            unsigned int count = getCount(self);
            if (count > 0){
                count = count - 1;
                _setCount(count,self);
            }
    }
}

static
int
isEmpty(void* obj){
    if(NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        unsigned int c = self->func->getCount((void*)self);
        if(c > 0 && NULL != self->end){
            return 1;
        }
    }
    return 0;
}

static
void
Treav(void* obj, void* call_obj, void (*pfunc)(void** node, void* obj)){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** end = self->end;
        if (NULL == self->head && NULL == self->end){
            CONDITION_VALUE_IS_NULL;
            return;
        }

        void** tmp = end;
        while (tmp != NULL){
            if (NULL == pfunc){
                CONDITION_VALUE_IS_NULL;
            }else{
                pfunc(tmp,call_obj);
            }
            tmp = *tmp;
        }
    }
}

static
void
Treaverse(void* obj, void (*pfunc)(void** node)){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** end = self->end;
        if (NULL == self->head && NULL == self->end){
            CONDITION_VALUE_IS_NULL;
            return;
        }

        void** tmp = end;
        while (tmp != NULL){
            if (NULL == pfunc){
                CONDITION_VALUE_IS_NULL;
            }else{
                pfunc(tmp);
            }
            tmp = *tmp;
        }
    }
}

static
int
Find(void** target_node,
    void* obj,
    int (*pfunc)(void** node,void* obj,void* pvalue),
    void* pvalue){

    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;

        if (NULL == self->end && NULL == self->head){
            DEBUG_LOG("do not have any node");
            return -1;
        }else{
            void** tmp= self->end;
            int fret;
            while (tmp != NULL){
                if (NULL == pfunc){
                    CONDITION_VALUE_IS_NULL;
                }else{
                    fret = pfunc(tmp,(void*)self,pvalue);
                    if (1 == fret){
                        *target_node = tmp;
                        return 1;
                    }
                }
                tmp = *tmp;
            }
            *target_node = tmp;
        }
    }

    return 0;
}

static
void
TreaverseFind(void** target_node, void** node,void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;

        void** end = self->end;
        if (NULL == self->head && NULL == self->end){
            CONDITION_VALUE_IS_NULL;
            return;
        }

        if (self->end == node){
            *target_node = &self->end;
            return;
        }

        void** tmp= self->end;
        while (tmp != NULL){
            if (*tmp == node){
                *target_node = tmp;
                return;
            }
            tmp = *tmp;
        }
        *target_node = tmp;
    }
}

static
void
Insert(void** node, void* obj){
    if (NULL == node || NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        if (NULL == self->end){
            self->head = node;
            self->end = node;
            *node = NULL;
            _addCount(self);
        }else{
            void** data = self->head;
            self->head = node;
            *data = node;
            *node = NULL;
            _addCount(self);
        }
    }
}

static
void
Push(void** node, void* obj){
    if (NULL == node || NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;

        if (NULL == self->end){
            self->head = node;
            self->end = node;
            *node = NULL;
            _addCount(self);
        }else{
            void** data = self->end;
            self->end = node;
            *node = data;
            _addCount(self);
        }
    }
}

static
int
Delete(void** node, void* obj){
    if (NULL == node || NULL == obj){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        void** node_prev;
        TreaverseFind((void**)&node_prev,node,(void*)obj);

        void** data = *node_prev;
        void** data2 = *data;
        *node_prev = data2;
        //self->count -= 1;
        _reduceCount(self);
        return 0;
    }
}

static
void**
Put(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;

        if (NULL == self->end){
            DEBUG_LOG("self->end is NULL self->count:%d",getCount(self));
        }else{
          void** data = self->end;
          void** data2 = *data;
          self->end = data2;

          //self->count -= 1;
          _reduceCount(self);
          return data;
        }
    }
    return NULL;
}

static
void**
Top(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        if (NULL == self->end){
            DEBUG_LOG("chain is empty");
        }else{
            void** data = self->end;
            return data;
        }
    }
    return NULL;
}

static
void**
Pop(void* obj){
    return Put(obj);
}


/////////////////////////////////////////////////////////////

static struct CLASS_FUNC_LIST(CLASS_NAME) class_funcs = {
    DL_BASE_FUNC
    getCount,
    isEmpty,
    Insert,
    Put,
    Top,
    Pop,
    Treav,
    Treaverse,
    TreaverseFind,
    Delete,
    Find,
    Push,
    FreeSelf,
    //to add function list here
};

CLASS_TYPE*
CreateDLGenericSingleChainList(){
    CLASS_TYPE* chainHead = CLASS_NAME(0);

    return chainHead;
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
    self->name = "object name";
    self->count = 0;

    self->head = NULL;
    self->end = NULL;
    return self;
}
