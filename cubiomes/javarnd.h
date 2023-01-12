#ifndef JAVARND_H_
#define JAVARND_H_

#include <stdint.h>

//Java random 
static inline void setSeed(int64_t *seed) {
  *seed = (*seed ^ 0x5deece66d) & ((1LL << 48) - 1);
}

static inline int next(int64_t *seed, const int bits) {
  *seed = (*seed * 0x5deece66d + 0xb) & ((1LL << 48) - 1);
  return (int)(*seed >> (48 - bits));
}

static inline int nextInt(int64_t *seed, const int n) {
  int bits, val;
  const int m = n - 1;

  if ((m & n) == 0)
    return (int)((n * (long)next(seed, 31)) >> 31);

  do {
    bits = next(seed, 31);
    val = bits % n;
  } while (bits - val + m < 0);
  return val;
}

//double
static inline double nextDouble(int64_t *seed) {
  return (((int64_t)next(seed, 26) << 27) + next(seed, 27)) /
         (double)(1LL << 53);
}

#endif /* JAVARND_H_ */
