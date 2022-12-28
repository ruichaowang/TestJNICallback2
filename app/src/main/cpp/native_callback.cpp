//
// Created by 王锐超 on 2022/12/28.
//

#include <android/log.h>
#include "native_callback.h"
#include <unistd.h>
#include <jni.h>
#include "log.h"

#define TAG "Navive_Thread"
//extern jmethodID nativeCallback;

native_callback::native_callback(JavaVM *m_JavaVM, jobject object, jmethodID methodID) {
    LOGI(TAG, "创建 class native_callback");
    gJavaVM = m_JavaVM;
    gJavaObj = object ;
    java_callback = methodID;
}
native_callback::~native_callback() {
    LOGI(TAG, "销毁 class native_callback");
}

void native_callback::start_native_process() {
    LOGI(TAG, "开始执行进程");
    JNIEnv *env;  //从全局的JavaVM中获取到环境变量
    gJavaVM->AttachCurrentThread(&env,NULL);
    for (int i = 0 ; i < 101; i = i + 10) {
        env->CallVoidMethod(gJavaObj,java_callback, i);
        sleep(1);
    }
    gJavaVM->DetachCurrentThread();
    LOGI(TAG, "结束执行进程");
}
