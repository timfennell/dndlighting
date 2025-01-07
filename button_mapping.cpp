#include "button_mapping.h"
#include <stdint.h>
#include <map>

std::map<const char*, int> buttonPinMap = {
    {"YELLOW1", 0}, {"YELLOW2", 1}, {"YELLOW3", 2}, {"YELLOW4", 3},
    {"RED1", 4}, {"RED2", 5}, {"RED3", 6}, {"RED4", 7},
    {"BLUE1", 0}, {"BLUE2", 1}, {"BLUE3", 2}, {"BLUE4", 3},
    {"GREEN1", 8}, {"GREEN2", 9}, {"GREEN3", 10}, {"GREEN4", 11},
    {"WHITE1", 12}, {"WHITE2", 13}, {"WHITE3", 14}, {"WHITE4", 15},
    {"BLACK1", 4}, {"BLACK2", 5}, {"BLACK3", 6}, {"BLACK4", 7}
};

std::map<const char*, Button> buttonStateMap;

std::map<const char*, DeviceType> buttonDeviceType = {
    {"YELLOW1", DeviceType::Arduino}, {"YELLOW2", DeviceType::Arduino}, {"YELLOW3", DeviceType::Arduino}, {"YELLOW4", DeviceType::Arduino},
    {"RED1", DeviceType::Arduino}, {"RED2", DeviceType::Arduino}, {"RED3", DeviceType::Arduino}, {"RED4", DeviceType::Arduino},
    {"BLUE1", DeviceType::MCP23X17}, {"BLUE2", DeviceType::MCP23X17}, {"BLUE3", DeviceType::MCP23X17}, {"BLUE4", DeviceType::MCP23X17},
    {"GREEN1", DeviceType::MCP23X17}, {"GREEN2", DeviceType::MCP23X17}, {"GREEN3", DeviceType::MCP23X17}, {"GREEN4", DeviceType::MCP23X17},
    {"WHITE1", DeviceType::MCP23X17}, {"WHITE2", DeviceType::MCP23X17}, {"WHITE3", DeviceType::MCP23X17}, {"WHITE4", DeviceType::MCP23X17},
    {"BLACK1", DeviceType::MCP23X17}, {"BLACK2", DeviceType::MCP23X17}, {"BLACK3", DeviceType::MCP23X17}, {"BLACK4", DeviceType::MCP23X17}
};

const int numButtons = buttonPinMap.size();