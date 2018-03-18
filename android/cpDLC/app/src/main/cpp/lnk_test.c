//
// Created by DarrenLiu on 16/10/26.
//

#include <jni.h>
#include <android/log.h>
#include "lnk_test.h"
#include "./cpdlc/dllog.h"
#include "./cpdlc/dlcpfunc.h"

#define  LOG_TAG    "HelloJni"


char * hello_world()
{
    int plat = getDLPlat();
    __android_log_print(ANDROID_LOG_INFO,LOG_TAG,"plat id:%d",plat);
    #ifdef __linux__
        #ifdef JNI_H_
            __android_log_print(ANDROID_LOG_INFO,LOG_TAG,"running on android");
//            INFO_LOG("info log");

        #endif
    #endif

    return "hello lnk test";
}
