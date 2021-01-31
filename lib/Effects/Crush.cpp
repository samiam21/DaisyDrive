#include "Crush.h"

void Crush::Setup(daisy::DaisySeed *hardware)
{
    hw = hardware;

    decimator.Init();

    // Initialize the knobs and effect values
    boostLevelKnob.Init(hw, KNOB_1_CHN, boostLevel, boostLevelMin, boostLevelMax);
    downsamplingFactorKnob.Init(hw, KNOB_2_CHN, downsampleLevel);
    bitcrushFactorKnob.Init(hw, KNOB_3_CHN, bitcrushLevel, bitcrushMinValue, bitcrushMaxValue);

    // Set parameters for bitcrusher
    decimator.SetDownsampleFactor(downsampleLevel);
    decimator.SetBitcrushFactor(bitcrushLevel);
}

void Crush::AudioCallback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        float wet;

        // Read signal from I/O and apply gain
        wet = in[AUDIO_IN_CH][i] * boostLevel;

        // Get wet signal by adding bitcrush
        wet = decimator.Process(wet);

        // Mix wet and dry and send to I/O
        out[AUDIO_OUT_CH][i] = wet;
    }
}

void Crush::Cleanup()
{
}

void Crush::Loop()
{
    // Update the boost level
    if (boostLevelKnob.SetNewValue(boostLevel))
    {
        debugPrintlnF(hw, "Updated the boost level to: %f", boostLevel);
    }

    // Update the bitcrush level
    if (bitcrushFactorKnob.SetNewValue(bitcrushLevel))
    {
        decimator.SetBitcrushFactor(bitcrushLevel);
        debugPrintlnF(hw, "Updated the bitcrush factor to: %f", bitcrushLevel);
    }

    // Update the downsample level
    if (downsamplingFactorKnob.SetNewValue(downsampleLevel))
    {
        decimator.SetDownsampleFactor(downsampleLevel);
        debugPrintlnF(hw, "Updated the downsample factor to: %f", downsampleLevel);
    }
}

char *Crush::GetEffectName()
{
    return (char *)"Bitcrush";
}