#include "terrain_configs.h"
#include "button_mapping.h"

#define DEFAULT_COLOR CRGB::Black

// --- Terrain Configurations ---
EffectInstance torchCampfire1 = {1, "YELLOW1", 0, 1, CRGB::Gold, -1};      // Torch 1 (1 LED)


EffectInstance terrainCampfire[] = {torchCampfire1};

TerrainConfig terrains[] = {
    {terrainCampfire, sizeof(terrainCampfire) / sizeof(terrainCampfire[0])},
};

int numTerrains = sizeof(terrains) / sizeof(terrains[0]);