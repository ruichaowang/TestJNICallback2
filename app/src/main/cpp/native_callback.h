//
// Created by 王锐超 on 2022/12/28.
//

#ifndef TESTJNICALLBACK2_NATIVE_CALLBACK_H
#define TESTJNICALLBACK2_NATIVE_CALLBACK_H

#include <jni.h>

class native_callback {
private:
    JavaVM *gJavaVM;
    jobject gJavaObj;
    jmethodID  java_callback;

public:
    native_callback(JavaVM *m_JavaVM, jobject object, jmethodID methodID);
    ~native_callback();
    void start_native_process();

};


#endif //TESTJNICALLBACK2_NATIVE_CALLBACK_H
