#include <FastLED.h> // Include FastLED.h
#include <stdint.h>
#include "waterfall.h"

Waterfall::Waterfall(CRGB* leds, int startIndex, int endIndex, int pin, CHSV baseColor) :
    leds(leds), startIndex(startIndex), endIndex(endIndex), pin(pin) {
    pinMode(pin, INPUT_PULLUP);

    // Initialize colors with hue shift
    color1 = CHSV(baseColor.hue + 10, baseColor.sat, baseColor.val);
    color2 = CHSV(baseColor.hue - 10, baseColor.sat, baseColor.val);

    // Initialize noise variables
    x = random8();
    y = random8();
    z = random8();
    speed = random8(2, 6);
    scale = random8(10, 20);
    noiseOffset = 0; 
    isOn = false; // Initialize isOn
    intensity = 0.0f;
}

float Waterfall::smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration) {
    float progress = (float)(millis() - startTime) / duration;
      if (progress > 100.0f || progress < 0.0f)
    {
       return startIntensity; //Return early, if we have a very large ratio
    }
    progress = constrain(progress, 0.0f, 1.0f);
    return startIntensity + (endIntensity - startIntensity) * progress;
}

void Waterfall::updateColors() {
    EVERY_N_MILLISECONDS(20) {
        noiseOffset += speed;

        for (int i = startIndex; i <= endIndex; i++) {
            // Layered noise for brightness variation
            uint8_t noiseVal1 = inoise8(x + i * scale, y + noiseOffset * (endIndex - startIndex - i + 1), z);
            uint8_t noiseVal2 = inoise8(x + i * scale * 2, y + noiseOffset * 2, z * 2);

            uint8_t brightness = map(noiseVal1, 0, 255, 64, 255);
            brightness = (brightness + map(noiseVal2, 0, 255, -64, 64)) / 2;

            // Moving twinkles
            uint8_t twinkleProbability = inoise8(x + i * scale * 4, y + noiseOffset * 4, z * 4);
            if (twinkleProbability > 220) {  // Twinkle threshold
                brightness = 255;
            }

            // Blend colors (and convert to HSV)
            CRGB blendedRgb = blend(color1, color2, noiseVal1);  // Blend in RGB
            CHSV blendedHsv = rgb2hsv_approximate(blendedRgb); // Convert to HSV

            leds[i] = CHSV(blendedHsv.hue, 255, (uint8_t)(brightness * intensity)); // Use blendedHsv.hue
        }
    }
}

void Waterfall::update(bool switchClosed) {
    unsigned long currentTime = millis();

    if (switchClosed && !isOn) {
        isOn = true;
        transitionStartTime = currentTime;
    } else if (!switchClosed && isOn) {
        isOn = false;
        transitionStartTime = currentTime;
         intensity = 0.0f;
    }

    if (isOn) {
        intensity = smoothTransition(0.0f, 1.0f, transitionStartTime, BuildupDuration);
        updateColors();
    } else {
        intensity = smoothTransition(intensity, 0.0f, transitionStartTime, FadeOutDuration);
        for (int i = startIndex; i <= endIndex; i++) {
            leds[i].fadeToBlackBy((uint8_t)(256 - 256.0f * intensity));
        }
    }
}