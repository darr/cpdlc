/////////////////////////////////////
// File name : testDLDict.c
// Create date : 2016-06-05 03:39
// Modified date : 2018-02-07 00:09
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/dlADTbase/DLDict.h"

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
    Class DLDict* dlp = CreateDLDict();
    dlp->name = "liuzy";
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE(name,"DLDict","str")
    char* obj_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE(obj_name,"liuzy","str")

    Node* nd1;
    nd1 = _malloc_Node(1,"first");
    char* key1 = "firstkey";
    dlp->func->Add(key1,nd1,(void*)dlp);

    int count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,1)

    Node* nd2;
    nd2 = _malloc_Node(2,"second");
    char* key2 = "secondkey";
    dlp->func->Add(key2,nd2,(void*)dlp);

    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,2)

    Node* nd3;
    nd3 = _malloc_Node(3,"third");
    char* key3 = "thirdkey";
    dlp->func->Add(key3,nd3,(void*)dlp);

    count = dlp->func->getCount((void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(count,3)

    Node* ndf = (Node*)dlp->func->Get(key3,nd2,(void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(ndf,nd3)

    dlp->func->Remove(key3,(void*)dlp);
    dlp->func->Treaverse((void*)dlp,_print);

    dlp->func->freeSelf((void*)dlp);
}

static
void
_marginal_test(void){
    Class DLDict* dlp = CreateDLDict();
    dlp->name = "liuzy";
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE(name,"DLDict","str")
    char* obj_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE(obj_name,"liuzy","str")

    dlp->func->Treaverse(NULL);
    dlp->func->isEmpty(NULL);
    dlp->func->getCount(NULL);
    dlp->func->Get(NULL,NULL);
    dlp->func->Get(NULL,(void*)dlp);
    dlp->func->Remove(NULL,(void*)dlp);
    dlp->func->Remove(NULL,NULL);

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

void testDLDict(void){
    _runtest();
}
