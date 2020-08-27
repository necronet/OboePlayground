//
// Created by Jose Ayerdis on 8/26/20.
//
#include <cstdint>
#include <cstring>
#include "Oscilator.h"
#include <android/log.h>

template<>
void Oscilator<float>::renderAudio(float *audioData, int32_t numFrames) {
    if (mIsWaveOn) {
        for (int i = 0 ; i < numFrames; i++) {

            if (mPhase <= kPI) {
                __android_log_print(ANDROID_LOG_INFO, "JNI Call", "Up");
                audioData[i] = -mAmplitude;
            } else {
                __android_log_print(ANDROID_LOG_INFO, "JNI Call", "Down");
                audioData[i] = mAmplitude;
            }

            mPhase += mPhaseIncrement;
            if (mPhase > two_KPI) {
                mPhase -= two_KPI;
            }

        }
    } else {
        memset(audioData, 0, sizeof(float) * numFrames);
    }
}

template<>
void Oscilator<float>::setWaveOn(bool isWaveOn) {
    mIsWaveOn = isWaveOn;
}

template<>
void Oscilator<float>::setAmplitude(float amplitude) {
    mAmplitude = amplitude;
};

template<>
void Oscilator<float>::setFrequency(float frequency) {
    mFrequency = frequency;
    mPhaseIncrement = (two_KPI * mFrequency)/defaultSR;
}

