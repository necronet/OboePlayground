//
// Created by Jose Ayerdis on 8/26/20.
//

#ifndef OBOEPLAYGROUND_AUDIOENGINE_H
#define OBOEPLAYGROUND_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include "Oscilator.h"

struct DataStr {
    float* data;
    int32_t numFrames;
};

class AudioEngine : public oboe::AudioStreamCallback {

public:
    DataStr data;
    void start();

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    oboe::AudioStream *stream;
    Oscilator<float> oscilator;

    DataStr getCurrentData();
    void tap(bool i);
    void setAmplitude(float amplitude);
    void setFrequency(float frequency);
    bool isWaveOn();
};


#endif //OBOEPLAYGROUND_AUDIOENGINE_H
