//terrain_configs.h

#ifndef TERRAIN_CONFIGS_H
#define TERRAIN_CONFIGS_H

#include <stdint.h>
#include "EffectInstance.h"

struct TerrainConfig {
    EffectInstance* effects;
    int numEffects;
};

extern TerrainConfig terrains[];
extern int numTerrains;

#endif