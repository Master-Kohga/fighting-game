#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include "vector.h"

#define NUMBEROFPLAYERTYPES 1

typedef struct keynode {
  SDL_Keycode key;
  struct keynode *next;
} keynode;

typedef struct {
  int type;
  vec pos, vel, acc;
  keynode *keys;
} player;


void renderplayer(player *, SDL_Renderer *);
void initialiseplayer(player *, int);
void updateplayer(player *);
void keydown(player *, SDL_Keycode);
void keyup(player *, SDL_Keycode);
#endif
