#include <jni.h>
#include <string>
#include <android/log.h>
#include "AudioEngine.h"

#define  LOG_TAG    "JNI_NATIVE_CODE"
#define  ALOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

AudioEngine engine;
extern "C"
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_MainActivity_startEngine(JNIEnv *env, jobject /* this */) {
    engine.start();
}

extern "C"
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_MainActivity_tap(JNIEnv *env, jobject thiz, jboolean b) {
    engine.tap(b);
}

extern "C"
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_MainActivity_setAmplitude(JNIEnv *env, jobject /* this */,
                                                            jfloat amplitude) {
    engine.setAmplitude(amplitude);
}extern "C"
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_MainActivity_setFrequency(JNIEnv *env, jobject /* this */,
                                                            jfloat frequency) {
    engine.setFrequency(frequency);
}