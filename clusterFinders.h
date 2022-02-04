#ifndef CLUSTERFINDERS_H
#define CLUSTERFINDERS_H

#include <stdbool.h>
#include "cubiomes/generator.h"
#include "cubiomes/finders.h"
#include "oceanMonument.h"
#include "simDistance.h"

void monumentCluster(LayerStack* layers, uint32_t worldSeed, Pos startPos, Pos endPos);

#endif
