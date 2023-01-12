#include "finders.h"

#include <stdlib.h>

//==============================================================================
// Globals
//==============================================================================

Biome biomes[256];

//==============================================================================
// Checking Biomes & Biome Helper Functions
//==============================================================================

int getBiomeAtPos(const LayerStack g, const Pos pos) {
	int* map = allocCache(&g.layers[g.layerNum - 1], 1, 1);
	genArea(&g.layers[g.layerNum - 1], map, pos.x, pos.z, 1, 1);
	int biomeID = map[0];
	free(map);
	return biomeID;
}