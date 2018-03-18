/////////////////////////////////////
// File name : dl_generic_chain_list.h
// Create date : 2018-01-26 08:10
// Modified date : 2018-01-31 10:19
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _dl_generic_chain_list_H
#define _dl_generic_chain_list_H

typedef struct dl_generic_chain_list_node{
    struct dl_generic_chain_list_node* prev;
    struct dl_generic_chain_list_node* next;
} dl_generic_chain_list_node;


void init_generic_chain_list(dl_generic_chain_list_node* head);
int insert_item(dl_generic_chain_list_node* head, dl_generic_chain_list_node* node);
int delete_item(dl_generic_chain_list_node* node);
int treaverse_item(dl_generic_chain_list_node* head, void (*pfunc)(dl_generic_chain_list_node* node) );
int find_item(dl_generic_chain_list_node** target_node, dl_generic_chain_list_node* head, int (*pfunc)(dl_generic_chain_list_node* node,void* pvalue),void* pvalue);

#endif

