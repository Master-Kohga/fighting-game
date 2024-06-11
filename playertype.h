#ifndef _PLAYERTYPE_
#define _PLAYERTYPE_

#include "animation.h"
#include "vector.h"
#include "attack.h"

#define NUMBEROFPLAYERTYPES 1
#define NUMBEROFANIMATIONS 5
#define NUMBEROFATTACKS 5

typedef struct {
  float maxvel, accel, jumpheight;
  animation animations[NUMBEROFANIMATIONS];
  vec hitbox;
  vec animationhitbox;
  attack attacks[NUMBEROFATTACKS];
} playertype;

playertype getplayertype(int);
void loadanimations(int, SDL_Renderer *, char *);

#endif
