/////////////////////////////////////
// File name : DLADTBase.h
// Create date : 2015-07-18 14:08
// Modified date : 2018-01-26 00:45
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLADTBASE_H
#define _DLADTBASE_H

#include "../dlobject/DLObject.h"

#undef CLASS_NAME
#undef CLASS_TYPE
#undef SUPER_CLASS_NAME

#define CLASS_NAME DLADTBase
#define CLASS_TYPE Class CLASS_NAME
#define SUPER_CLASS_NAME DLObject


CLASS_TYPE
{
    Class SUPER_CLASS_NAME* super;
    const char* className;
    char* name;
    struct CLASS_FUNC_LIST(CLASS_NAME)* func;
};

struct CLASS_FUNC_LIST(CLASS_NAME){
    DL_BASE_FUNC_POINT
    int (*freeSelf)();
};

CLASS_TYPE* CLASS_NAME();
#endif
