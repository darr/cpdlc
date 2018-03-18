/////////////////////////////////////
// File name : testDLGenericSingleChainList.c
// Create date : 2016-06-05 03:39
// Modified date : 2018-02-07 00:09
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/dlADTbase/DLGenericSingleChainList.h"

typedef struct {
    int id;
    void** next;
} Node;

static
Node*
_malloc_Node(int id){
    Node* nd = (Node*)malloc(sizeof(Node));
    if ( nd != NULL ) {
        nd->id = id;
    }
    return nd;
}

static
int
_find(void** ptr,void* obj,void* pvalue)
{
    Class DLGenericSingleChainList* dlp = (Class DLGenericSingleChainList*)obj;
    Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
    if (nd == NULL)
        return 0;

    int* value = pvalue;
    if (*value == nd->id){
        //int ret = dlp->func->Delete(&nd->entry,(void*)dlp);
        //DL_TEST_COMPARE_VALUE_INT(ret,0)
        return 1;
    }
    return 0;
}

static
void
_print(void** ptr){
    Node* nd = DL_GET_LIST_ENTRY(ptr, Node, next);
    if (nd == NULL)
        return;
    //DEBUG_LOG("Node id = %d\n", nd->id);
}

static
void
_common_use_test(void){
    Class DLGenericSingleChainList* dlp = CreateDLGenericSingleChainList();
    dlp->name = "liuzy";
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE(name,"DLGenericSingleChainList","str")
    char* obj_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE(obj_name,"liuzy","str")

    Node* nd1;
    nd1 = _malloc_Node(1);
    dlp->func->Insert(&nd1->next,(void*)dlp);

    int count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)

    Node* nd2;
    nd2 = _malloc_Node(2);
    dlp->func->Insert(&nd2->next,(void*)dlp);

    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)

    Node* nd3;
    nd3 = _malloc_Node(3);

    dlp->func->Insert(&nd3->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,3)

    Node* nd4;
    nd4 = _malloc_Node(4);

    dlp->func->Insert(&nd4->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,4)

    Node* nd5;
    nd5 = _malloc_Node(5);

    dlp->func->Insert(&nd5->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,5)

    void** ptr2;
    Node* pnd2;

    dlp->func->TreaverseFind(&ptr2,&nd3->next,(void*)dlp);
    pnd2 = DL_GET_LIST_ENTRY(ptr2, Node, next);
    DL_TEST_COMPARE_VALUE_INT(pnd2,nd2)

    dlp->func->TreaverseFind(&ptr2,&nd1->next,(void*)dlp);
    void** pend = (void**)&dlp->end;
    DL_TEST_COMPARE_VALUE_INT(ptr2,pend)

    dlp->func->TreaverseFind(&ptr2,&nd5->next,(void*)dlp);
    pnd2 = DL_GET_LIST_ENTRY(ptr2, Node, next);
    DL_TEST_COMPARE_VALUE_INT(pnd2,nd4)

//    dlp->func->Treaverse((void*)dlp,_print);


    void** ptr;
    int a = 1;
    int find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    Node* fnd = DL_GET_LIST_ENTRY(ptr, Node, next);

    DL_TEST_COMPARE_VALUE_INT(fnd,nd1)
    DL_TEST_COMPARE_VALUE_INT(find_ret,1)

    a = 3;
    find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    fnd = DL_GET_LIST_ENTRY(ptr, Node, next);

    DL_TEST_COMPARE_VALUE_INT(fnd,nd3)
    DL_TEST_COMPARE_VALUE_INT(find_ret,1)


    a = 5;
    find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    fnd = DL_GET_LIST_ENTRY(ptr, Node, next);

    DL_TEST_COMPARE_VALUE_INT(fnd,nd5)
    DL_TEST_COMPARE_VALUE_INT(find_ret,1)

    int ret = dlp->func->Delete(&nd1->next,(void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(ret,0)
    a = 1;
    find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    DL_TEST_COMPARE_VALUE_INT(ptr,NULL)
    DL_TEST_COMPARE_VALUE_INT(find_ret,0)
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,4)


    ret = dlp->func->Delete(&nd3->next,(void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(ret,0)
    a = 3;
    find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    DL_TEST_COMPARE_VALUE_INT(ptr,NULL)
    DL_TEST_COMPARE_VALUE_INT(find_ret,0)
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,3)


    ret = dlp->func->Delete(&nd5->next,(void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(ret,0)
    a = 5;
    find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    DL_TEST_COMPARE_VALUE_INT(ptr,NULL)
    DL_TEST_COMPARE_VALUE_INT(find_ret,0)
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)


    dlp->func->Put((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)

    Node* nd6;
    nd6 = _malloc_Node(6);

    dlp->func->Push(&nd6->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)

    Node* nd7;
    nd7 = _malloc_Node(7);

    dlp->func->Push(&nd7->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,3)

    Node* nd8;
    nd8 = _malloc_Node(8);

    dlp->func->Push(&nd8->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,4)

    void** p8 = dlp->func->Pop((void*)dlp);
    Node* pnd8 = DL_GET_LIST_ENTRY(p8,Node,next);
    DL_TEST_COMPARE_VALUE_INT(pnd8,nd8)
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,3)

    dlp->func->Treaverse((void*)dlp,_print);
    dlp->func->Pop((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)
    dlp->func->Pop((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)
    dlp->func->Pop((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0)
    dlp->func->Pop((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0)
    dlp->func->Pop((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0)

    Node* nd9;
    nd9 = _malloc_Node(9);

    dlp->func->Push(&nd9->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)

    Node* nd10;
    nd10 = _malloc_Node(10);

    dlp->func->Push(&nd10->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)

    dlp->func->Pop((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)

    dlp->func->freeSelf((void*)dlp);
}

static
void
_marginal_test(void){
    Class DLGenericSingleChainList* dlp = CreateDLGenericSingleChainList();
    dlp->name = "liuzy";
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE(name,"DLGenericSingleChainList","str")
    char* obj_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE(obj_name,"liuzy","str")

    Node* nd1;
    nd1 = _malloc_Node(1);
    dlp->func->Insert(&nd1->next,(void*)dlp);

    int count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)

    Node* nd2;
    nd2 = _malloc_Node(2);
    dlp->func->Insert(&nd2->next,(void*)dlp);

    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)
    dlp->func->Insert(NULL,(void*)dlp);
    dlp->func->Insert(NULL,NULL);
    dlp->func->Push(NULL,NULL);
    dlp->func->Push(NULL,(void*)dlp);


    int a = 6;
    void** ptr;
    int find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    DL_TEST_COMPARE_VALUE_INT(ptr,NULL)

    DL_TEST_COMPARE_VALUE_INT(find_ret,0)
}

static
void
_runtest(void){
    _common_use_test();
    if (1 == DL_MARGINAL_TEST)
        _marginal_test();
}

void testDLGenericSingleChainList(void){
    _runtest();
}
