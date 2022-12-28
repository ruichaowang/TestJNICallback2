//
// Created by 王锐超 on 2022/12/28.
//
#include <jni.h>
#include <string>
#include <android/log.h>
#include <assert.h>
#include <unistd.h>;
#include "log.h"

#include "native_callback.h"

#define TAG "JNIThread"

static JavaVM *gJavaVM;             // 全局 JavaVM 变量
static jobject gJavaObj;            // 全局 Jobject 变量
static jmethodID java_callback;     // 全局的 java callback方法ID

// @deprecated  方案 1 测试代码
static void* native_thread_exec(void *arg) {
    LOGI(TAG,"The pthread id : %d\n", pthread_self());
    JNIEnv *env;
    //从全局的JavaVM中获取到环境变量
    gJavaVM->AttachCurrentThread(&env,NULL);

    for(int i = 0 ; i < 101; i = i + 10) {
        env->CallVoidMethod(gJavaObj,java_callback, i);
        sleep(1);
    }

    gJavaVM->DetachCurrentThread();
    LOGI(TAG,"thread stop");
    return ((void *)0);
}

// 创建长耗时的线程测试 native 的 callback
static void* native_thread_callback(void *arg) {
    LOGI(TAG,"The pthread id : %d\n", pthread_self());
    std::unique_ptr<native_callback> m_native_callback(new native_callback(gJavaVM, gJavaObj, java_callback));
    m_native_callback->start_native_process();
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
    java_callback = env->GetMethodID(clazz,"UpdateProgress","(I)V");

    // 创建线程1 此方法的问题在于只能验证 JNI ，并不能真正应用于项目中,跨线程回调Java层函数，每秒完成 10% 进度并返回 Java
//    pthread_t id1;
//    if (pthread_create(&id1,NULL,native_thread_exec,NULL) !=0 ) {
//        LOGI(TAG,"native thread1 create fail");
//    } else {
//        LOGI(TAG,"native thread1 create success");
//    }

    pthread_t id2;
    if (pthread_create(&id2,NULL,native_thread_callback, NULL) !=0 ) {
        LOGI(TAG,"native thread2 create fail");
    } else {
        LOGI(TAG,"native thread2 create success");
    }
}