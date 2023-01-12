#ifndef SIMDISTANCE_H
#define SIMDISTANCE_H

#include <stdbool.h>
#include "cubiomes/generator.h"
#include "cubiomes/finders.h"

bool sim6(LayerStack* layers, uint32_t seed, Pos originPos, bool (*feature)(LayerStack*, uint32_t, Pos));

#endif
