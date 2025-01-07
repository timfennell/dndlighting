#ifndef SYSTEMSTATE_H
#define SYSTEMSTATE_H

#include <FastLED.h>
#include "terrain_configs.h"
#include "button_mapping.h"
#include <map>

class SystemState {
public:
    static const int MAX_LEDS = 300;
    static const int TERRAIN_INDICATOR_PIN = 23;
    static const CRGB DEFAULT_COLOR;

    SystemState(CRGB* leds, std::map<const char*, Button>& buttonStateMap, TerrainConfig* terrains, int numTerrains);

    void update();
    void nextTerrain();
       std::map<const char*, Button>& getButtonStateMap();

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

    void firePit(int startLed, CRGB color, float intensity);
    void torch(int startLed, CRGB color, float intensity);
    void altar(int startLed, int numLeds, CRGB color, float intensity);
    void waterfall(int startLed, int numLeds, CRGB color, float intensity);
    void water(int startLed, int numLeds, CRGB color, float intensity);
    void ruin(int startLed, int numLeds, CRGB color, float intensity);
};

#endif