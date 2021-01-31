#ifndef MODDRIVE_H
#define MODDRIVE_H

#include <math.h>
#include "daisy_seed.h"
#include "daisysp.h"
#include "../../include/IEffect.h"
#include "../../include/PedalConfig.h"
#include "../Inputs/Knob.h"
#include "../Inputs/Button.h"

using namespace daisy;
using namespace daisysp;

/**********************************************
 * Modulated Overdrive Effect
 * 
 * SPST 1 - Tone Filter On/Off
 * SPST 2 - 
 * SPST 3 - 
 * SPST 4 - 
 * 
 * SPDT 1 - 
 * SPDT 2 - 
 * 
 * Knob 1 - Boost
 * Knob 2 - Drive
 * Knob 3 - Tone
 * Knob 4 - 
 * 
 * LED 1 - Tone Filter Indicator
 * LED 2 - 
 * LED 3 - 
 * LED 4 - 
 **********************************************/

class ModDrive : public IEffect
{
public:
    void Setup(daisy::DaisySeed *hardware);
    void Cleanup();
    void AudioCallback(float **in, float **out, size_t size);
    void Loop();
    char *GetEffectName();

private:
    float WaveShape(float in, float k);

    DaisySeed *hw;
    float sample_rate;
    const int LED_MAX_VALUE = 256;
    const int LED_MIN_VALUE = 0;

    // Effect constants
    const float boostLevelMin = 30.0f;
    const float boostLevelMax = 60.0f;
    const float driveLevelMin = 25.0f;
    const float driveLevelMax = 75.0f;
    const float toneLevelMin = -0.35f;
    const float toneLevelMax = 0.35f;

    // Effect parameters
    float boostLevel = 0.0f;
    float driveLevel = 0.0f;
    float toneLevel = 0.0f;
    bool isToneFilterOn = false;
    float toneFreqHP = 0.0f;
    float toneFreqLP = 0.0f;

    Knob boostLevelKnob;
    Knob driveLevelKnob;
    Knob toneLevelKnob;

    Button toneOnOffButton;
    Led toneLed;

    Tone toneLP;
    ATone toneHP;
    Balance balance;
};

#endif