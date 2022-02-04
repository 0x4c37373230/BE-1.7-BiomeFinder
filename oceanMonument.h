#ifndef OCEANMONUMENT_H
#define OCEANMONUMENT_H

#include <stdbool.h>
#include <corecrt_malloc.h>
#include "cubiomes/generator.h"
#include "cubiomes/finders.h"

bool isMonumentChunk(LayerStack* layers, uint32_t worldSeed, Pos pos);

#endif
