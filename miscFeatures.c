#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include "partyMT.h"
#include "cubiomes/finders.h"

bool isSlimeChunk(Pos chunk)
{
    uint32_t* mt = partyMT(((int)(floor(chunk.x / 16)) * 0x1f1f1f1f) ^ (int)(floor(chunk.z / 16)), 1);
    bool result = mt[0] % 10 == 0;

    free(mt);
    return result;
}
