/////////////////////////////////////
// File name : DLGenericChainList.c
// Create date : 2015-07-18 14:06
// Modified date : 2018-01-31 10:35
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/dllog.h"
#include "DLGenericChainList.h"

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

static
void
Treaverse(void* obj, void (*pfunc)(GenericChainListNode* node)){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        GenericChainListNode* head = &self->head;
        if ( NULL == head || NULL == head->next ){
            CONDITION_VALUE_IS_NULL;
            return;
        }

        GenericChainListNode* tmp = head->next;
        if (head == tmp){
            INFO_LOG("only head self");
            return;
        }
        while (tmp != head){
            if (NULL == pfunc){
                CONDITION_VALUE_IS_NULL;
            }else{
                pfunc(tmp);
            }
            tmp = tmp->next;
        }
    }
}

static
void
Insert(GenericChainListNode* node, void* obj){
    if (NULL == node || NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        GenericChainListNode* head = &(self->head);
        self->count += 1;

        if (head->prev == NULL && head->next == NULL){
            head->prev = node;
            head->next = node;
            node->prev = head;
            node->next = head;
        }else{
            GenericChainListNode* tmp;
            tmp = head->prev;
            tmp->next = node;
            node->prev = tmp;
            node->next = head;
            head->prev = node;
        }
    }
}

static
int
Delete(GenericChainListNode* node, void* obj){
    if (NULL == node || NULL == obj){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        if (node->prev == node->next){
            INFO_LOG("do not have any node");
            return -1;
        }

        CLASS_TYPE* self = (CLASS_TYPE*)obj;

        GenericChainListNode*p = node->prev;
        GenericChainListNode*n = node->next;
        p->next = n;
        n->prev = p;

        self->count -= 1;
        return 0;
    }
}

static
int
Find(GenericChainListNode** target_node,
    void* obj,
    int (*pfunc)(GenericChainListNode* node,void* obj,void* pvalue),
    void* pvalue){

    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        GenericChainListNode* head = &self->head;
        GenericChainListNode* tmp = head->next;
        if (head == tmp){
            INFO_LOG("do not have any node");
            return 0;
        }

        int fret;
        while (tmp != head){
            if (NULL == pfunc){
                CONDITION_VALUE_IS_NULL;
            }else{
                fret = pfunc(tmp,(void*)self,pvalue);
                if (1 == fret){
                    *target_node = tmp;
                    return 1;
                }
            }
            tmp = tmp->next;
        }
    }

    return 0;
}

static
GenericChainListNode*
Put(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        GenericChainListNode* head = &self->head;

        if (head->prev == NULL && head->next == NULL){
            DEBUG_LOG("do not have any node");
            return NULL;
        }else{
            GenericChainListNode* tmp;
            tmp = head->next;

            GenericChainListNode* tmp2;
            tmp2 = tmp->next;

            head->next = tmp2;
            tmp2->prev = head;

            self->count -= 1;
            return tmp;
        }
    }
    return NULL;
}

/////////////////////////////////////////////////////////////

static struct CLASS_FUNC_LIST(CLASS_NAME) class_funcs = {
    DL_BASE_FUNC
    Insert,
    Put,
    Treaverse,
    Delete,
    Find,
    FreeSelf,
    //to add function list here
};

CLASS_TYPE*
CreateDLGenericChainList(){
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
    self->count = cnt;

    self->head.prev = NULL;
    self->head.next = NULL;
    return self;
}
