#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include "vector.h"

#define NUMBEROFPLAYERTYPES 1
#define KEYBUFSIZE 5

typedef struct keynode {
  SDL_Keycode key;
  unsigned long milliseconds;
  struct keynode *next;
} keynode;

typedef struct {
  int type;
  vec pos, vel, acc;
  keynode *keys;
  keynode keybuf[KEYBUFSIZE];
} player;


void renderplayer(player *, SDL_Renderer *);
void initialiseplayer(player *, int);
void updateplayer(player *);
void keydown(player *, SDL_Keycode, unsigned long);
void keyup(player *, SDL_Keycode, unsigned long);
#endif
