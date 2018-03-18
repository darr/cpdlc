/////////////////////////////////////
// File name : testcpdlc.c
// Create date : 2016-06-04 02:50
// Modified date : 2018-02-06 21:47
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////


#include <stdio.h>
#include "testdllog.h"
#include "testcjson.h"
#include "testcpdlc.h"
#include "testdlobject.h"
#include "testdlsqlite.h"
#include "testdl_generic_chain_list.h"
#include "testDLGenericChainList.h"
#include "testDLGenericSingleChainList.h"
#include "testDLQueue.h"
#include "testDLStack.h"
#include "testDLList.h"
#include "testDLDict.h"
#include "testdlsort.h"
#include "testDLGenericStack.h"
#include "../cpdlc/cpdlc/dlcpfunc.h"
#include "../cpdlc/cpdlc/dllog.h"

#include "testdlcpNet.h"

void testDeveloper(){
    dlcpMkdir("./testdllog");
    int pt = getDLPlat();
//    printf("plat is :%d",pt);
}

void
testCheckPlat(){
    int plat = getDLPlat();
    printf("plat :%d!\n",plat);
    if (isPlatWindows() == 0){
        printf("hello windows!\n");
    }
    
    if (isPlatLinux() == 0){
        printf("hello linux!\n");
    }
    
    if(isPlatMac() == 0){
        printf("hello mac!\n");
    }
    
//  if(isPlatIphoneSimulator() == 0)
//  {
//      printf("hello iphone simulator!\n");
//  }
//  
//  if(isPlatIphone() == 0)
//  {
//      printf("hello iphone!\n");
//  }
}

void
mainTest(){
    testDeveloper();
    //testLog();
    //create_objects();
    testdlobject();
    testdl_generic_chain_list();
    //testSqlite();
    testDLSqlite();
    //testdlcpNet();
    testDLGenericChainList();
    testDLGenericSingleChainList();
    testDLQueue();
    testDLStack();
    testDLList();
    testDLDict();
    testdlsort();
    testDLGenericStack();
//    testCheckPlat();
}

void
testcpdlcBegin()
{
    setLogPrintLevel(log_level_info);
    mainTest();
}



