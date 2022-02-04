#include "simDistance.h"

bool sim6(LayerStack* layers, uint32_t seed, Pos originPos, bool (*feature)(LayerStack*, uint32_t, Pos))
{
    bool result = false;

    for (int i = -5; i <= 5; ++i)
    {
        int w = abs(i % 5);

        for (int j = -w; j <= w; ++j)
        {
            if (feature(layers, seed, (Pos) { originPos.x + i, originPos.z + j }))
                result = true;
        }
    }

    return result;
}

