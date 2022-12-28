//
// Created by 王锐超 on 2022/12/28.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include <assert.h>
#include <unistd.h>
#include "JNI_callback.h"

#define TAG "JNIThread"


//跨线程回调Java层函数
static void* native_thread_exec(void *arg) {
    LOGI(TAG,"The pthread id : %d\n", pthread_self());
    JNIEnv *env;
    //从全局的JavaVM中获取到环境变量
    gJavaVM->AttachCurrentThread(&env,NULL);

    for(int i = 0 ; i < 101; i++) {
        usleep(100000);
        env->CallVoidMethod(gJavaObj,nativeCallback, i);
    }

    gJavaVM->DetachCurrentThread();
    LOGI(TAG,"thread stoped");
    return ((void *)0);
}


//JNI  的实现
extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjnicallback2_MainActivity_StartProgress(JNIEnv *env, jobject object) {
    // 创建全局引用
    env->GetJavaVM(&gJavaVM);
    gJavaObj = env->NewGlobalRef(object);
    jclass clazz = env->GetObjectClass(object);
    nativeCallback = env->GetMethodID(clazz,"UpdateProgress","(I)V");

    // 创建线程
    pthread_t id;
    if (pthread_create(&id,NULL,native_thread_exec,NULL) !=0 ) {
        LOGI(TAG,"native thread create fail");
    } else {
        LOGI(TAG,"native thread create success");
    }
}