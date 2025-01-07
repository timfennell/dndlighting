#include <FastLED.h>
#include <Wire.h>
#include <Adafruit_MCP23X17.h>
#include "terrain_configs.h"
#include "button_mapping.h"
#include "SystemState.h"
#include <map>

#define DATA_PIN 16
#define TERRAIN_INDICATOR_PIN 23
#define TERRAIN_SELECT_PIN 6

Adafruit_MCP23X17 mcp;
CRGB leds[SystemState::MAX_LEDS + 8];
SystemState* systemState;

void setup() {
    Serial.begin(115200);
     Serial.print("FastLED Init, using data pin: ");
     Serial.println(DATA_PIN);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, SystemState::MAX_LEDS + 8);

    FastLED.setBrightness(50);
    FastLED.clear();
    FastLED.show();

    Wire.begin();
    mcp.begin_I2C();

    for (int i = 0; i < 16; i++) {
        mcp.pinMode(i, INPUT_PULLUP);
    }

    pinMode(TERRAIN_SELECT_PIN, INPUT_PULLUP);
    for (const auto& [key, val] : buttonPinMap) {
        if (buttonDeviceType.at(key) == DeviceType::Arduino) {
            pinMode(val, INPUT_PULLUP);
        }
    }

     systemState = new SystemState(leds, buttonStateMap, terrains, numTerrains);
}

void loop() {
    unsigned long startTime = millis();

    if (digitalRead(TERRAIN_SELECT_PIN) == LOW) {
        systemState->nextTerrain();
        delay(200); // Debounce
    }
    // Handle latching button presses
     for (auto& [key, button] : buttonStateMap) {
        int pinReading;
        if (buttonDeviceType[key] == DeviceType::Arduino) {
            pinReading = digitalRead(buttonPinMap.at(key));
        } else {
            pinReading = mcp.digitalRead(buttonPinMap.at(key));
        }
         bool currentlyPressed = (pinReading == LOW);

        if (currentlyPressed != button.isPressed) {
          buttonStateMap[key].isPressed = currentlyPressed;
        //  systemState->buttonStateMap[key].isPressed = currentlyPressed;
           Serial.print("Button: ");
          Serial.print(key);
         Serial.print(" State: ");
          Serial.println((currentlyPressed) ? "Pressed" : "Released");
        }
    }
    systemState->update();
    FastLED.show();


    unsigned long endTime = millis();
    Serial.print("Loop Time: ");
    Serial.print(endTime - startTime);
    Serial.println("ms");
}