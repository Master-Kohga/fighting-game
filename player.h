#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include "vector.h"
#include "attack.h"
#include "key.h"

#define NUMBEROFPLAYERTYPES 1
#define NUMBEROFATTACKS 5
#define KEYBUFSIZE 5
#define IDLE -1

typedef struct {
  int type, state, frame, health;
  vec pos, vel, acc;
  keynode *keys;
  keynode keybuf[KEYBUFSIZE];
} player;

void renderplayer(player *, SDL_Renderer *);
void initialiseplayer(player *, int);
void updateplayer(player *, int , int);
void pkeydown(player *, SDL_Keycode, unsigned long);
void pkeyup(player *, SDL_Keycode, unsigned long);
#endif
