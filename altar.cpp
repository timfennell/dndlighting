#include <FastLED.h>  // Include FastLED.h
#include <stdint.h>
#include "altar.h"

Altar::Altar(CRGB* leds, int led1Index, int led2Index, int pin, CRGB targetColor) :
    leds(leds), led1Index(led1Index), led2Index(led2Index), pin(pin), targetColor(targetColor) {
    pinMode(pin, INPUT_PULLUP);
    hsvTarget = rgb2hsv_approximate(targetColor);
    color1 = CHSV(hsvTarget.hue - 15, 255, 255);
    color2 = CHSV(hsvTarget.hue + 15, 255, 255);
    colorChangeInterval = random(30000, 60001);
    x = random8();
    y = random8();
    z = random8();
    speed = random8(2, 8);
    scale = random8(8, 32);
    intensity = 0.0f;
}

float Altar::smoothTransition(float startIntensity, float endIntensity, unsigned long startTime, int duration) {
    float progress = (float)(millis() - startTime) / duration;
    if (progress > 100.0f || progress < 0.0f)
    {
       return startIntensity; //Return early, if we have a very large ratio
    }
    progress = constrain(progress, 0.0f, 1.0f);
    return startIntensity + (endIntensity - startIntensity) * progress;
}


void Altar::setAltarColors(float intensity) {
    leds[led1Index] = CHSV(color1.hue, color1.sat, (uint8_t)(intensity * 255.0f));
    leds[led2Index] = CHSV(color2.hue, color2.sat, (uint8_t)(intensity * 255.0f));
}


void Altar::updateColors() {
    EVERY_N_MILLISECONDS(20) {
        uint8_t noiseVal = inoise8(x, y, z);
        uint8_t shimmer1 = beatsin8(10, 64, 255, 0, noiseVal);
        uint8_t shimmer2 = beatsin8(13, 64, 255, 0, noiseVal + 64);

        leds[led1Index] = CHSV(color1.hue, color1.sat, (uint8_t)(shimmer1 * intensity));
        leds[led2Index] = CHSV(color2.hue, color2.sat, (uint8_t)(shimmer2 * intensity));

        z += speed;
    }

    EVERY_N_SECONDS(random(30, 61)) {
        CHSV shiftedTarget = CHSV(hsvTarget.hue + random(-10, 11), 255, 255);
        color1.hue = shiftedTarget.hue - 15;
        color2.hue = shiftedTarget.hue + 15;
    }
}


void Altar::update(bool switchClosed) {
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
        setAltarColors(intensity);
    }
}