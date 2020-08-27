//
// Created by Jose Ayerdis on 8/26/20.
//
#include "AudioEngine.h"
#include "../../../../../oboe/include/oboe/AudioStreamBuilder.h"
#include "../../../../../oboe/include/oboe/Definitions.h"
#include <android/log.h>
#define  LOG_TAG    "JNI_NATIVE_CODE"
#define  ALOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

void AudioEngine::start() {

    oboe::AudioStreamBuilder b;

    b.setFormat(oboe::AudioFormat::Float);
    b.setChannelCount(1);
    b.setPerformanceMode(oboe::PerformanceMode::LowLatency);

    b.setSharingMode(oboe::SharingMode::Exclusive);
    b.setCallback(this);
    b.openStream(&stream);
    stream->setBufferSizeInFrames(stream->getFramesPerBurst()*2);

    stream->requestStart();
}

oboe::DataCallbackResult
AudioEngine::onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    oscilator.renderAudio(static_cast<float *>(audioData), numFrames);

    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::tap(bool i) {
    __android_log_print(ANDROID_LOG_INFO, "JNI Call", "Tapping %d", i);
    oscilator.setWaveOn(i);
}

void AudioEngine::setAmplitude(float amplitude) {
    oscilator.setAmplitude(amplitude);
}

void AudioEngine::setFrequency(float frequency) {
    oscilator.setFrequency(frequency);
}

