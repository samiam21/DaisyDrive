#include "Fuzz.h"

void Fuzz::Setup(daisy::DaisySeed *hardware)
{
    hw = hardware;

    // Initialize tone control button and LED
    toneOnOffButton.Init(hw->GetPin(effectSPSTPin1));
    toneLed.Init(hw->GetPin(effectLedPin1), false);
    toneLed.Set(isToneFilterOn ? 1.f : 0);
    toneLed.Update();

    // Initialize the knobs and effect values
    boostLevelKnob.Init(hw, KNOB_1_CHN, boostLevel, boostLevelMin, boostLevelMax);
    driveLevelKnob.Init(hw, KNOB_2_CHN, driveLevel, driveLevelMin, driveLevelMax);
    toneLevelKnob.Init(hw, KNOB_3_CHN, toneLevel, toneLevelMin, toneLevelMax);

    // Initialize the filters
    sample_rate = hw->AudioSampleRate();
    toneHP.Init(sample_rate);
    toneLP.Init(sample_rate);
    balance.Init(sample_rate);
}

void Fuzz::AudioCallback(float **in, float **out, size_t size)
{
    // Set signal parameters
    //float clipLevel = boostLevel / driveLevel;
    float clipLevel = abs(driveLevel);

    if (isToneFilterOn)
    {
        // Set the filter frequencies
        if (toneLevel < 0.0f)
        {
            // Left half of pot HP off, LP on
            toneFreqHP = 0;
            toneFreqLP = 5000.0f * (powf(10, 2 * toneLevel)) + 100.f; //This is a more complex function just to make the taper nice and smooth, the filter turned on too fast when linear
        }
        else
        {
            // Right half of pot HP on, LP off
            toneFreqHP = 5000.0f * powf(10, 2.f * toneLevel - 2); //This is a more complex function just to make the taper nice and smooth, the filter turned on too fast when linear
            toneFreqLP = 1000000.0f;                              // just something very high so the filter is not killing any actual guitar sound
        }

        // Update tone filters
        toneHP.SetFreq(toneFreqHP);
        toneLP.SetFreq(toneFreqLP);
    }

    for (size_t i = 0; i < size; i++)
    {
        float wet, dry;

        // Adjust input signal by the gain
        dry = in[AUDIO_IN_CH][i];
        dry *= boostLevel;

        // Shape the wet waveform
        wet = WaveShape(dry, clipLevel);

        // Output the signal with or without tone control
        if (isToneFilterOn)
        {
            // Apply the filters
            wet = toneHP.Process(wet);
            wet = toneLP.Process(wet);
        }

        // Balance the output to account for volume loss in processing
        wet = balance.Process(wet, dry);

        // Send the output signal
        out[AUDIO_OUT_CH][i] = wet;
    }
}

void Fuzz::Cleanup()
{
    // Turn off the LED
    toneLed.Set(0);
    toneLed.Update();
}

void Fuzz::Loop()
{
    // Update the boost level
    if (boostLevelKnob.SetNewValue(boostLevel))
    {
        debugPrintlnF(hw, "Updated the boost level to: %f", boostLevel);
    }

    // Update the drive level
    if (driveLevelKnob.SetNewValue(driveLevel))
    {
        debugPrintlnF(hw, "Updated the drive level to: %f", driveLevel);
    }

    // Update the hard gain level
    if (toneLevelKnob.SetNewValue(toneLevel))
    {
        debugPrintlnF(hw, "Updated the tone level to: %f", toneLevel);
    }

    // Check for the tone on/off
    if (toneOnOffButton.IsPressed())
    {
        isToneFilterOn = !isToneFilterOn;
        toneLed.Set(isToneFilterOn ? 1.f : 0);
        toneLed.Update();
    }
}

char *Fuzz::GetEffectName()
{
    return (char *)"Fuzz";
}

float Fuzz::WaveShape(float in, float clipLevel)
{
    // Hard clip
    in = in > clipLevel ? clipLevel : in;
    in = in < -clipLevel ? -clipLevel : in;

    return in;
}