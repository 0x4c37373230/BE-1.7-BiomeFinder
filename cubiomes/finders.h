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
  // Moving Structures
  //==============================================================================

  /* Transposes a base seed such that structures are moved by the specified region
   * vector, (regX, regZ).
   */
static inline int64_t moveStructure(const int64_t baseSeed,
	const int regX, const int regZ) {
	return (baseSeed - regX * 341873128712 - regZ * 132897987541) & 0xffffffffffff;
}


//==============================================================================
// Saving & Loading Seeds
//==============================================================================

/* Loads a list of seeds from a file. The seeds should be written as decimal
 * UFT-8 numbers separated by newlines.
 * @fnam: file path
 * @scnt: number of valid seeds found in the file, which is also the number of
 *        elements in the returned buffer
 *
 * Return a pointer to dynamically allocated seed list.
 */
int64_t* loadSavedSeeds(const char* fnam, int64_t* scnt);


//==============================================================================
// Checking Biomes & Biome Helper Functions
//==============================================================================

/* Returns the biome for the specified block position.
 * (Alternatives should be considered first in performance critical code.)
 */
int getBiomeAtPos(const LayerStack g, const Pos pos);

/* Finds a suitable pseudo-random location in the specified area.
 * This function is used to determine the positions of spawn and strongholds.
 * Warning: accurate, but slow!
 *
 * @mcversion        : Minecraft version (changed in: 1.7, 1.13)
 * @g                : generator layer stack
 * @cache            : biome buffer, set to NULL for temporary allocation
 * @centreX, centreZ : origin for the search
 * @range            : square 'radius' of the search
 * @isValid          : boolean array of valid biome ids (size = 256)
 * @seed             : seed used for the RNG
 *                     (initialise RNG using setSeed(&seed))
 * @passes           : number of valid biomes passed, set to NULL to ignore this
 */
Pos findBiomePosition(
	const int           mcversion,
	const LayerStack    g,
	int* cache,
	const int           centerX,
	const int           centerZ,
	const int           range,
	const int* isValid,
	int64_t* seed,
	int* passes
);

/* Determines if the given area contains only biomes specified by 'biomeList'.
 * This function is used to determine the positions of villages, ocean monuments
 * and mansions.
 * Warning: accurate, but slow!
 *
 * @g          : generator layer stack
 * @cache      : biome buffer, set to NULL for temporary allocation
 * @posX, posZ : centre for the check
 * @radius     : 'radius' of the check area
 * @isValid    : boolean array of valid biome ids (size = 256)
 */
int areBiomesViable(
	const LayerStack    g,
	int* cache,
	const int           posX,
	const int           posZ,
	const int           radius,
	const int* isValid
);

/* Finds the smallest radius (by square around the origin) at which all the
 * specified biomes are present. The input map is assumed to be a square of
 * side length 'sideLen'.
 *
 * @map             : square biome map to be tested
 * @sideLen         : side length of the square map (should be 2*radius+1)
 * @biomes          : list of biomes to check for
 * @bnum            : length of 'biomes'
 * @ignoreMutations : flag to count mutated biomes as their original form
 *
 * Return the radius on the square map that covers all biomes in the list.
 * If the map does not contain all the specified biomes, -1 is returned.
 */
int getBiomeRadius(
	const int* map,
	const int       mapSide,
	const int* biomes,
	const int       bnum,
	const int       ignoreMutations);


//==============================================================================
// Seed Filters
//==============================================================================


/* Looks through the list of seeds in 'seedsIn' and copies those that have all
 * major overworld biomes in the specified area into 'seedsOut'. These checks
 * are done at a scale of 1:256.
 *
 * @g           : generator layer stack, (NOTE: seed will be modified)
 * @cache       : biome buffer, set to NULL for temporary allocation
 * @seedsIn     : list of seeds to check
 * @seedsOut    : output buffer for the candidate seeds
 * @seedCnt     : number of seeds in 'seedsIn'
 * @pX, pZ      : search starting coordinates (in 256 block units)
 * @sX, sZ      : size of the searching area (in 256 block units)
 *
 * Returns the number of seeds found.
 */
int64_t filterAllMajorBiomes(
	LayerStack* g,
	int* cache,
	const int64_t* seedsIn,
	int64_t* seedsOut,
	const int64_t       seedCnt,
	const int           pX,
	const int           pZ,
	const unsigned int  sX,
	const unsigned int  sZ
);

/* Creates a biome filter configuration from a given list of biomes.
 */
BiomeFilter setupBiomeFilter(const int* biomeList, int listLen);

/* Tries to determine if the biomes configured in the filter will generate in
 * this seed within the specified area. The smallest layer scale checked is
 * given by 'minscale'. Lowering this value terminate the search earlier and
 * yield more false positives.
 */
int64_t checkForBiomes(
	LayerStack* g,
	int* cache,
	const int64_t       seed,
	const int           blockX,
	const int           blockZ,
	const unsigned int  width,
	const unsigned int  height,
	const BiomeFilter   filter,
	const int           minscale);


#endif /* FINDERS_H_ */