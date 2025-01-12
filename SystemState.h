#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <FastLED.h>
#include "terrain_configs.h"
#include "button_mapping.h"
#include <map>

class SystemState {
public:
    static const int MAX_LEDS = 300;
    static const CRGB DEFAULT_COLOR;
    
    SystemState(CRGB* leds, std::map<const char*, Button>& buttonStateMap, TerrainConfig* terrains, int numTerrains);

    void update();
    void nextTerrain();
    void updateButtonState(const char* buttonName, bool isPressed);
    const std::map<const char*, Button>& getButtonStateMap() const;


private:
    CRGB* leds;
    TerrainConfig* terrains;
    int numTerrains;
    int currentTerrain = 0;
    std::map<const char*, Button> buttonStateMap;
    bool getButtonState(const char* buttonName);
    DeviceType getDeviceType(const char* buttonName);
    void updateIndicatorLights();
    void runEffect(int effectIndex);
    CHSV getHsvColor(CRGB color);
    void clearLedsForTerrain(); // Added this declaration


   //Common Timings
    static const int FIRE_PIT_BUILDUP_DURATION_MS = 30000;
    static const int FIRE_PIT_FADE_DURATION_MS = 120000;
    static const int FIRE_PIT_STOKE_DURATION_MS = 60000;
    static const int FIRE_PIT_FADEOUT_DURATION_MS = 30000;
    static const int FIRE_PIT_EMBER_UPDATE_INTERVAL_MS = 50;
    static const int FIRE_PIT_SPARK_INTERVAL_MS = 2000;
    static const int COLOR_CHANGE_INTERVAL_MS = 5000;


     float smoothTransition(float startIntensity, float endIntensity, float progress);
     void firePit(int startLed, float intensity);
    void torch(int startLed, CRGB color, float intensity);
    void altar(int startLed, int numLeds, CRGB color, float intensity);
    void waterfall(int startLed, int numLeds, float intensity);
    void water(int startLed, int numLeds, CRGB color, float intensity);
    void ruin(int startLed, int numLeds, float intensity);

};

#endif