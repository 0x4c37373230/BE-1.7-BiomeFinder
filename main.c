#include <stdio.h>
#include "./cubiomes/generator.h"
#include "./cubiomes/finders.h"


/*
*	Add whatever code here
*/

int main() {
	initBiomes();
	LayerStack layers = setupGeneratorMCBE17();
	int64_t seed = 1918114094;
	Pos pos = { 1200 , -6576 };
	applySeed(&layers, seed);
	int biomeId = getBiomeAtPos(layers, pos);
	printf("%d", biomeId);
	return 0;
}
