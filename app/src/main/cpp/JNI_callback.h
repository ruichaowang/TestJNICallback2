//
// Created by 王锐超 on 2022/12/28.
//

#ifndef TESTJNICALLBACK2_JNI_CALLBACK_H
#define TESTJNICALLBACK2_JNI_CALLBACK_H

#define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)


JavaVM *gJavaVM = NULL;  //全局JavaVM 变量
jobject gJavaObj = NULL;   //全局Jobject变量
jmethodID nativeCallback = NULL;//全局的方法ID

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testjnicallback2_MainActivity_StartProgress(JNIEnv *env, jobject object);

#endif //TESTJNICALLBACK2_JNI_CALLBACK_H
