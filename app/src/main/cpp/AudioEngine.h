//
// Created by Jose Ayerdis on 8/26/20.
//

#ifndef OBOEPLAYGROUND_AUDIOENGINE_H
#define OBOEPLAYGROUND_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include "Oscilator.h"

class AudioEngine : public oboe::AudioStreamCallback {

public:
    void start();

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    oboe::AudioStream *stream;
    Oscilator<float> oscilator;

    void tap(bool i);
    void setAmplitude(float amplitude);
    void setFrequency(float frequency);
};


#endif //OBOEPLAYGROUND_AUDIOENGINE_H
