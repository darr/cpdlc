/////////////////////////////////////
// File name : testdlsqlite.c
// Create date : 2017-11-29 05:35
// Modified date : 2018-02-07 16:04
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include "../cpdlc/cpdlc/dllog.h"
#include "../cpdlc/cpdlc/dlcpstring.h"
#include "../cpdlc/dlsqlite/DLSqlite.h"
#include "testdlsqlite.h"

void
testSqlite(void){
    Class DLSqlite *dlp = DLSqlite();
    dlp->func->setName("liuzy",(void*)dlp);
    const char* name = dlp->func->getClassName((void*)dlp);
    DL_TEST_COMPARE_VALUE_STR(name,"DLSqlite");
    char * person_name = dlp->func->getName((void*)dlp);
    DL_TEST_COMPARE_VALUE_STR(person_name,"liuzy");
}

void
testSqliteDB(void){
    Class DLSqlite *dlp = CreateSqliteDB();
    char* table_name = "healthinfo";

    dlp->func->checkIsHaveTable(table_name,(void*)dlp);
    char* sql = mallocFormatString("create table if not exists %s ("\
                        "sid int primary key not null," \
                        "name text not null," \
                        "ishealth char(4) not null);",table_name
    );

    dlp->func->createTable(table_name,sql,(void*)dlp);

    sql = "insert into healthinfo (sid, name, ishealth)" \
    "values (201601001, 'xiaowang', 'yes');" \

    "insert into healthinfo (sid, name, ishealth)" \
    "values (201601002, 'xiaoli', 'yes');" \

    "insert into healthinfo (sid, name, ishealth)" \
    "values (201601003, 'xiaozhang', 'no');" \

    "insert into healthinfo (sid, name, ishealth)" \
    "values (201601004, 'xiaozhou', 'yes');" \

    "insert into healthinfo (sid, name, ishealth)" \
    "values (201601005, 'xiaosun', 'yes');";

    dlp->func->Insert(table_name,sql,(void*)dlp);

    const char* data = "select call back function call!\n";
    sql = "select * from healthinfo where ishealth == 'yes';";
    dlp->func->Select(table_name,sql,(void*)dlp);

    data = "update call back function call!\n";
    sql = "update healthinfo set ishealth = 'no' where name='xiaoli';";
    dlp->func->Update(table_name,sql,(void*)dlp);

    sql = "delete from healthinfo where sid = 201601002";

    dlp->func->Delete(table_name,sql,(void*)dlp);


    /* 删除表 */  
    sql = "drop table healthinfo;";
    dlp->func->dropTable(table_name,sql,(void*)dlp);

    dlp->func->freeSelf((void*)dlp);
}

static
void
_common_use_test(void){
    testSqlite();
    testSqliteDB();
}

static
void
_marginal_test(void){
    FUNC_RUN_LOG;
}

static
void
_runtest(void){
    _common_use_test();
    if (1 == DL_MARGINAL_TEST)
        _marginal_test();
    _marginal_test();
}

void testDLSqlite(void){
    _runtest();
}
