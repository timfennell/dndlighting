#ifndef TORCH_H
#define TORCH_H
#include <FastLED.h>

class Torch {
private:
    CRGB* leds;
    int startLED;
    int pin;
    float intensity = 0.0;
    bool isOn = false;  // Track on/off state
    unsigned long transitionStartTime = 0; // For both buildup and fadeout

    const int BuildupDuration = 500;     // Adjust buildup time
    const int FadeOutDuration = 1000;    // Adjust fadeout time

    float smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration);

public:
    Torch(CRGB* leds, int startLED, int pin = 0);
    void update(bool switchClosed);

};

#endif