#include "SystemState.h"
#include "button_mapping.h"
#include <FastLED.h>

// Fixed scale8 function for better performance
#define FASTLED_SCALE8_FIXED 1
uint8_t scale8_video_LEDS( uint8_t i, fract8 scale)
{
    uint8_t j = (((int)i * (int)scale) >> 8) + ((i&&scale)?1:0);
    return j;
}

const CRGB SystemState::DEFAULT_COLOR = CRGB::Black;

SystemState::SystemState(CRGB* leds, std::map<const char*, Button>& buttonStateMap, TerrainConfig* terrains, int numTerrains) :
    leds(leds), buttonStateMap(buttonStateMap), terrains(terrains), numTerrains(numTerrains) 
    {
    }

bool SystemState::getButtonState(const char* buttonName) {
    if (buttonStateMap.count(buttonName)) {
        return buttonStateMap.at(buttonName).isPressed;
    }
    return false;
}

DeviceType SystemState::getDeviceType(const char* buttonName)
{
    if (buttonDeviceType.count(buttonName) > 0)
    {
        return buttonDeviceType.at(buttonName);
    }

    return DeviceType::Arduino; //defaults to Arduino
}
  const std::map<const char*, Button>& SystemState::getButtonStateMap() const {
        return buttonStateMap;
    }

CHSV SystemState::getHsvColor(CRGB color)
{
  return rgb2hsv_approximate(color);
}

void SystemState::updateIndicatorLights() {
    // Turn off all indicator LEDs
    for (int i = 0; i < numTerrains; i++)
    {
        leds[MAX_LEDS + i] = DEFAULT_COLOR;
    }
     if (currentTerrain < numTerrains)
    {
        leds[MAX_LEDS + currentTerrain] = CRGB::Orange;
    }
    leds[MAX_LEDS + numTerrains] = CRGB::Orange;
}

