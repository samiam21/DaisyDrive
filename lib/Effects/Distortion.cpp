#include "Distortion.h"

void Distortion::Setup(daisy::DaisySeed *hardware)
{
    // // Initialize tone control button and LED
    // toneOnOffButton.Init(
    //     effectSPSTPin1, INPUT, [this]() { return ToneOnOff(); }, RISING);
    // pinMode(effectLedPin1, OUTPUT);
    // digitalWrite(effectLedPin1, (int)isToneFilterOn);

    // // Initialize the clipping toggle
    // clippingToggle.Init(effectSPDT1Pin1, INPUT, effectSPDT1Pin2, INPUT);
    // SetClipThreshold();

    // // Initialize the knobs and effect values
    // boostLevelKnob.Init(effectPotPin1, INPUT, boostLevel, boostLevelMin, boostLevelMax);
    // driveKnob.Init(effectPotPin2, INPUT, driveLevel, driveLevelMin, driveLevelMax);
    // toneKnob.Init(effectPotPin3, INPUT, toneLevel, toneLevelMin, toneLevelMax);

    // // Initialize the filters
    // sample_rate = DAISY.get_samplerate();
    // toneHP.Init(sample_rate);
    // toneLP.Init(sample_rate);
    // balance.Init(sample_rate);
}

void Distortion::AudioCallback(float **in, float **out, size_t size)
{
    float gain = driveLevel * 100 + 1.2;

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
        wet = dry * gain;
        wet = WaveShape(wet);

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

void Distortion::Cleanup()
{
    // // Turn off the LEDs
    // digitalWrite(effectLedPin1, LOW);
    // digitalWrite(effectLedPin2, LOW);
}

void Distortion::Loop()
{
    // // Update the boost level
    // if (boostLevelKnob.SetNewValue(boostLevel))
    // {
    //     debugPrint("Updated the boost level to: ");
    //     debugPrintlnF(boostLevel, 5);
    // }

    // // Update the drive level
    // if (driveKnob.SetNewValue(driveLevel))
    // {
    //     debugPrint("Updated the drive level to: ");
    //     debugPrintlnF(driveLevel, 5);
    // }

    // // Update the tone level
    // if (toneKnob.SetNewValue(toneLevel))
    // {
    //     debugPrint("Updated the tone level to: ");
    //     debugPrintlnF(toneLevel, 5);
    // }

    // // Update the clipping threshold
    // SetClipThreshold();
}

char *Distortion::GetEffectName()
{
    return (char *)"Distortion";
}

float Distortion::WaveShape(float in)
{
    // Soft clip
    if (in > 0)
    {
        in = 1 - expf(-in);
    }
    else
    {
        in = -1 + expf(in);
    }

    // Hard clip
    in = in > hardClipThreshold ? hardClipThreshold : in;
    in = in < -hardClipThreshold ? -hardClipThreshold : in;

    return in;
}

void Distortion::ToneOnOff()
{
    isToneFilterOn = !isToneFilterOn;
    //digitalWrite(effectLedPin1, (int)isToneFilterOn);
}

void Distortion::SetClipThreshold()
{
    // int togg = clippingToggle.ReadToggle();
    // if (togg != currentClip)
    // {
    //     if (togg == 0)
    //     {
    //         hardClipThreshold = clipThresholdHigh;
    //         debugPrintln("Clipping set to high");
    //     }
    //     else if (togg == 1)
    //     {
    //         hardClipThreshold = clipThresholdMid;
    //         debugPrintln("Clipping set to middle");
    //     }
    //     else
    //     {
    //         hardClipThreshold = clipThresholdLow;
    //         debugPrintln("Clipping set to low");
    //     }

    //     currentClip = togg;
    // }
}