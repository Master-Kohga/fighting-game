#ifndef _ATTACK_
#define _ATTACK_
#include "vector.h"

#define MIN(A, B) (A > B ? B : A)
#define MAX(A, B) (A < B ? B : A)

typedef struct {
  vec pos, hitbox, pvel, ovel;
  int startframe, endframe, waitframe;
  int damage, endoncollision;
} attack;

int rectanglecollide(vec, vec, vec, vec);

#endif
