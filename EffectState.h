#ifndef EFFECTSTATE_H
#define EFFECTSTATE_H
#include <FastLED.h>

class EffectState {
public:
    // General State
    bool isOn = false;          // Is the effect currently on?
    float intensity = 0.0f;      // Current intensity
    unsigned long transitionStartTime = 0; // Start time for transitions
    unsigned long lastColorUpdate = 0;


     // For FirePit Effects,
    enum FireStage { Buildup, Fade, Stoke, FadeOut };
    FireStage currentFireStage = FadeOut;
    unsigned long buildupStartTime = 0;
    unsigned long fadeStartTime = 0;
    unsigned long stokeStartTime = 0;
    unsigned long fadeOutStartTime = 0;
    unsigned long lastEmberUpdate = 0;
     unsigned long lastSparkTime = 0;


    // Common Timings
      const int BuildupDuration = 500;
      const int FadeOutDuration = 1000;
       const int FadeDuration = 120000;
       const int StokeDuration = 60000;

    //Common Update Intervals
      const int EmberUpdateInterval = 50;
      const int SparkInterval = 2000;
      const int colorChangeInterval = 5000;

    // For Altar Effects
    CHSV color1;
    CHSV color2;
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;
    uint8_t speed = 2;
    uint8_t scale = 5;

    // For Waterfall and Water Effects
    uint16_t noiseOffset = 0;

    // Constructor (declaration only)
    EffectState();
};

#endif