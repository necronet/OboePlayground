#ifndef SAMPLES_IRENDERABLEAUDIO_H
#define SAMPLES_IRENDERABLEAUDIO_H

#include <cstdint>
#include <string>

class IRenderableAudio {

public:
    virtual ~IRenderableAudio() = default;
    virtual void renderAudio(float *audioData, int32_t numFrames) = 0;
};


#endif //SAMPLES_IRENDERABLEAUDIO_H