#ifndef EFFECTINSTANCE_H
#define EFFECTINSTANCE_H
#include <FastLED.h>

struct EffectInstance {
    int type;
    const char* buttonName;
    int startLed;
    int numLeds;
    CRGB color;
    int groupId;
};

#endif