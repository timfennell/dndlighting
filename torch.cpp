#include <FastLED.h>  // Include FastLED.h
#include <stdint.h>
#include "torch.h"

Torch::Torch(CRGB* leds, int startLed, int pin) : 
    leds(leds), startLED(startLed), pin(pin) { 
    if (pin != 0) {
        pinMode(pin, INPUT_PULLUP);
    }
    isOn = false;
    intensity = 0;
}

void Torch::update(bool switchClosed) {
    unsigned long currentTime = millis();

    if (switchClosed && !isOn) { // Button pressed, torch should turn on
        isOn = true;
        transitionStartTime = currentTime; // Start buildup
    } else if (!switchClosed && isOn) {  //Button released, torch off
        isOn = false;
        transitionStartTime = currentTime;   //Start fade out
        intensity = 0.0f; //Reset intensity, to prevent overflow issue
    }

    if (isOn) {
        intensity = smoothTransition(0.0f, 1.0f, transitionStartTime, BuildupDuration);
    } else { //Fading out
        intensity = smoothTransition(intensity, 0.0f, transitionStartTime, FadeOutDuration);
    }

    // Set the LED color based on intensity
    leds[startLED] = CHSV(random8(0, 16), 255, (uint8_t)(intensity * 220)); 
}

float Torch::smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration) {
  float ratio = (millis() - startTime) / (float)duration;
    if (ratio > 100.0f || ratio < 0.0f)
    {
       return startIntensity; //Return early, if we have a very large ratio
    }
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    return startIntensity + (endIntensity - startIntensity) * ratio;
}