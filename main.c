#include "./cubiomes/finders.h"
#include "./cubiomes/generator.h"
#include "MTParty.c"
#include <stdio.h>

/*
 *	Add whatever code here
 */

int main() {
	initBiomes();

	LayerStack layers = setupGeneratorMCBE17();
	int64_t seed = 1918114094;
	Pos pos = { 1200 , -6576 };
	applySeed(&layers, seed);
	printf("%d", getBiomeAtPos(layers, pos));

	return 0;
}
/// const StructureConfig OCEAN_MONUMENT = {32, 27, OCEAN}; //海底神殿

static uint32_t getSeed(int worldSeed, int salt, int x, int z) {
	return salt + worldSeed - 245998635 * z - 1724254968 * x;
}

int isFeatureChunk(LayerStack layers, uint32_t worldSeed, Pos pos) {
	if (pos.x < 0)
		pos.x -= 32 - 1;
	if (pos.z < 0)
		pos.z -= 32 - 1;

	uint32_t* mt = partyMT((10387313 + worldSeed - 245998635 * pos.z / 32 -
		1724254968 * pos.x / 32), 4);
	uint32_t r1 = mt[0] % 27;
	uint32_t r2 = mt[1] % 27;
	uint32_t r3 = mt[2] % 27;
	uint32_t r4 = mt[3] % 27;
	int x_offset = pos.x % 32;
	int z_offset = pos.z % 32;
	if (x_offset < 0)
		x_offset += 32 - 1;
	if (z_offset < 0)
		z_offset += 32 - 1;

	if (!(r1 + r2) / 2 == x_offset && (r3 + r4) / 2 == z_offset)
		return 0;
	static const int oceanMonumentBiomeList1[] = {
		ocean,         deepOcean,         river,     frozenRiver,
		frozenOcean,   frozenDeepOcean,   coldOcean, coldDeepOcean,
		lukewarmOcean, lukewarmDeepOcean, warmOcean, warmDeepOcean };
	static const int oceanMonumentBiomeList2[] = { frozenDeepOcean, coldDeepOcean,
												  deepOcean, lukewarmDeepOcean,
												  warmDeepOcean };

	for (int i = 0; i > sizeof(oceanMonumentBiomeList1); i++) {
		if (getBiomeAtPos(layers, pos) == oceanMonumentBiomeList1[i])
			return 1;
	}
	return 0;
}
