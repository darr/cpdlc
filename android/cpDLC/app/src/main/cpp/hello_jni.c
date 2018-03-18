//
// Created by DarrenLiu on 16/10/26.
//

#include <jni.h>
#include <android/log.h>
#include "lnk_test.h"

#define  LOG_TAG    "HelloJni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

jstring Java_com_aidaling_cpdlc_MainActivity_stringJNI(JNIEnv* env, jobject thiz) {
    char * s = hello_world();
    LOGI("call from jni!");
    return (*env)->NewStringUTF(env,s);
}