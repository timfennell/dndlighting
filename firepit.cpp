#include <FastLED.h>  // Include FastLED.h
#include <stdint.h>
#include "firepit.h"

FirePit::FirePit(CRGB* leds, int startLED, int pin) : leds(leds), startLED(startLED), pin(pin) {
    this->endLED = startLED + 4 - 1;  // Firepit always uses 4 LEDs
    pinMode(pin, INPUT_PULLUP);
    intensity = 0.0f;
}

float FirePit::smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration) {
    float progress = (float)(millis() - startTime) / duration;
     if (progress > 100.0f || progress < 0.0f)
    {
       return startIntensity; //Return early, if we have a very large ratio
    }
    progress = constrain(progress, 0.0f, 1.0f);
    return startIntensity + (endIntensity - startIntensity) * progress;
}

void FirePit::update(bool switchClosed) {
    unsigned long currentTime = millis();

    if (switchClosed && currentStage == FadeOut) {
        currentStage = Buildup;
        buildupStartTime = currentTime;
    } else if (!switchClosed && currentStage != FadeOut) {
        currentStage = FadeOut;
        fadeOutStartTime = currentTime;
         intensity = 0.0f;
    }

    switch (currentStage) {
        case Buildup:
            intensity = smoothTransition(0.0, 1.0, buildupStartTime, BuildupDuration);
            if (intensity >= 0.99) {
                currentStage = Fade;
                fadeStartTime = currentTime;
            }
            break;

        case Fade:
            intensity = smoothTransition(1.0, 0.4, fadeStartTime, FadeDuration);
            if (intensity <= 0.41) {  // Small buffer to prevent rapid transitions
                currentStage = Stoke;
                stokeStartTime = currentTime;
            }
            break;

        case Stoke:
            intensity = smoothTransition(0.4, 1.0, stokeStartTime, StokeDuration);
            if (intensity >= 0.99) {
                currentStage = Fade;
                fadeStartTime = currentTime;
            }
            break;

        case FadeOut:
            if (intensity <= 0.01) {
                intensity = 0.0;
                break; // Exit early if already near zero
            }
            intensity = smoothTransition(intensity, 0.0, fadeOutStartTime, FadeOutDuration);
            break;
    }

    renderFire();
}

void FirePit::renderFire() {
    unsigned long currentTime = millis();

    if (currentTime - lastEmberUpdate > EmberUpdateInterval) {
        for (int i = startLED + 1; i <= endLED; i++) {  // Embers (start from second LED)
            uint8_t emberFlicker = random8(70, 100);
            uint8_t newEmberBrightness = (intensity > 0.0) ? (uint8_t)(intensity * emberFlicker * 0.5) : 0;
            leds[i].g = lerp8by8(leds[i].g, newEmberBrightness, 10);  // Smooth ember transitions
            leds[i] = CHSV(random8(0, 16), 255, newEmberBrightness);   // Ember color
        }
        lastEmberUpdate = currentTime;
    }


    if (intensity > 0.0) {
        uint8_t flameFlicker = random8(120, 180);
        uint8_t flameBrightness = (uint8_t)((intensity * flameFlicker) * 1.2)+50;
        leds[startLED] = CHSV(random8(0, 16), 255, flameBrightness); // Main Flame

        //Sparks
        if (currentTime - lastSparkTime > SparkInterval && intensity > 0.3) {
            leds[startLED] = CHSV(random8(0, 16), 255, 255); // Bright spark
            lastSparkTime = currentTime;
        }
    } else {
        for (int i = startLED; i <= endLED; i++) {
            leds[i] = CRGB::Black;  // Turn off LEDs when off
        }
    }
}