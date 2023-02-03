// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("openglesdemo");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("openglesdemo")
//      }
//    }

#include <jni.h>
#include <android/log.h>
#define LOG_TAG "OpenGLESDemo"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


extern "C"
JNIEXPORT void JNICALL
Java_com_example_openglesdemo_cver_NativeLibrary_init(JNIEnv *env, jobject thiz) {
    LOGI("Hello From the Native Side!!");
}