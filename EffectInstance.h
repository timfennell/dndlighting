//EffectInstance.h

#ifndef EFFECTINSTANCE_H
#define EFFECTINSTANCE_H
#include <FastLED.h>

// Structure to define an effect instance
struct EffectInstance {
    int type;       // 0 = FirePit, 1 = Torch, 2 = Altar, 3 = Waterfall, 4 = Water, 5 = Ruin
    const char* buttonName;   // Button Name that the effect is mapped to
    int startLed;  // Starting LED index for this instance
    int numLeds;   // Number of LEDs used by the effect (if applicable)
    uint32_t color; // Color for the effect (used only for Altar, Waterfall, Water, Ruin)
    int groupId;    // Group ID for controlling multiple effects with one button (-1 for no group)
};

#endif