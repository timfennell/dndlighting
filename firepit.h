//firepit.h
#ifndef FIREPIT_H
#define FIREPIT_H
#include <FastLED.h>

class FirePit {
private:
    CRGB* leds;
    int startLED;
    int endLED;
    int pin;

    float intensity = 0.0;
    enum FireStage { Buildup, Fade, Stoke, FadeOut };
    FireStage currentStage = FadeOut;
    unsigned long buildupStartTime = 0;
    unsigned long fadeStartTime = 0;
    unsigned long stokeStartTime = 0;
    unsigned long fadeOutStartTime = 0;
    unsigned long lastEmberUpdate = 0;
    unsigned long lastSparkTime = 0;

    const int BuildupDuration = 30000;
    const int FadeDuration = 120000;
    const int StokeDuration = 60000;
    const int FadeOutDuration = 30000;
    const int EmberUpdateInterval = 50;
    const int SparkInterval = 2000;

    float smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration);

public:
    FirePit(CRGB* leds, int startLED, int pin); // Simplified constructor
    void update(bool switchClosed);
    void renderFire();
};

#endif