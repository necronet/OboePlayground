//
// Created by Jose Ayerdis on 8/26/20.
//

#ifndef OBOEPLAYGROUND_OSCILATOR_H
#define OBOEPLAYGROUND_OSCILATOR_H

#include <math.h>

constexpr double kPI = M_PI;
constexpr double two_KPI = 2 * kPI;


template <typename T>
class Oscilator  {
public:
    void renderAudio(T *audioData, int32_t numFrames);
    void setWaveOn(bool isWaveOn);
    void setAmplitude(float amplitude);
    void setFrequency(float frequency);

private:
    bool mIsWaveOn = false;
    float mAmplitude = .1;
    double mPhase = 0;
    double mFrequency = 440.0;
    double defaultSR = 48000;
    double mPhaseIncrement = (two_KPI * mFrequency)/defaultSR;
};


#endif //OBOEPLAYGROUND_OSCILATOR_H
