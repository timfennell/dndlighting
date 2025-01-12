//button_mapping.h

#ifndef BUTTON_MAPPING_H
#define BUTTON_MAPPING_H
#include <stdint.h>
#include <map>

enum class DeviceType { Arduino, MCP23X17 };

struct Button {
    bool isPressed;
    const char* name;
};

extern std::map<const char*, int> buttonPinMap;
extern std::map<const char*, Button> buttonStateMap;
extern std::map<const char*, DeviceType> buttonDeviceType;

extern const int numButtons;

#endif