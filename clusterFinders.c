#include "clusterFinders.h"

void monumentCluster(LayerStack* layers, uint32_t worldSeed, Pos startPos, Pos endPos)
{
    bool found = false;
    for (int z = startPos.z; z <= endPos.z; z++)
    {
        for (int x = startPos.x; x <= endPos.x; x++)
        {
            if (isMonumentChunk(layers, worldSeed, (Pos){x * 16, z * 16}))
            {
                short num = sim6(layers, worldSeed, (Pos) { x, z }, isMonumentChunk);
                if (num > 0)
                {
                    printf("Found a cluster at: %d, %d with number: %i\n", x, z, num);
                    found = true;
                }
            }
        }
    }

    if (!found)
        printf("No clusters found");
}