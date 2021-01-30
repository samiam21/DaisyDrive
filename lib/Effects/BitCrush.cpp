#include "BitCrush.h"

void BitCrush::Setup(daisy::DaisySeed *hardware)
{
    decimator.Init();

    // // Initialize the knobs and effect values
    // boostLevelKnob.Init(effectPotPin1, INPUT, boostLevel, boostLevelMin, boostLevelMax);
    // downsamplingFactorKnob.Init(effectPotPin2, INPUT, downsampleLevel);
    // bitcrushFactorKnob.Init(effectPotPin3, INPUT, bitcrushLevel, bitcrushMinValue, bitcrushMaxValue);

    // Set parameters for bitcrusher
    decimator.SetDownsampleFactor(downsampleLevel);
    decimator.SetBitcrushFactor(bitcrushLevel);
}

void BitCrush::AudioCallback(float **in, float **out, size_t size)
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

void BitCrush::Cleanup()
{
}

void BitCrush::Loop()
{
    // // Update the boost level
    // if (boostLevelKnob.SetNewValue(boostLevel))
    // {
    //     debugPrint("Updated the boost level to: ");
    //     debugPrintlnF(boostLevel, 5);
    // }

    // // Update the bitcrush level
    // if (bitcrushFactorKnob.SetNewValue(bitcrushLevel))
    // {
    //     decimator.SetBitcrushFactor(bitcrushLevel);
    //     debugPrint("Updated the bitcrush factor to: ");
    //     debugPrintlnF(bitcrushLevel, 5);
    // }

    // // Update the downsample level
    // if (downsamplingFactorKnob.SetNewValue(downsampleLevel))
    // {
    //     decimator.SetDownsampleFactor(downsampleLevel);
    //     debugPrint("Updated the downsample factor to: ");
    //     debugPrintlnF(downsampleLevel, 5);
    // }
}

char *BitCrush::GetEffectName()
{
    return (char *)"Bitcrush";
}