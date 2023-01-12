#ifndef FINDERS_H_
#define FINDERS_H_

#include "generator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>

typedef HANDLE thread_id_t;

#else

typedef thread_id_t;

#endif

#define SEED_BASE_MAX (1LL << 48)
#define PI 3.141592653589793

#define LARGE_STRUCT 1
#define USE_POW2_RNG 2

//==============================================================================
// Biome Tables
//==============================================================================

static const int achievementBiomes_1_7[] =
{
		ocean, plains, desert, extremeHills, forest, taiga, swampland, river, /*hell, sky,*/ // 0-9
		/*frozenOcean,*/ frozenRiver, icePlains, iceMountains, mushroomIsland, mushroomIslandShore, beach, desertHills, forestHills, taigaHills,  // 10-19
		/*extremeHillsEdge,*/ jungle, jungleHills, jungleEdge, deepOcean, stoneBeach, coldBeach, birchForest, birchForestHills, roofedForest, // 20-29
		coldTaiga, coldTaigaHills, megaTaiga, megaTaigaHills, extremeHillsPlus, savanna, savannaPlateau, mesa, mesaPlateau_F, mesaPlateau // 30-39
};

STRUCT(Pos) {
	int x, z;
};

STRUCT(BiomeFilter) {
	// bitfield for required temperature categories, including special variants
	uint64_t tempCat;
	// bitfield for the required ocean types
	uint64_t oceansToFind;
	// bitfield of required biomes without modification bit
	uint64_t biomesToFind;
	// bitfield of required modified biomes
	uint64_t modifiedToFind;

	// check that there is a minimum of both special and normal temperatures
	int tempNormal, tempSpecial;
	// check for the temperatures specified by tempCnt (1:1024)
	int doTempCheck;
	// check for mushroom potential
	int requireMushroom;
	// combine a more detailed mushroom and temperature check (1:256)
	int doShroomAndTempCheck;
	// early check for 1.13 ocean types (1:256)
	int doOceanTypeCheck;
	//
	int doMajorBiomeCheck;
	// pre-generation biome checks in layer L_BIOME_256
	int checkBiomePotential;
	//
	int doScale4Check;
};

//==============================================================================
// Globals
//==============================================================================

extern Biome biomes[256];

/******************************** SEED FINDING *********************************
 *
 *  If we want to find rare seeds that meet multiple custom criteria then we
 *  should test each condition, starting with the one that is the cheapest
 *  to test for, while ruling out the most seeds.
 *
 *  Biome checks are quite expensive and should be applied late in the
 *  condition chain (to avoid as many unnecessary checks as possible).
 *  Fortunately we can often rule out vast amounts of seeds before hand.
 */

 /*************************** Quad-Structure Checks *****************************
  *
  *  Several tricks can be applied to determine candidate seeds for quad
  *  temples (inc. witch huts).
  *
  *  Minecraft uses a 48-bit pseudo random number generator (PRNG) to determine
  *  the position of it's structures. The remaining top 16 bits do not influence
  *  the structure positioning. Additionally the position of most structures in a
  *  world can be translated by applying the following transformation to the
  *  seed:
  *
  *  seed2 = seed1 - dregX * 341873128712 - dregZ * 132897987541;
  *
  *  Here seed1 and seed2 have the same structure positioning, but moved by a
  *  region offset of (dregX,dregZ). [a region is 32x32 chunks].
  *
  *  For a quad-structure, we mainly care about relative positioning, so we can
  *  get away with just checking the regions near the origin: (0,0),(0,1),(1,0)
  *  and (1,1) and then move the structures to the desired position.
  *
  *  Lastly we can recognise a that the transformation of relative region-
  *  coordinates imposes some restrictions in the PRNG, such that
  *  perfect-position quad-structure-seeds can only have certain values for the
  *  lower 16-bits in their seeds.
  *
  *
  ** The Set of all Quad-Witch-Huts
  *
  *  These conditions only leave 32 free bits which can comfortably be brute-
  *  forced to get the entire set of quad-structure candidates. Each of the seeds
  *  found this way describes an entire set of possible quad-witch-huts (with
  *  degrees of freedom for region-transposition, and the top 16-bit bits).
  *
  */

//==============================================================================
// Checking Biomes & Biome Helper Functions
//==============================================================================

/* Returns the biome for the specified block position.
 * (Alternatives should be considered first in performance critical code.)
 */
int getBiomeAtPos(const LayerStack g, const Pos pos);

#endif /* FINDERS_H_ */