#ifndef OCEANMONUMENT_H
#define OCEANMONUMENT_H

static uint32_t getSeed(int worldSeed, int salt, int x, int z);

int isFeatureChunk(LayerStack layers, uint32_t worldSeed, Pos pos);

#endif
