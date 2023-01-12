#ifndef OCEANMONUMENT_H
#define OCEANMONUMENT_H

#include <stdbool.h>
#include "cubiomes/generator.h"
#include "cubiomes/finders.h"

bool isMonumentChunk(LayerStack* layers, uint32_t worldSeed, Pos pos);

#endif
