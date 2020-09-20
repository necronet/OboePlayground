#include <jni.h>
#include <string>
#include <android/log.h>
#include "AudioEngine.h"

#define  LOG_TAG    "JNI_NATIVE_CODE"

AudioEngine engine;
extern "C"
JNIEXPORT void JNICALL
    Java_info_necronet_oboeplayground_OboeHelloPlayground_startEngine(JNIEnv *env, jobject /* this */) {
    engine.start();
}

extern "C"
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_OboeHelloPlayground_tap(JNIEnv *env, jobject thiz, jboolean b) {
    engine.tap(b);
}

extern "C"
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_OboeHelloPlayground_setAmplitude(JNIEnv *env, jobject /* this */,
                                                                   jfloat amplitude) {
    engine.setAmplitude(amplitude);
}extern "C"
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_OboeHelloPlayground_setFrequency(JNIEnv *env, jobject /* this */,
                                                                   jfloat frequency) {
    engine.setFrequency(frequency);
}
extern "C"
JNIEXPORT jfloatArray JNICALL
Java_info_necronet_oboeplayground_OboeHelloPlayground_getCurrentData(JNIEnv *env, jobject /* this */) {

    jfloatArray result;
    DataStr data = engine.getCurrentData();

    result = env->NewFloatArray(data.numFrames);
    env->SetFloatArrayRegion(result, 0, data.numFrames, data.data);

    return result;

}extern "C"
JNIEXPORT jboolean JNICALL
Java_info_necronet_oboeplayground_OboeHelloPlayground_isWaveOn(JNIEnv *env, jobject thiz) {
    return engine.isWaveOn();
}