#ifndef water_h
#define water_h

//water.h
#include <FastLED.h>

class Water {
public:
    Water(CRGB* leds, int startIndex, int endIndex, int pin, CHSV baseColor);

    void update(bool switchClosed);

private:
    // LED Data and Ranges
    CRGB* leds;
    int startIndex;
    int endIndex;
    int pin;
    
    // Color Variables
    CHSV color1;
    CHSV color2;
    
    // Noise Variables
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t speed;
    uint8_t scale;
    uint16_t noiseOffset; 

    // Intensity (for fade in/out)
    float intensity;
    unsigned long transitionStartTime;
    bool isOn;

    // Function to create a smooth transition between two intensity values
    float smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration);

    // Function to update the LED colors for the effect
    void updateColors();

    // Duration for the effect to fade in
    int BuildupDuration = 500;

    // Duration for the effect to fade out
    int FadeOutDuration = 500;
};

#endif