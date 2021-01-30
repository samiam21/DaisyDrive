#ifndef EFFECT_TYPE_H
#define EFFECT_TYPE_H

#include "IEffect.h"
#include "../lib/Effects/SimpleBypass.h"
#include "../lib/Effects/BitCrush.h"
#include "../lib/Effects/Distortion.h"
#include "../lib/Effects/Fuzz.h"
#include "../lib/Effects/Drive.h"

// Effect Objects
SimpleBypass simpleBypass;
BitCrush bitCrush;
Distortion distortion;
Drive overdrive;
Fuzz fuzz;

/**
 * The rotary encoder is using Gray code, not standard hex.
 * The sequence of decimal numbers that it produces is as follows:
 * 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
 */
enum EffectType
{
    BITCRUSH = 0,
    OVERDRIVE = 1,
    DISTORTION = 3,
    FUZZ = 2,

    SIMPLEBYPASS = 8,
    UNSET = 99
};

/**
 * Returns the effect object based on the passed in enum
 */
extern IEffect *GetEffectObject(EffectType type)
{
    switch (type)
    {
    case FUZZ:
        return (IEffect *)&fuzz;
    case OVERDRIVE:
        return (IEffect *)&overdrive;
    case DISTORTION:
        return (IEffect *)&distortion;
    case BITCRUSH:
        return (IEffect *)&bitCrush;
    case SIMPLEBYPASS:
    case UNSET:
    default:
        return (IEffect *)&simpleBypass;
    }
};

#endif