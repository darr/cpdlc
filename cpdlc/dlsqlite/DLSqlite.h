/////////////////////////////////////
// File name : DLSqlite.h
// Create date : 2015-07-18 14:08
// Modified date : 2018-02-07 15:52
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLSQLITE_H
#define _DLSQLITE_H

#include "../dlobject/DLObject.h"

#undef CLASS_TYPE
#undef CLASS_NAME
#undef SUPER_CLASS_NAME

#define CLASS_TYPE Class DLSqlite
#define CLASS_NAME DLSqlite
#define SUPER_CLASS_NAME DLObject

CLASS_TYPE
{
    Class SUPER_CLASS_NAME* super;
    const char* className;
    char* name;
    struct CLASS_FUNC_LIST(CLASS_NAME)* func;
    void* db;
};

struct CLASS_FUNC_LIST(CLASS_NAME){
    DL_BASE_FUNC_POINT
    int (*createTable)();
    int (*checkIsHaveTable)();
    int (*Insert)();
    int (*Select)();
    int (*Update)();
    int (*Delete)();
    int (*dropTable)();
    int (*sqlExec)();
    int (*freeSelf)();
};

CLASS_TYPE* CreateSqliteDB();
CLASS_TYPE* CLASS_NAME();
#endif
