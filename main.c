#include <stdio.h>
#include "./cubiomes/generator.h"
#include "./cubiomes/finders.h"

int main()
{
    initBiomes();

    LayerStack layers = setupGeneratorMCBE17();
    int64_t seed = -395202839;
    Pos pos = { -260, -76 };

    applySeed(&layers, seed);

    int biomeId = getBiomeAtPos(layers, pos);

    printf("%d", biomeId);

    return 0;
}
