//altar.h
#ifndef ALTAR_H
#define ALTAR_H
#include <FastLED.h>

class Altar {
private:
    CRGB* leds;
    int led1Index;
    int led2Index;
    int pin;
    CRGB targetColor;
    CHSV hsvTarget;
    CHSV color1;
    CHSV color2;
    unsigned long lastColorChangeTime = 0;
    int colorChangeInterval = 0;
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t speed;
    uint8_t scale;
    bool isOn = false;
    unsigned long transitionStartTime = 0;
    float intensity = 0.0; // Added intensity member
    const int BuildupDuration = 500;
    const int FadeOutDuration = 1000;


    float smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration);
    void setAltarColors(float intensity);
    void updateColors();

public:
    Altar(CRGB* leds, int led1Index, int led2Index, int pin, CRGB targetColor);
    void update(bool switchClosed);
};

#endif