void SystemState::runEffect(int effectIndex) {
    EffectInstance& effect = terrains[currentTerrain].effects[effectIndex];
    float intensity = getButtonState(effect.buttonName) ? 1.0f : 0.0f;

    switch (effect.type) {
        case 0: firePit(effect.startLed, intensity); break;
        case 1: torch(effect.startLed, effect.color, intensity); break;
        case 2: altar(effect.startLed, effect.numLeds, effect.color, intensity); break;
        case 3: waterfall(effect.startLed, effect.numLeds, intensity); break;
        case 4: water(effect.startLed, effect.numLeds, effect.color, intensity); break;
        case 5: ruin(effect.startLed, effect.numLeds, intensity); break;
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

void SystemState::clearLedsForTerrain() {
     // Clear all non-indicator LEDs first
    for(int i=0; i < MAX_LEDS; i++)
     {
        leds[i] = DEFAULT_COLOR;
    }

    // Then, loop through all effects in the current terrain
    // and ensure their LEDs are lit as expected
    for(int i = 0; i < terrains[currentTerrain].numEffects; i++) {
        EffectInstance& effect = terrains[currentTerrain].effects[i];
         if (getButtonState(effect.buttonName)) {
              // if effect button is on, ensure effect leds are on
             switch (effect.type) {
                case 0: //FirePit
                     for(int j = 0; j < 4; j++)
                     {
                         leds[effect.startLed + j] = CHSV(random8(0, 16), 255, 50);
                     }
                     break;
                 case 1: //Torch
                     leds[effect.startLed] = CHSV(getHsvColor(effect.color).hue, 255, 50);
                    break;
                 case 2: //Altar
                     for(int j = 0; j < effect.numLeds; j++)
                     {
                         leds[effect.startLed + j] = CHSV(getHsvColor(effect.color).hue, 255, 50);
                     }
                     break;
                 case 3: //Waterfall
                      for(int j = 0; j < effect.numLeds; j++)
                     {
                          leds[effect.startLed + j] = CHSV(160, 255, 50);
                     }
                      break;
                  case 4: //Water
                     for(int j = 0; j < effect.numLeds; j++)
                     {
                         leds[effect.startLed + j] = CHSV(160, 255, 50);
                     }
                      break;
                  case 5: //Ruin
                    for(int j = 0; j < effect.numLeds; j++)
                     {
                        leds[effect.startLed + j] = CHSV(0, 0, 50);
                    }
                     break;
            }
         }
     }
}


void SystemState::nextTerrain() {
    clearLedsForTerrain(); // Clear the leds before changing the terrain
    currentTerrain = (currentTerrain + 1) % numTerrains;
}

 float SystemState::smoothTransition(float startIntensity, float endIntensity, float progress)
{
     progress = constrain(progress, 0.0f, 1.0f);
    return startIntensity + (endIntensity - startIntensity) * progress;
}

void SystemState::firePit(int startLed, float intensity) {
     struct FirePitState {
        unsigned long buildupStartTime = 0;
        unsigned long fadeStartTime = 0;
        unsigned long stokeStartTime = 0;
        unsigned long fadeOutStartTime = 0;
        unsigned long lastEmberUpdate = 0;
        unsigned long lastSparkTime = 0;
        enum class FireStage { Buildup, Fade, Stoke, FadeOut } currentFireStage = FireStage::FadeOut;
    };
    static FirePitState state;

    unsigned long currentTime = millis();
    int endLED = startLed + 4 - 1;

    if (intensity > 0.0f && state.currentFireStage == FirePitState::FireStage::FadeOut) {
        state.currentFireStage = FirePitState::FireStage::Buildup;
        state.buildupStartTime = currentTime;
    } else if (intensity == 0.0f && state.currentFireStage != FirePitState::FireStage::FadeOut) {
        state.currentFireStage = FirePitState::FireStage::FadeOut;
        state.fadeOutStartTime = currentTime;
    }

    float progress;
    switch (state.currentFireStage) {
        case FirePitState::FireStage::Buildup:
            progress = (currentTime - state.buildupStartTime) / (float)FIRE_PIT_BUILDUP_DURATION_MS;
            intensity = smoothTransition(0.0, 1.0, progress);
            if (intensity >= 0.99) {
                state.currentFireStage = FirePitState::FireStage::Fade;
                state.fadeStartTime = currentTime;
            }
            break;

        case FirePitState::FireStage::Fade:
            progress = (currentTime - state.fadeStartTime) / (float)FIRE_PIT_FADE_DURATION_MS;
            intensity = smoothTransition(1.0, 0.4, progress);
             if (intensity <= 0.41) {  // Small buffer to prevent rapid transitions
                state.currentFireStage = FirePitState::FireStage::Stoke;
                state.stokeStartTime = currentTime;
            }
            break;

        case FirePitState::FireStage::Stoke:
            progress = (currentTime - state.stokeStartTime) / (float)FIRE_PIT_STOKE_DURATION_MS;
              intensity = smoothTransition(0.4, 1.0, progress);
            if (intensity >= 0.99) {
                state.currentFireStage = FirePitState::FireStage::Fade;
                state.fadeStartTime = currentTime;
            }
            break;

        case FirePitState::FireStage::FadeOut:
            if (intensity <= 0.01) {
                 intensity = 0.0;
                break; // Exit early if already near zero
            }
            progress = (currentTime - state.fadeOutStartTime) / (float)FIRE_PIT_FADEOUT_DURATION_MS;
            intensity = smoothTransition(intensity, 0.0, progress);
            break;
    }
    if (currentTime - state.lastEmberUpdate > FIRE_PIT_EMBER_UPDATE_INTERVAL_MS) {
        for (int i = startLed + 1; i <= endLED; i++) {  // Embers (start from second LED)
            uint8_t emberFlicker = random8(70, 100);
            uint8_t newEmberBrightness = (intensity > 0.0) ? (uint8_t)(intensity * emberFlicker * 0.5) : 0;
            leds[i].g = lerp8by8(leds[i].g, newEmberBrightness, 10);  // Smooth ember transitions
            leds[i] = CHSV(random8(0, 16), 255, newEmberBrightness);   // Ember color
        }
        state.lastEmberUpdate = currentTime;
    }
     if (intensity > 0.0) {
        uint8_t flameFlicker = random8(120, 180);
        uint8_t flameBrightness = (uint8_t)((intensity * flameFlicker) * 1.2)+50;
        leds[startLed] = CHSV(random8(0, 16), 255, flameBrightness); // Main Flame

       //Sparks
        if (currentTime - state.lastSparkTime > FIRE_PIT_SPARK_INTERVAL_MS && intensity > 0.3) {
            leds[startLed] = CHSV(random8(0, 16), 255, 255); // Bright spark
            state.lastSparkTime = currentTime;
        }
    } else {
        for (int i = startLed; i <= endLED; i++) {
           leds[i] = CRGB::Black;  // Turn off LEDs when off
        }
    }
}

void SystemState::torch(int startLed, CRGB color, float intensity) {
    CHSV hsvColor = getHsvColor(color);
    uint8_t flicker = random8(190, 255);
    leds[startLed] = CHSV(hsvColor.hue, hsvColor.sat, (uint8_t)(intensity * flicker));
}

void SystemState::altar(int startLed, int numLeds, CRGB color, float intensity) {
    struct AltarState {
        unsigned long lastColorChangeTime = 0;
        unsigned long lastColorUpdate = 0;
            CHSV color1 = CHSV(0, 255, 255);
        CHSV color2 = CHSV(0, 255, 255);
         uint8_t z = 0;
        
        uint8_t speed = 2;
        uint8_t scale = 5;
    };
    static AltarState state;
    unsigned long currentTime = millis();
    uint8_t noiseVal = inoise8(0, 0, state.z);
    uint8_t shimmer1 = beatsin8(10, 64, 255, 0, noiseVal);
    uint8_t shimmer2 = beatsin8(13, 64, 255, 0, noiseVal + 64);
    leds[startLed] = CHSV(state.color1.hue, state.color1.sat, (uint8_t)(shimmer1 * intensity));
    leds[startLed+1] = CHSV(state.color2.hue, state.color2.sat, (uint8_t)(shimmer2 * intensity));
    state.z += state.speed;

    if (currentTime - state.lastColorChangeTime > COLOR_CHANGE_INTERVAL_MS) {
        CHSV shiftedTarget = CHSV(getHsvColor(color).hue + random(-10, 11), 255, 255);
        state.color1.hue = shiftedTarget.hue - 15;
        state.color2.hue = shiftedTarget.hue + 15;
        state.lastColorChangeTime = currentTime;
    }
}

void SystemState::waterfall(int startLed, int numLeds, float intensity) {
    struct WaterfallState {
        unsigned long lastColorUpdate = 0;
        uint16_t noiseOffset = 0;
        uint8_t z = 0;
        uint8_t speed = 2;
        uint8_t scale = 5;
        CHSV color1 = CHSV(0, 255, 255);
        CHSV color2 = CHSV(0, 255, 255);
    };
    static WaterfallState state;
    unsigned long currentTime = millis();
    if (currentTime - state.lastColorUpdate > 20)
    {
        state.noiseOffset += state.speed;
        for (int i = startLed; i <= startLed + numLeds - 1; i++) {
            // Layered noise for brightness variation
            uint8_t noiseVal1 = inoise8(i * state.scale, state.noiseOffset * (startLed + numLeds - 1 - i + 1), state.z);
            uint8_t noiseVal2 = inoise8(i * state.scale * 2, state.noiseOffset * 2, state.z * 2);

            uint8_t brightness = map(noiseVal1, 0, 255, 64, 255);
            brightness = (brightness + map(noiseVal2, 0, 255, -64, 64)) / 2;

            // Moving twinkles
            uint8_t twinkleProbability = inoise8(i * state.scale * 4, state.noiseOffset * 4, state.z * 4);
            if (twinkleProbability > 220) {  // Twinkle threshold
                brightness = 255;
            }
            // Blend colors (and convert to HSV)
            CRGB blendedRgb = blend(state.color1, state.color2, noiseVal1);
            CHSV blendedHsv = rgb2hsv_approximate(blendedRgb); // Convert to HSV
            leds[i] = CHSV(blendedHsv.hue, 255, (uint8_t)(brightness * intensity));
        }
        state.lastColorUpdate = currentTime;
    }
}

void SystemState::water(int startLed, int numLeds, CRGB color, float intensity) {
    struct WaterState {
         unsigned long lastColorUpdate = 0;
        uint16_t noiseOffset = 0;
        uint8_t z = 0;
        uint8_t speed = 2;
        uint8_t scale = 5;
        CHSV color1;
        CHSV color2;
    };
    static WaterState state;
    unsigned long currentTime = millis();
    if (currentTime - state.lastColorUpdate > 40)
    {
        state.noiseOffset += state.speed;
        for (int j = startLed; j <= startLed + numLeds - 1; j++) {
            // Layered noise for brightness variation
            uint8_t noiseVal1 = inoise8(j * state.scale, state.noiseOffset * (startLed + numLeds - 1 - j + 1), state.z);
            uint8_t noiseVal2 = inoise8(j * state.scale * 1, state.noiseOffset * 1, state.z * 1);
            
            uint8_t brightness = map(noiseVal1, 0, 255, 64, 255);
            brightness = (brightness + map(noiseVal2, 0, 255, -64, 64)) / 1.5;

                // Blend colors (and convert to HSV)
            CRGB blendedRgb = blend(state.color1, state.color2, noiseVal1);
            CHSV blendedHsv = rgb2hsv_approximate(blendedRgb); // Convert to HSV

            leds[j] = CHSV(blendedHsv.hue, 255, (uint8_t)(brightness * intensity));
        }
        state.lastColorUpdate = currentTime;
    }
    if(state.color1.hue == 0)
     {
         state.color1 = getHsvColor(color);
        state.color2 = getHsvColor(color);
    }
}


void SystemState::ruin(int startLed, int numLeds, float intensity) {
    struct RuinState {
         unsigned long lastColorUpdate = 0;
        uint16_t noiseOffset = 1.1f;
        uint8_t z = 0;
        uint8_t speed = 2;
        uint8_t scale = 5;
        CHSV color1 = CHSV(0, 255, 255);
        CHSV color2 = CHSV(0, 255, 255);
    };
    static RuinState state;
   unsigned long currentTime = millis();
    if(currentTime - state.lastColorUpdate > 60) {
        state.noiseOffset += state.speed;
        for (int j = startLed; j <= startLed + numLeds - 1; j++) {
            // Layered noise for brightness variation
             uint8_t noiseVal1 = inoise8(j * state.scale, state.noiseOffset * (startLed + numLeds - 1 - j + 1), state.z);
             uint8_t noiseVal2 = inoise8(j * state.scale * 1.5, state.noiseOffset * 1.5, state.z * 1.1);

            uint8_t brightness = map(noiseVal1, 0, 255, 64, 255);
            brightness = (brightness + map(noiseVal2, 0, 255, -160, 64)) / 1.025;

             // Blend colors (and convert to HSV)
             CRGB blendedRgb = blend(state.color1, state.color2, noiseVal1);  // Blend in RGB
            CHSV blendedHsv = rgb2hsv_approximate(blendedRgb); // Convert to HSV

             leds[j] = CHSV(blendedHsv.hue, 255, (uint8_t)(brightness * intensity));
          }
       state.lastColorUpdate = currentTime;
    }
}

void SystemState::updateButtonState(const char* buttonName, bool isPressed) {
    if (buttonStateMap.count(buttonName)) {
         buttonStateMap[buttonName].isPressed = isPressed;
    }
}