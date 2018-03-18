/////////////////////////////////////
// File name : testDLGenericStack.c
// Create date : 2016-06-05 03:39
// Modified date : 2018-01-29 06:43
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/dlADTbase/DLGenericStack.h"
#include "testDLGenericStack.h"

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
void*
testStackPop(Class DLGenericStack *dlp){
    int element;
    int cnt;
    int isE = dlp->func->IsEmpty((void*)dlp);
    if (!isE){
        void** node = dlp->func->Top((void*)dlp);
        Node* nd = DL_GET_LIST_ENTRY(node, Node, next);
        //deal node
        dlp->func->Pop((void*)dlp);
        DLFreeMemory(nd);

        return node;
    }
    return 0;
}
static
void
_common_use_test(void){
    Class DLGenericStack *dlp = CreateDLGenericStack();
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE_STR(name,"DLGenericStack");
    dlp->name = "my stack";
    char * object_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE_STR(object_name,"my stack");
    const char* name2 = dlp->func->getClassStack((void*)dlp);
    DL_TEST_COMPARE_VALUE_STR(name2,"DLGenericStack");

    int count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0);

    Node* nd1;
    nd1 = _malloc_Node(1);

    dlp->func->Push(&nd1->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1);

    Node* nd2;
    nd2 = _malloc_Node(2);
    dlp->func->Push(&nd2->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2);

    Node* nd3;
    nd3 = _malloc_Node(3);
    dlp->func->Push(&nd3->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,3);

    Node* nd4;
    nd4 = _malloc_Node(4);
    dlp->func->Push(&nd4->next,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,4);

    testStackPop(dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,3);
    testStackPop(dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2);
    testStackPop(dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1);
    testStackPop(dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0);
    testStackPop(dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0);
    testStackPop(dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0);
    testStackPop(dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0);
    dlp->func->freeSelf((void*)dlp);
}

static
void
_marginal_test(void){
    Class DLGenericStack *dlp = CreateDLGenericStack();
    dlp->func->Push(NULL,(void*)dlp);
    dlp->func->Push(NULL,NULL);
}

static
void
_runtest(){
    _common_use_test();
    if (1 == DL_MARGINAL_TEST)
        _marginal_test();
}

void
testDLGenericStack(){
    _runtest();
}
