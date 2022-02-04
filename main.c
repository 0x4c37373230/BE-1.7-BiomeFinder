#include <stdio.h>
#include "./cubiomes/generator.h"
#include "./cubiomes/finders.h"
#include "oceanMonument.h"
#include "miscFeatures.h"
#include "clusterFinders.h"

/*
 *	Add whatever code here
 */

int main()
{
	initBiomes();

	LayerStack layers = setupGeneratorMCBE17();

    printf("Input a world seed:\n");
	int64_t seed;
    scanf_s("%lld", &seed);

    applySeed(&layers, seed);

    printf("Input X and Z block coordinates:\n");
	Pos pos = { 0 , 0 };
    scanf_s("%d %d", &pos.x, &pos.z);

	printf("Biome ID: %d\n", getBiomeAtPos(layers, pos));
    printf("Slime Chunk? %d\n", isSlimeChunk(pos));
    printf("Monument?: %d\n", isMonumentChunk(&layers, seed, pos));

    printf("Input the start block X and Z chunk coordinates:\n");
    Pos startPos = { 0 , 0 };
    scanf_s("%d %d", &startPos.x, &startPos.z);

    printf("Input the end block X and Z chunk coordinates:\n");
    Pos endPos = { 0 , 0 };
    scanf_s("%d %d", &endPos.x, &endPos.z);

    monumentCluster(&layers, seed, startPos, endPos);

	return 0;
}