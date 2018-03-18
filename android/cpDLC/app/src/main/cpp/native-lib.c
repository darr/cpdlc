#include <jni.h>

 jstring Java_com_aidaling_cpdlc_MainActivity_stringFromJNI(JNIEnv* env, jobject thiz) {
         return (*env)->NewStringUTF(env,"Hello Jni---->C!");
 }
