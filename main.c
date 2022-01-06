#include <stdio.h>
#include "./cubiomes/generator.h"
#include "./cubiomes/finders.h"
#include "oceanMonument.h"

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

    printf("Input X and Z block coordinates:\n");
	Pos pos = { 0 , 0 };
    scanf_s("%d %d", &pos.x, &pos.z);

	applySeed(&layers, seed);
	printf("Biome ID: %d\n", getBiomeAtPos(layers, pos));
    printf("Monument?: %d", isMonumentChunk(layers, seed, pos));

	return 0;
}