//
// Created by chenfeng on 2017/10/14.
//

#include <jni.h>
#include <stddef.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

/**
 * jni静态注册的方式来调用,函数命名规则为：Java_类全路径_方法名,包名中"."用"_"代替
 */

JNIEXPORT jstring JNICALL
Java_com_cfryan_ndkhelloworld_NativeUtils_getString(JNIEnv *env, jobject obj) {
    return (*env)->NewStringUTF(env, "Hello from JNI !  build with static register！(no-static method)");
}

JNIEXPORT jstring JNICALL
Java_com_cfryan_ndkhelloworld_NativeUtils_staticGetString(JNIEnv *env, jclass clazz) {
    return (*env)->NewStringUTF(env, "Hello from JNI !  build with static register！(static method)");
}

/**
 * jni动态注册的方式来调用,需要通过映射表
 */
JNIEXPORT jstring JNICALL
dynamic_string(JNIEnv *env, jclass clazz) {
    return (*env)->NewStringUTF(env, "Hello from JNI !  build with dynamic register！");
}

JNIEXPORT jstring JNICALL
dynamic_string_param(JNIEnv *env, jclass clazz, jstring jstr) {

    char *final;
    char *jni_str = "Hello from JNI !  build with dynamic register！";

    //将java传入的string转换为本地utf的char*
    const char *pName = (*env)->GetStringUTFChars(env, jstr, NULL);
    if (NULL != pName) {

        final = (char *) malloc(strlen(jni_str) + strlen(pName) + 1);
        strcpy(final, jni_str);
        strcat(final, pName);

        //java的name对象不需要再使用,通知虚拟机回收name
        (*env)->ReleaseStringUTFChars(env, jstr, pName);
    } else {
        final = (char *) malloc(strlen(jni_str) + 1);
        strcpy(final, jni_str);
    }

    return (*env)->NewStringUTF(env, final);
}


//参数映射表
static JNINativeMethod methods[] = {
        {"dynamicGetString",          "()Ljava/lang/String;",                   (void *) dynamic_string},
        {"dynamicGetStringWithParam", "(Ljava/lang/String;)Ljava/lang/String;", (void *) dynamic_string_param},
        //这里可以有很多其他映射函数
};

//为某一个类注册本地方法，调用Jni注册
static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
                                 int numMethods) {
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }

    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

//注册Native
static int registerNatives(JNIEnv *env) {
    const char *className = "com/cfryan/ndkhelloworld/NativeUtils"; //指定注册的类
    return registerNativeMethods(env, className, methods, sizeof(methods) / sizeof(methods[0]));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    //LOGD("-------------JNI_OnLoad into.--------\n");
    JNIEnv *env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);

    //动态注册，自定义函数
    if (!registerNatives(env)) {
        return -1;
    }

    return JNI_VERSION_1_4;
}
