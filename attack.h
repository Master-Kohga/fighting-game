#ifndef _ATTACK_
#define _ATTACK_
#include "vector.h"

typedef struct {
  vec pos, hitbox;
  int startframe, endframe, waitframe;
  int damage;
} attack;

int rectanglecollide(vec, vec, vec, vec);

#endif
