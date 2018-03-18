/////////////////////////////////////
// File name : testdl_generic_chain_list.c
// Create date : 2016-06-05 03:39
// Modified date : 2018-02-01 20:42
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/dlADTbase/dl_generic_chain_list.h"

typedef struct {
    int id;
    dl_generic_chain_list_node entry;
} student_t;

static
void
print(dl_generic_chain_list_node* ptr){
    student_t* stu = DL_GET_LIST_ENTRY(ptr, student_t, entry);
    if (stu == NULL)
        return;
    DEBUG_LOG("student id = %d\n", stu->id);
}

static
void
free_node(dl_generic_chain_list_node* ptr){
    if (ptr == NULL )
        return;

    student_t* node = DL_GET_LIST_ENTRY(ptr, student_t, entry);
    delete_item(&node->entry);
    free(node);
}

static
student_t*
make_node(int id){
    student_t* stu = (student_t*)malloc(sizeof(student_t));
    if ( stu != NULL ) {
        stu->id = id;
    }
    return stu;
}

static
void
testCreateList(){
    dl_generic_chain_list_node list;
    init_generic_chain_list(&list);
    student_t* stu;
    stu = make_node(1);
    insert_item(&list,&stu->entry);
    int count = treaverse_item(&list,print);

    DL_TEST_COMPARE_VALUE_INT(count,1);

    student_t* stu2;
    stu2 = make_node(2);
    insert_item(&list,&stu2->entry);
    count = treaverse_item(&list,print);

    DL_TEST_COMPARE_VALUE_INT(count,2);

    student_t* stu3;
    stu3 = make_node(2);
    insert_item(&list,&stu3->entry);
    int new_count = treaverse_item(&list,print);

    DL_TEST_COMPARE_VALUE_INT(new_count,3);
}

static
int
_find(dl_generic_chain_list_node* ptr,void* pvalue)
{
    student_t* stu = DL_GET_LIST_ENTRY(ptr, student_t, entry);

    if (stu == NULL)
        return 0;
    INFO_LOG("%d",stu->id);
    int* value = pvalue;
    if (*value == stu->id){
        printf("find it\n");
        return 1;
    }
    return 0;
}

static
void
testCreateList2(){
    dl_generic_chain_list_node list;
    init_generic_chain_list(&list);

    student_t* stu;
    stu = make_node(1);
    insert_item(&list,&stu->entry);
    stu = make_node(2);
    insert_item(&list,&stu->entry);
    stu = make_node(8);
    insert_item(&list,&stu->entry);
    dl_generic_chain_list_node* ptr;

    int a = 8;
    int ret = find_item(&ptr,&list,_find,&a);
    if (ret){
        student_t* stu2 = DL_GET_LIST_ENTRY(ptr, student_t, entry);
        delete_item(&stu2->entry);
    }else{
        INFO_LOG("do not find the item");
    }

    int count = treaverse_item(&list,print);
}


static
void
testDLGenericChainList(){
    dl_generic_chain_list_node list;

    init_generic_chain_list(0);
    init_generic_chain_list(&list);

    int i;
    student_t* stu;
    for ( i=0; i<5; i++ ) {
        stu = make_node(i);
        if ( stu != NULL )
            insert_item(&list, 0);
    }

    treaverse_item(&list, free_node);
}
static
void
_common_use_test(){
    //testDLGenericChainList();
    testCreateList();
    //testCreateList2();
}

static
void
_marginal_test(){
    dl_generic_chain_list_node list;
    init_generic_chain_list(NULL);
    init_generic_chain_list(&list);
    insert_item(NULL,NULL);
    insert_item(&list,NULL);
    treaverse_item(NULL,NULL);
    treaverse_item(&list,NULL);
    treaverse_item(NULL,print);
}

static
void
_runtest(void){
    _common_use_test();
    if (1 == DL_MARGINAL_TEST)
        _marginal_test();
}

void testdl_generic_chain_list(void){
    _runtest();
}
