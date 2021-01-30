#ifndef DISTORTION_H
#define DISTORTION_H

#include "daisy_seed.h"
#include "daisysp.h"
#include "../../include/IEffect.h"
#include "../../include/PedalConfig.h"
#include "../Inputs/Knob.h"
#include "../Inputs/Button.h"
#include "../Inputs/NFNToggle.h"

using namespace daisy;
using namespace daisysp;

/**********************************************
 * Distortion Effect
 * 
 * SPST 1 -
 * SPST 2 -
 * SPST 3 - 
 * SPST 4 - 
 * 
 * SPDT 1 - Clipping Level
 * SPDT 2 - 
 * 
 * Knob 1 - Boost
 * Knob 2 - Drive
 * Knob 3 - Tone
 * Knob 4 - 
 * 
 * LED 1 -
 * LED 2 -
 * LED 3 - 
 * LED 4 - 
 **********************************************/

class Distortion : public IEffect
{
public:
    void Setup(daisy::DaisySeed *hardware);
    void Cleanup();
    void AudioCallback(float **in, float **out, size_t size);
    void Loop();
    char *GetEffectName();

private:
    float WaveShape(float in);
    void ToneOnOff();
    void SetClipThreshold();

    size_t numChannels;
    float sample_rate;
    int currentClip = -1;
    const int LED_MAX_VALUE = 256;
    const int LED_MIN_VALUE = 0;

    // Effect constants
    const float boostLevelMin = 45.0f;
    const float boostLevelMax = 75.0f;
    const float driveLevelMin = 0.05f;
    const float driveLevelMax = 0.2f;
    const float toneLevelMin = -0.35f;
    const float toneLevelMax = 0.35f;
    const float clipThresholdHigh = 0.1f;
    const float clipThresholdMid = 0.5f;
    const float clipThresholdLow = 1.0f;

    // Effect parameters
    float boostLevel = 0.0f;
    float driveLevel = 0.0f;
    float toneLevel = 0.0f;
    bool isToneFilterOn = false;
    float toneFreqHP = 0.0f;
    float toneFreqLP = 0.0f;
    float hardClipThreshold = 1.0f;

    Knob boostLevelKnob;
    Knob driveKnob;
    Knob toneKnob;

    Button toneOnOffButton;

    NFNToggle clippingToggle;

    Tone toneLP;
    ATone toneHP;
    Balance balance;
};

#endif