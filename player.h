#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include "vector.h"

typedef struct {
  int type;
  vec pos, vel, acc;
} player;

void initialiseplayer(player *, int);
void updateplayer(player *, SDL_Keycode);
#endif
