#ifndef EFFECT_TYPE_H
#define EFFECT_TYPE_H

#include "IEffect.h"
#include "../lib/Effects/SimpleBypass.h"
#include "../lib/Effects/Crush.h"
#include "../lib/Effects/Distortion.h"
#include "../lib/Effects/Fuzz.h"
#include "../lib/Effects/ModDrive.h"
#include "../lib/Effects/NaturalDrive.h"

// Effect Objects
SimpleBypass simpleBypass;
Crush bitCrush;
Distortion distortion;
ModDrive modDrive;
Fuzz fuzz;
NaturalDrive naturalDrive;

/**
 * The rotary encoder is using Gray code, not standard hex.
 * The sequence of decimal numbers that it produces is as follows:
 * 0, 1, 3, 2, 6, 7, 5, 4, 12, 13, 15, 14, 10, 11, 9, 8
 */
enum EffectType
{
    BITCRUSH = 0,
    MODDRIVE = 1,
    NATURALDRIVE = 3,
    DISTORTION = 2,
    FUZZ = 6,

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
    case MODDRIVE:
        return (IEffect *)&modDrive;
    case NATURALDRIVE:
        return (IEffect *)&naturalDrive;
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