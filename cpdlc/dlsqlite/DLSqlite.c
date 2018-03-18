/////////////////////////////////////
// File name : DLSqlite.c
// Create date : 2015-07-18 14:06
// Modified date : 2018-02-07 16:04
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "../cpdlc/dllog.h"
#include "../cpdlc/dlcpstring.h"
#include "DLSqlite.h"

DL_BASE_FUNC_BODYS

static
int
_createDB(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;

        char* database_path = "./mysqlite.db";
        int rc = sqlite3_open(database_path, (struct sqlite3**)&self->db);
        if (rc){
            ERROR_LOG("open sqlite3 database fault");
            return -1;
        }else{
            return 0;
        }
    }
    return -1;
}

static
int
_closeDB(void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        sqlite3_close(self->db);
    }
    return 0;
}

static
int
_sql_exec(char* sql,void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        char *zErrMsg = 0;

        int ret = sqlite3_exec(self->db, sql, NULL, NULL, &zErrMsg);
        if( ret != SQLITE_OK ){
            ERROR_LOG("SQL error:%s",zErrMsg);
            sqlite3_free(zErrMsg);
        }else{
            //INFO_LOG("sql run successfully");
            return 0;
        }
    }

    return -1;
}

static
int
_checkIsHaveTable(char* tb_name,void* obj){
    if (NULL== tb_name || NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        char *zErrMsg = 0;
        char* sql = mallocFormatString("select * from %s", tb_name);

        int ret = sqlite3_exec(self->db, sql, NULL, NULL, &zErrMsg);
        if( ret == SQLITE_ERROR ){
            sqlite3_free(zErrMsg);
        }else{
            return 1;
        }
    }
    return -1;
}

static
int
checkIsHaveTable(char* sql,void* obj){
    return _checkIsHaveTable(sql,obj);
}

static
int
createTable(char* table_name, char* sql, void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;

        if(_checkIsHaveTable(table_name,self)){
            _sql_exec(sql,obj);
        }
    }
    return -1;
}

static
int
Insert(char* table_name, char* sql, void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _sql_exec(sql,obj);
    }
    return -1;
}

static
int
Select(char* table_name, char* sql, void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _sql_exec(sql,obj);
    }
    return -1;
}

static
int
Update(char* table_name, char* sql, void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _sql_exec(sql,obj);
    }
    return -1;
}

static
int
Delete(char* table_name, char* sql, void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _sql_exec(sql,obj);
    }
    return -1;
}

static
int
dropTable(char* table_name, char* sql, void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _sql_exec(sql,obj);
    }
    return -1;
}

static
int
sqlExec(char* table_name, char* sql, void* obj){
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _sql_exec(sql,obj);
    }
    return -1;
}

static
int
FreeSelf(void* obj) {
    if (NULL == obj){
        CONDITION_VALUE_IS_NULL;
    }else{
        CLASS_TYPE* self = (CLASS_TYPE*)obj;
        _closeDB(self);
        //DLFreeMemory(self->db);
        DestorySelf(obj);
    }
    return 0;
}

////////////////////////////////////////////////////

static struct DLSqlite_func class_funcs= {
    DL_BASE_FUNC
    createTable,
    checkIsHaveTable,
    Insert,
    Select,
    Update,
    Delete,
    dropTable,
    sqlExec,
    FreeSelf,
};

CLASS_TYPE*
CreateSqliteDB(){
    CLASS_TYPE* obj = CLASS_NAME();
    _createDB((void*)obj);
    return obj;
}

CLASS_TYPE*
CLASS_NAME()
{
    CLASS_TYPE* self= (CLASS_TYPE*) malloc(sizeof(CLASS_TYPE));
    if (NULL == self){
        CONDITION_VALUE_IS_NULL;
        return NULL;
    }
    self->super = SUPER_CLASS_NAME();
    self->className= __FUNCTION__;
    self->name = "object name";
    self->func = &class_funcs;
    self->db = NULL;
    return self;
}
