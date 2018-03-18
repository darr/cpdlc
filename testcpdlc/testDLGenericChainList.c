/////////////////////////////////////
// File name : testDLGenericChainList.c
// Create date : 2016-06-05 03:39
// Modified date : 2018-01-29 05:42
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/dlADTbase/DLGenericChainList.h"

typedef struct {
    int id;
    GenericChainListNode entry;
} student_n;

static
student_n*
_make_node(int id){
    student_n* stu = (student_n*)malloc(sizeof(student_n));
    if ( stu != NULL ) {
        stu->id = id;
    }
    return stu;
}

static
int
_find(GenericChainListNode* ptr,void* obj,void* pvalue)
{
    Class DLGenericChainList* dlp = (Class DLGenericChainList*)obj;
    student_n* stu = DL_GET_LIST_ENTRY(ptr, student_n, entry);
    if (stu == NULL)
        return 0;

    int* value = pvalue;
    if (*value == stu->id){
        int ret = dlp->func->Delete(&stu->entry,(void*)dlp);
        DL_TEST_COMPARE_VALUE_INT(ret,0)
        return 1;
    }
    return 0;
}

static
void
_print(GenericChainListNode* ptr){
    student_n* stu = DL_GET_LIST_ENTRY(ptr, student_n, entry);
    if (stu == NULL)
        return;
    DEBUG_LOG("student id = %d\n", stu->id);
}

static
void
_common_use_test(void){
    Class DLGenericChainList* dlp = CreateDLGenericChainList();
    dlp->name = "liuzy";
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE(name,"DLGenericChainList","str")
    char* obj_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE(obj_name,"liuzy","str")

    student_n* stu;
    stu = _make_node(1);
    dlp->func->Insert(&stu->entry,(void*)dlp);

    int count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)

    student_n* stu2;
    stu2 = _make_node(2);

    dlp->func->Insert(&stu2->entry,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)

    student_n* stu3;
    stu3 = _make_node(3);

    dlp->func->Insert(&stu3->entry,(void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,3)

    dlp->func->Treaverse((void*)dlp,_print);

    int ret = dlp->func->Delete(&stu3->entry,(void*)dlp);
    DL_TEST_COMPARE_VALUE_INT(ret,0)

    GenericChainListNode* ptr;

    int a = 3;
    int find_ret = dlp->func->Find(&ptr,(void*)dlp,_find,&a);
    DL_TEST_COMPARE_VALUE_INT(find_ret,0)

    dlp->func->Treaverse((void*)dlp,_print);

    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,2)

    dlp->func->Put((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,1)

    dlp->func->Put((void*)dlp);
    count = dlp->count;
    DL_TEST_COMPARE_VALUE_INT(count,0)

    dlp->func->freeSelf((void*)dlp);
}

static
void
_marginal_test(void){
    Class DLGenericChainList* dlp = CreateDLGenericChainList();
    dlp->func->Insert(NULL,(void*)dlp);
    dlp->func->Insert(NULL,NULL);
    dlp->func->Treaverse(NULL,NULL);
    dlp->func->Treaverse(NULL,_print);
    dlp->func->Treaverse((void*)dlp,NULL);
}

static
void
_runtest(void){
    _common_use_test();
    if (1 == DL_MARGINAL_TEST)
        _marginal_test();
}

void testDLGenericChainList(void){
    _runtest();
}
