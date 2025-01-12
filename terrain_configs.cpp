//terrain_configs.cpp

#include "terrain_configs.h"
#include "button_mapping.h"

#define DEFAULT_COLOR CRGB::Black

// --- Terrain Configurations ---

// --- Campfire (Terrain 0) ---
// Updated to include all effects and buttons
EffectInstance firePitCampfire = {0, "RED1", 0, 4, CRGB::Red, -1};         // Fire Pit (4 LEDs)
EffectInstance torchCampfire1 = {1, "YELLOW1", 4, 1, CRGB::Gold, -1};      // Torch 1 (1 LED)
EffectInstance torchCampfire2 = {1, "YELLOW2", 5, 1, CRGB::Gold, -1};      // Torch 2 (1 LED)
EffectInstance torchCampfire3 = {1, "YELLOW3", 6, 1, CRGB::Gold, -1};      // Torch 3 (1 LED)
EffectInstance torchCampfire4 = {1, "YELLOW4", 7, 1, CRGB::Gold, -1};      // Torch 4 (1 LED)
EffectInstance altarCampfire = {2, "GREEN1", 8, 2, CRGB::Green, -1};       // Altar (2 LEDs)
EffectInstance waterfallCampfire = {3, "BLUE1", 10, 5, CRGB::Aqua, -1};   // Waterfall (5 LEDs)
EffectInstance waterCampfire = {4, "BLUE2", 15, 4, CRGB::Aqua, -1};       // Water (4 LEDs)
EffectInstance ruinCampfire = {5, "WHITE1", 19, 3, CRGB::Gray, -1};        // Ruin (3 LEDs)

//Example using all MCP23017 Buttons:
EffectInstance ruinCampfire2 = {5, "WHITE2", 22, 3, CRGB::Gray, -1};        // Ruin (3 LEDs)
EffectInstance ruinCampfire3 = {5, "WHITE3", 25, 3, CRGB::Gray, -1};        // Ruin (3 LEDs)
EffectInstance ruinCampfire4 = {5, "WHITE4", 28, 3, CRGB::Gray, -1};        // Ruin (3 LEDs)

EffectInstance firePitCampfire2 = {0, "RED2", 31, 4, CRGB::Red, -1};         // Fire Pit (4 LEDs)
EffectInstance firePitCampfire3 = {0, "RED3", 35, 4, CRGB::Red, -1};         // Fire Pit (4 LEDs)
EffectInstance firePitCampfire4 = {0, "RED4", 39, 4, CRGB::Red, -1};         // Fire Pit (4 LEDs)

EffectInstance altarCampfire2 = {2, "GREEN2", 43, 2, CRGB::Green, -1};       // Altar (2 LEDs)
EffectInstance altarCampfire3 = {2, "GREEN3", 45, 2, CRGB::Green, -1};       // Altar (2 LEDs)
EffectInstance altarCampfire4 = {2, "GREEN4", 47, 2, CRGB::Green, -1};       // Altar (2 LEDs)

EffectInstance waterfallCampfire2 = {3, "BLUE3", 49, 5, CRGB::Aqua, -1};   // Waterfall (5 LEDs)
EffectInstance waterfallCampfire3 = {3, "BLUE4", 54, 5, CRGB::Aqua, -1};   // Waterfall (5 LEDs)

// --- Terrain Configuration Array ---
EffectInstance terrainCampfire[] = {
    firePitCampfire, torchCampfire1, torchCampfire2, torchCampfire3, torchCampfire4,
    altarCampfire, waterfallCampfire, waterCampfire, ruinCampfire,
    ruinCampfire2, ruinCampfire3, ruinCampfire4,
    firePitCampfire2, firePitCampfire3, firePitCampfire4,
    altarCampfire2, altarCampfire3, altarCampfire4,
    waterfallCampfire2, waterfallCampfire3
};
// --- Cave ---
EffectInstance torchCaveEast = {1, "YELLOW2", 11, 1, CRGB::Red, -1};
EffectInstance ruinCaveSmall = {5, "WHITE1", 31, 3, CRGB::Gray, -1};
EffectInstance terrainCave[] = {torchCaveEast, ruinCaveSmall};

// --- Cliff ---
EffectInstance waterfallCliff = {3, "BLUE1", 26, 5, CRGB::Aqua, -1};
EffectInstance waterLake = {4, "BLUE2", 22, 4, CRGB::Aqua, -1};

EffectInstance terrainCliff[] = {waterfallCliff, waterLake};

// --- Forest ---
EffectInstance altarForestGood = {2, "GREEN1", 9, 2, CRGB::Green, -1};
EffectInstance torchForestWest = {1, "YELLOW4", 21, 1, DEFAULT_COLOR, -1};

EffectInstance terrainForest[] = {altarForestGood, torchForestWest};

// --- Desert ---
EffectInstance torchDesertSouth = {1, "YELLOW3", 20, 1, CRGB::Gold, -1};
EffectInstance firePitDesert = {0, "RED2", 5, 4, CRGB::Orange, -1};

EffectInstance terrainDesert[] = {torchDesertSouth, firePitDesert};

// --- Town ---
EffectInstance torchTownNorth = {1, "YELLOW1", 4, 1, DEFAULT_COLOR, -1};
EffectInstance torchTownEast = {1, "YELLOW2", 11, 1, DEFAULT_COLOR, -1};
EffectInstance torchTownSouth = {1, "YELLOW3", 20, 1, DEFAULT_COLOR, -1};

EffectInstance terrainTown[] = {torchTownNorth, torchTownEast, torchTownSouth};

// --- Dungeon ---
EffectInstance ruinDungeonLarge = {5, "BLACK1", 34, 5, CRGB::DarkGray, -1};
EffectInstance torchDungeonNorth = {1, "YELLOW1", 4, 1, CRGB::DeepSkyBlue, -1};

EffectInstance terrainDungeon[] = {ruinDungeonLarge, torchDungeonNorth};


TerrainConfig terrains[] = {
    {terrainCampfire, sizeof(terrainCampfire) / sizeof(terrainCampfire[0])},
    {terrainCave, sizeof(terrainCave) / sizeof(terrainCave[0])},
    {terrainCliff, sizeof(terrainCliff) / sizeof(terrainCliff[0])},
    {terrainForest, sizeof(terrainForest) / sizeof(terrainForest[0])},
    {terrainDesert, sizeof(terrainDesert) / sizeof(terrainDesert[0])},
    {terrainTown, sizeof(terrainTown) / sizeof(terrainTown[0])},
    {terrainDungeon, sizeof(terrainDungeon) / sizeof(terrainDungeon[0])}
};

// Number of terrains (automatically calculated)
int numTerrains = sizeof(terrains) / sizeof(terrains[0]);