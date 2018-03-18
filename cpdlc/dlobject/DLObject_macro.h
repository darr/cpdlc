/////////////////////////////////////
// File name : DLObject_macro.h
// Create date : 2017-11-30 09:14
// Modified date : 2018-02-06 23:53
// Author : DARREN
// Describe : not set
// Email : lzygzh@126.com
////////////////////////////////////

#ifndef _DLObject_macro_H
#define _DLObject_macro_H

#undef CLASS_TYPE
#undef CLASS_NAME
#undef SUPER_CLASS_NAME
#define CLASS_NAME DLObject
#define CLASS_TYPE Class CLASS_NAME

#define _CLASS_FUNC_LIST(x)  x##_func
#define CLASS_FUNC_LIST(x)  _CLASS_FUNC_LIST(x)

#define DL_DESTORY_FUNC static \
                        void \
                        DestorySelf(void* obj) { \
                            if (NULL == obj){\
                                CONDITION_VALUE_IS_NULL;\
                            }else{\
                                DL_DESTORY_SELF((CLASS_TYPE*)obj) \
                            }\
                        } \

#define DL_SET_NAME_FUNC    static \
                            void  \
                            setName(char* name,void* obj) { \
                                if (NULL == obj){\
                                    CONDITION_VALUE_IS_NULL;\
                                }else{\
                                    CLASS_TYPE* self = (CLASS_TYPE*)obj; \
                                    self->name = name; \
                                }\
                            } \

#define DL_GET_NAME_FUNC    static \
                            char * \
                            getName(void* obj) { \
                                if (NULL == obj){\
                                    CONDITION_VALUE_IS_NULL;\
                                }else{\
                                    CLASS_TYPE* self = (CLASS_TYPE*)obj; \
                                    return self->name; \
                                }\
                                return NULL;\
                            } \

#define DL_GET_CLASS_NAME_FUNC  static \
                                const char*  \
                                getClassName(void* obj) { \
                                    if (NULL == obj){\
                                        CONDITION_VALUE_IS_NULL;\
                                    }else{\
                                        CLASS_TYPE *self= (CLASS_TYPE*)obj; \
                                        return self->className; \
                                    }\
                                    return NULL;\
                                } \

#define DL_GET_CLASS_STACk_FUNC static \
                                const char*  \
                                getClassStack(void* obj) { \
                                    CLASS_TYPE *self= (CLASS_TYPE*)obj; \
                                    if (self->super != NULL) { \
                                        const char *super_class_name; \
                                        super_class_name = self->super->func->getClassStack(self->super); \
                                    } \
                                    const char *class_name = self->className; \
                                    return class_name; \
                                } \

#define DL_BASE_FUNC_BODYS  DL_DESTORY_FUNC \
                            DL_GET_NAME_FUNC \
                            DL_SET_NAME_FUNC \
                            DL_GET_CLASS_NAME_FUNC \
                            DL_GET_CLASS_STACk_FUNC \

#define DL_DESTORY_SELF(obj)    (obj)->super->func->freeSelf((obj)->super); \
                                DLFreeMemory((obj));


#define DL_BASE_FUNC_POINT  void (*Destroy)(void*); \
                            const char * (*getClassName)(void*); \
                            const char * (*getClassStack)(void*); \
                            void (*setName)(char*,void*); \
                            char* (*getName)(void*);

#define DL_BASE_FUNC    DestorySelf, \
                        getClassName, \
                        getClassStack, \
                        setName, \
                        getName,

#endif

