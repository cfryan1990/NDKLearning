package com.cfryan.ndkhelloworld;

/**
 * native方法工具类
 *
 * @author chenfeng
 * @since 2017-10-13 11:29
 */

public class NativeUtils {

    static {
        System.loadLibrary("NDKHelloWorld");
    }

    /**
     * 通过jni静态注册方式实现(分实例方法和静态方法)
     * @return
     */
    public native String getString();
    public static native String staticGetString();

    /**
     * 通过jni动态注册的方式实现
     */
    public static native String dynamicGetString();

    public static native String dynamicGetStringWithParam(String txt);


}
