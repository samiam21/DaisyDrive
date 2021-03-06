#ifndef BITCRUSH_H
#define BITCRUSH_H

#include "daisy_seed.h"
#include "daisysp.h"
#include "../../include/IEffect.h"
#include "../../include/PedalConfig.h"
#include "../Inputs/Knob.h"

using namespace daisy;
using namespace daisysp;

/**********************************************
 * Bit Crush Effect
 * 
 * SPST 1 - 
 * SPST 2 - 
 * SPST 3 - 
 * SPST 4 - 
 * 
 * SPDT 1 - 
 * SPDT 2 - 
 * 
 * Knob 1 - Effect Level
 * Knob 2 - Downsampling Factor
 * Knob 3 - Bits To Crush
 * Knob 4 - 
 * 
 * LED 1 - 
 * LED 2 - 
 * LED 3 - 
 * LED 4 - 
 **********************************************/

class Crush : public IEffect
{
public:
    void Setup(daisy::DaisySeed *hardware);
    void Cleanup();
    void AudioCallback(float **in, float **out, size_t size);
    void Loop();
    char *GetEffectName();

private:
    DaisySeed *hw;
    const int LED_MAX_VALUE = 256;
    const int LED_MIN_VALUE = 0;

    // Effect constants
    const float boostLevelMin = 1.0f;
    const float boostLevelMax = 10.0f;
    const float bitcrushMaxValue = 0.75f;
    const float bitcrushMinValue = 0.25f;

    // Effect parameters
    float boostLevel = 0.0f;
    float bitcrushLevel = 0.0f;
    float downsampleLevel = 0.0f;

    Decimator decimator;
    Knob boostLevelKnob;
    Knob bitcrushFactorKnob;
    Knob downsamplingFactorKnob;
};

#endif