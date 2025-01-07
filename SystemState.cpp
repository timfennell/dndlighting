#include "SystemState.h"
#include "button_mapping.h"
#include <FastLED.h>

const CRGB SystemState::DEFAULT_COLOR = CRGB::Black;

// Fixed scale8 function for better performance
#define FASTLED_SCALE8_FIXED 1
uint8_t scale8_video_LEDS( uint8_t i, fract8 scale)
{
    uint8_t j = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
    return j;
}

SystemState::SystemState(CRGB* leds, std::map<const char*, Button>& buttonStateMap, TerrainConfig* terrains, int numTerrains) :
    leds(leds), buttonStateMap(buttonStateMap), terrains(terrains), numTerrains(numTerrains) {}

bool SystemState::getButtonState(const char* buttonName) {
       if (buttonStateMap.count(buttonName) > 0)
    {
     return buttonStateMap.at(buttonName).isPressed;
   }
    return false; // Button not found.
}

DeviceType SystemState::getDeviceType(const char* buttonName)
{
    if (buttonDeviceType.count(buttonName) > 0)
    {
        return buttonDeviceType.at(buttonName);
    }

    return DeviceType::Arduino; //defaults to Arduino
}
  std::map<const char*, Button>& SystemState::getButtonStateMap() {
        return buttonStateMap;
    }

void SystemState::updateIndicatorLights() {
     // Turn off all indicator LEDs
      for (int i = 0; i <= numTerrains; i++)
    {
         leds[SystemState::MAX_LEDS + i] = SystemState::DEFAULT_COLOR;
    }

    if (currentTerrain < numTerrains)
    {
        torch(SystemState::MAX_LEDS + currentTerrain, CRGB::White, 1.0f);
     }
    torch(SystemState::MAX_LEDS + numTerrains, CRGB::White, 1.0f);
}

void SystemState::runEffect(int effectIndex) {
    EffectInstance& effect = terrains[currentTerrain].effects[effectIndex];
    float intensity = getButtonState(effect.buttonName) ? 1.0f : 0.0f;

    switch (effect.type) {
        case 0: firePit(effect.startLed, effect.color, intensity); break;
        case 1: torch(effect.startLed, effect.color, intensity); break;
        case 2: altar(effect.startLed, effect.numLeds, effect.color, intensity); break;
        case 3: waterfall(effect.startLed, effect.numLeds, effect.color, intensity); break;
        case 4: water(effect.startLed, effect.numLeds, effect.color, intensity); break;
        case 5: ruin(effect.startLed, effect.numLeds, effect.color, intensity); break;
    }
}

void SystemState::update() {
   updateIndicatorLights();
    if(numTerrains > 0)
    {
         for (int i = 0; i < terrains[currentTerrain].numEffects; ++i) {
           runEffect(i);
         }
     }
}

void SystemState::nextTerrain() {
    currentTerrain = (currentTerrain + 1) % numTerrains;
}

void SystemState::firePit(int startLed, CRGB color, float intensity) {
    int endLed = startLed + 3;
    for (int i = startLed; i <= endLed; ++i) {
        leds[i] = color;
          leds[i].fadeLightBy((255 - (intensity * 255)));
    }
}

void SystemState::torch(int startLed, CRGB color, float intensity) {
    uint8_t flicker = random8(190, 255);
    leds[startLed] = CHSV(random8(0, 16), 255, (uint8_t)(intensity * flicker));
}

void SystemState::altar(int startLed, int numLeds, CRGB color, float intensity) {
    for (int i = startLed; i < startLed + numLeds; ++i) {
        leds[i] = color;
          leds[i].fadeLightBy((255 - (intensity * 255)));
    }
}

void SystemState::waterfall(int startLed, int numLeds, CRGB color, float intensity) {
    for (int i = startLed; i < startLed + numLeds; ++i) {
        leds[i] = color;
           leds[i].fadeLightBy((255 - (intensity * 255)));
    }
}

void SystemState::water(int startLed, int numLeds, CRGB color, float intensity) {
    for (int i = startLed; i < startLed + numLeds; ++i) {
        leds[i] = color;
          leds[i].fadeLightBy((255 - (intensity * 255)));
    }
}

void SystemState::ruin(int startLed, int numLeds, CRGB color, float intensity) {
    for (int i = startLed; i < startLed + numLeds; i++) {
         leds[i] = color;
           leds[i].fadeLightBy((255 - (intensity * 255)));
    }
}