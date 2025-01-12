//button_mapping.cpp

#include "button_mapping.h"
#include <stdint.h>
#include <map>

std::map<const char*, int> buttonPinMap = {
    {"YELLOW1", 12}, {"YELLOW2", 11}, {"YELLOW3", 10}, {"YELLOW4", 9},
    {"RED1", 26}, {"RED2", 27}, {"RED3", 28}, {"RED4", 29},
    {"BLUE1", 0}, {"BLUE2", 1}, {"BLUE3", 2}, {"BLUE4", 3},
    {"GREEN1", 4}, {"GREEN2", 5}, {"GREEN3", 12}, {"GREEN4", 13},
    {"WHITE1", 6}, {"WHITE2", 7}, {"WHITE3", 14}, {"WHITE4", 15},
    {"BLACK1", 8}, {"BLACK2", 9}, {"BLACK3", 10}, {"BLACK4", 11}
};

std::map<const char*, Button> buttonStateMap = {
      {"YELLOW1", {false, "YELLOW1"}}, {"YELLOW2", {false, "YELLOW2"}}, {"YELLOW3", {false, "YELLOW3"}}, {"YELLOW4", {false, "YELLOW4"}},
      {"RED1", {false, "RED1"}}, {"RED2", {false, "RED2"}}, {"RED3", {false, "RED3"}}, {"RED4", {false, "RED4"}},
      {"BLUE1", {false, "BLUE1"}}, {"BLUE2", {false, "BLUE2"}}, {"BLUE3", {false, "BLUE3"}}, {"BLUE4", {false, "BLUE4"}},
      {"GREEN1", {false, "GREEN1"}}, {"GREEN2", {false, "GREEN2"}}, {"GREEN3", {false, "GREEN3"}}, {"GREEN4", {false, "GREEN4"}},
      {"WHITE1", {false, "WHITE1"}}, {"WHITE2", {false, "WHITE2"}}, {"WHITE3", {false, "WHITE3"}}, {"WHITE4", {false, "WHITE4"}},
      {"BLACK1", {false, "BLACK1"}}, {"BLACK2", {false, "BLACK2"}}, {"BLACK3", {false, "BLACK3"}}, {"BLACK4", {false, "BLACK4"}}
    };

std::map<const char*, DeviceType> buttonDeviceType = {
    {"YELLOW1", DeviceType::Arduino}, {"YELLOW2", DeviceType::Arduino}, {"YELLOW3", DeviceType::Arduino}, {"YELLOW4", DeviceType::Arduino},
    {"RED1", DeviceType::Arduino}, {"RED2", DeviceType::Arduino}, {"RED3", DeviceType::Arduino}, {"RED4", DeviceType::Arduino},
    {"BLUE1", DeviceType::MCP23X17}, {"BLUE2", DeviceType::MCP23X17}, {"BLUE3", DeviceType::MCP23X17}, {"BLUE4", DeviceType::MCP23X17},
    {"GREEN1", DeviceType::MCP23X17}, {"GREEN2", DeviceType::MCP23X17}, {"GREEN3", DeviceType::MCP23X17}, {"GREEN4", DeviceType::MCP23X17},
    {"WHITE1", DeviceType::MCP23X17}, {"WHITE2", DeviceType::MCP23X17}, {"WHITE3", DeviceType::MCP23X17}, {"WHITE4", DeviceType::MCP23X17},
    {"BLACK1", DeviceType::MCP23X17}, {"BLACK2", DeviceType::MCP23X17}, {"BLACK3", DeviceType::MCP23X17}, {"BLACK4", DeviceType::MCP23X17}
};

const int numButtons = buttonPinMap.size();