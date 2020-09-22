#include <jni.h>
#include <memory>
#include "SoundGame.h"
#include "logger.h"

#include <android/asset_manager_jni.h>

extern "C" {

std::unique_ptr<SoundGame> soundGame;

JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_GameSurfaceView_native_1onTouchInput(JNIEnv *env, jclass clazz,
                                                                       jint event_type,
                                                                       jlong time_since_boot_ms,
                                                                       jint pixel_x, jint pixel_y) {
    LOGD("OnTap Method called");
    soundGame->tap(time_since_boot_ms);
}

JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_GameSurfaceView_native_1surfaceDestroyed(JNIEnv *env,
                                                                           jclass clazz) {
    soundGame->onSurfaceDestroy();
}

JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_RendererWrapper_native_1onSurfaceCreated(JNIEnv *env, jclass clazz) {
    soundGame->onSurfaceCreated();
}

JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_RendererWrapper_native_1onSurfaceChanged(JNIEnv *env,
                                                                           jclass clazz,
                                                                           jint width_in_pixels,
                                                                           jint height_in_pixels) {
    soundGame->onSurfaceChanged(width_in_pixels, height_in_pixels   );
}
JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_RendererWrapper_native_1onDrawFrame(JNIEnv *env, jclass clazz) {
    soundGame->tick();
}

JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_OboeSoundPlaying_native_1onStart(JNIEnv *env, jobject thiz,
                                                                   jobject asset_manager) {

    LOGD("OnStart gets called");
    AAssetManager *assetManager = AAssetManager_fromJava(env, asset_manager);

    soundGame = std::make_unique<SoundGame>(*assetManager);
    soundGame->start();
}

JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_OboeSoundPlaying_native_1onStop(JNIEnv *env, jobject thiz) {
    soundGame->stop();
}

JNIEXPORT void JNICALL
Java_info_necronet_oboeplayground_OboeSoundPlaying_native_1setDefaultStreamValues(JNIEnv *env,
                                                                                  jobject thiz,
                                                                                  jint default_sample_rate,
                                                                                  jint default_frames_per_burst) {

    oboe::DefaultStreamValues::SampleRate = default_sample_rate;
    oboe::DefaultStreamValues::FramesPerBurst = default_frames_per_burst;

}

}