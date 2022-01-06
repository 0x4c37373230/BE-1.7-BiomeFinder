#include <stdint.h>
#include "cubiomes/generator.h"
#include "cubiomes/finders.h"
#include "partyMT.h"

int isMonumentChunk(LayerStack layers, uint32_t worldSeed, Pos pos)
{
    Pos ogPos = pos;
    pos.x -= (pos.x < 0) ? 31 : 0;
    pos.z -= (pos.z < 0) ? 31 : 0;
    uint32_t* mt = partyMT((10387313 + worldSeed - 245998635 * pos.z / 32 - 1724254968 * pos.x / 32), 4);
    int xOffset = pos.x % 32;
    int zOffset = pos.z % 32;
    xOffset += (xOffset < 0) ? 31 : 0;
    zOffset += (zOffset < 0) ? 31 : 0;
    int flag = (mt[0] % 27 + mt[1] % 27) / 2 == xOffset && (mt[2] % 27 + mt[3] % 27) / 2 == zOffset;
    static const int oceanMonumentBiomeList1[] = { 0, 7, 10, 11, 24, 40, 41, 42, 43, 44, 45, 46 };
    int biomeId =getBiomeAtPos(layers, ogPos);

    for (int i = 0; i < 12; ++i)
    {
        if ((biomeId == oceanMonumentBiomeList1[i]) && flag)
            return 1;
    }

    return 0;
}
/*

// I had an idea while messing with stuff which I can't be asked to explain, and I thought this would work.
// It's unreliable sadly. I'll keep messing with this later (luke)

int isMonumentChunk2(LayerStack layers, uint32_t worldSeed, Pos pos)
{
    Pos ogPos = pos;
    static const int monumentBiomes[] = { 0, 7, 10, 11, 24, 40, 41, 42, 43, 44, 45, 46 };
    int biomeID = getBiomeAtPos(layers, ogPos);
    pos.x -= (pos.x < 0) ? 31 : 0;
    pos.z -= (pos.z < 0) ? 31 : 0;
    uint32_t* mt = partyMT((10387313 + worldSeed - 245998635L * (pos.z / 32) - 1724254968L * (pos.x / 32)), 4);
    int flag = ((mt[0] % 27 + mt[1] % 27) / 2) % 2 == 0 && ((mt[2] % 27 + mt[3] % 27) / 2) % 2 == 0;

    for (int i = 0; i < 12; ++i)
    {
        if (biomeID == monumentBiomes[i] && flag)
            return 1;
    }

    return 0;
}
*/