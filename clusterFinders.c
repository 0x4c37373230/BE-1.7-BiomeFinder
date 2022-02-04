#include "clusterFinders.h"

void monumentCluster(LayerStack* layers, uint32_t worldSeed, Pos startPos, Pos endPos)
{
    bool found = false;
    int z = startPos.z;
    int previousZ = z;

    while (z <= endPos.z)
    {
        for (int x = startPos.x; x <= endPos.x; x++)
        {
            if (previousZ != z)
                previousZ = z;

            if (isMonumentChunk(layers, worldSeed, (Pos){x, z}))
            {
                if (sim6(layers, worldSeed, (Pos){x, z}, isMonumentChunk))
                {
                    printf("Found a cluster at: %d, %d", x, z);
                    found = true;
                }
            }
        }
        ++z;
    }

    if (!found)
        printf("No clusters found");
}