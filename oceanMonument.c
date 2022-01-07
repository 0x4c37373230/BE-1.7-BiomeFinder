#include <stdint.h>
#include <stdbool.h>
#include "cubiomes/generator.h"
#include "cubiomes/finders.h"
#include "partyMT.h"

bool isMonumentChunk(LayerStack layers, uint32_t worldSeed, Pos pos)
{
    int biomeID = getBiomeAtPos(layers, pos);
    pos.x -= (pos.x < 0) ? 31 : 0;
    pos.z -= (pos.z < 0) ? 31 : 0;
    uint32_t* mt = partyMT((10387313 + worldSeed - 245998635 * pos.z / 32 - 1724254968 * pos.x / 32), 4);
    int xOffset = pos.x % 32;
    int zOffset = pos.z % 32;
    xOffset += (xOffset < 0) ? 31 : 0;
    zOffset += (zOffset < 0) ? 31 : 0;
    bool flag = (mt[0] % 27 + mt[1] % 27) / 2 != xOffset && (mt[2] % 27 + mt[3] % 27) / 2 != zOffset;
    static const int oceanMonumentBiomeList1[] = { 0, 7, 10, 11, 24, 40, 41, 42, 43, 44, 45, 46 };
    if(!flag) { return 0; }
    for (int i = 0; i < 12; ++i)
    {
        if (biomeID == oceanMonumentBiomeList1[i])
            return 1;
    }

    return 0;
}
