/////////////////////////////////////
// File name : testDLList.c
// Create date : 2016-06-05 03:39
// Modified date : 2018-02-07 00:08
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/dlADTbase/DLList.h"

typedef struct {
    int id;
    char* content;
} Node;

static
Node*
_malloc_Node(int id,char* content){
    Node* nd = (Node*)malloc(sizeof(Node));
    if ( nd != NULL ) {
        nd->id = id;
        nd->content = content;
    }
    return nd;
}

static
void
_print(void** ptr){
    Node* nd = (Node*)ptr;
    if (nd == NULL)
        return;
//    INFO_LOG("Node:%p id:%d content:%s",nd,nd->id,nd->content);
}

static
void
_common_use_test(void){
    Class DLList* dlp = CreateDLList();
    dlp->name = "liuzy";
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE(name,"DLList","str")
    char* obj_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE(obj_name,"liuzy","str")

    Node* nd1;
    nd1 = _malloc_Node(1,"first");
    dlp->func->Append(nd1,(void*)dlp);

    int count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,1)

    Node* nd2;
    nd2 = _malloc_Node(2,"second");
    dlp->func->Append(nd2,(void*)dlp);

    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,2)

    Node* nd3;
    nd3 = _malloc_Node(3,"third");
    dlp->func->Append(nd3,(void*)dlp);

    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,3)

    dlp->func->Treaverse((void*)dlp,_print);

    dlp->func->Pop((void*)dlp);
    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,2)

    dlp->func->Pop((void*)dlp);
    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,1)

    dlp->func->Treaverse((void*)dlp,_print);
    int isE = dlp->func->isEmpty((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(isE,1)

    dlp->func->Pop((void*)dlp);
    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,0)

    dlp->func->Treaverse((void*)dlp,_print);
    isE = dlp->func->isEmpty((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(isE,0)

    Node* nd4;
    nd4 = _malloc_Node(4,"four");
    dlp->func->Append(nd4,(void*)dlp);
    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,1)

    Node* nd5;
    nd5 = _malloc_Node(5,"five");
    dlp->func->Append(nd5,(void*)dlp);
    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,2)

    dlp->func->freeSelf((void*)dlp);
}

static
void
_marginal_test(void){
    Class DLList* dlp = CreateDLList();
    dlp->name = "liuzy";
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE(name,"DLList","str")
    char* obj_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE(obj_name,"liuzy","str")

    dlp->func->Append(NULL,(void*)dlp);
    dlp->func->Append(NULL,NULL);
    dlp->func->Treaverse(NULL);
    dlp->func->Pop(NULL);
    dlp->func->isEmpty(NULL);
    dlp->func->getCount(NULL);
    dlp->func->freeSelf((void*)dlp);
}

static
void
_runtest(void){
    _common_use_test();
    if (1 == DL_MARGINAL_TEST)
        _marginal_test();
//    _marginal_test();
}

void testDLList(void){
    _runtest();
}
