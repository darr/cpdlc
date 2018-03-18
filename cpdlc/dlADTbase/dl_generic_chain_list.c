/////////////////////////////////////
// File name : dl_generic_chain_list.c
// Create date : 2018-01-26 08:10
// Modified date : 2018-01-31 10:57
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/dllog.h"
#include "dl_generic_chain_list.h"

void
init_generic_chain_list(dl_generic_chain_list_node* head){
    if (NULL != head){
        head->prev = NULL;
        head->next = NULL;
    }else{
        CONDITION_VALUE_IS_NULL;
    }
}

int
insert_item(dl_generic_chain_list_node* head, dl_generic_chain_list_node* node){
    if (NULL == head || NULL == node){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        if (head->prev == NULL && head->next == NULL){
            head->prev = node;
            head->next = node;
            node->prev = head;
            node->next = head;
        }else{
            dl_generic_chain_list_node* tmp;
            tmp = head->prev;
            tmp->next = node;
            node->prev = tmp;
            node->next = head;
            head->prev = node;
        }
        return 0;
    }
}

int
delete_item(dl_generic_chain_list_node* node){
    if (NULL == node){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        if (node->prev == node->next){
            INFO_LOG("do not have any node");
            return -1;
        }
        dl_generic_chain_list_node *p = node->prev;
        dl_generic_chain_list_node *n = node->next;
        p->next = n;
        n->prev = p;
        return 0;
    }
}

int
treaverse_item(dl_generic_chain_list_node* head, void (*pfunc)(dl_generic_chain_list_node* node)){
    if (NULL == head){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{

        int count = 0;
        if (head->next == NULL ){
            INFO_LOG("do not have any node");
            return -1;
        }

        dl_generic_chain_list_node* tmp = head->next;
        if (head == tmp){
            printf("only head self \n");
            return 0;
        }
        while (tmp != head){
            count++;
            if (NULL == pfunc){
                CONDITION_VALUE_IS_NULL;
            }else{
                pfunc(tmp);
            }
            tmp = tmp->next;
        }
        return count;
    }
}

int
find_item(dl_generic_chain_list_node** target_node,
          dl_generic_chain_list_node* head,
          int (*pfunc)(dl_generic_chain_list_node* node,void* pvalue),
          void* pvalue){

    if (NULL == head || NULL == target_node){
        CONDITION_VALUE_IS_NULL;
        return -1;
    }else{
        int fret = 0;
            dl_generic_chain_list_node* tmp = head->next;
            while (tmp != head){
                if (NULL == pfunc){
                    CONDITION_VALUE_IS_NULL;
                }else{
                    fret = pfunc(tmp,pvalue);
                    if (1 == fret){
                        *target_node = tmp;
                        return 1;
                    }
                }
                tmp = tmp->next;
            }
        return 0;
    }
}
