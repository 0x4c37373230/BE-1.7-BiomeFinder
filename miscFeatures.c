#include <stdbool.h>
#include "partyMT.h"
#include "cubiomes/finders.h"

bool isSlimeChunk(Pos chunk)
{
    uint32_t* mt = partyMT((chunk.x * 0x1f1f1f1f) ^ chunk.z, 1);
    return mt[0] % 10 == 0;
}
