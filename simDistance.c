#include "simDistance.h"

short sim6(LayerStack* layers, uint32_t seed, Pos originPos, bool (*feature)(LayerStack*, uint32_t, Pos))
{
    short result = 0;

    for (int i = -5; i <= 5; ++i)
    {
        int w = abs(i % 5);

        for (int j = -w; j <= w; ++j)
        {
            if (feature(layers, seed, (Pos){ (originPos.x + i) * 16, (originPos.z + j) * 16 }))
            {
                result++;
            }
        }
    }

    return result;
}

