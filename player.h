#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include "vector.h"
#include "attack.h"
#include "key.h"

#define NUMBEROFPLAYERTYPES 1
#define NUMBEROFATTACKS 5
#define NUMBEROFANIMATIONS 1
#define KEYBUFSIZE 5
#define IDLE -1

typedef struct {
  int type, state, frame, health, direction;
  vec pos, vel, acc;
  keynode *keys;
  keynode keybuf[KEYBUFSIZE];
} player;

void loadanimations(int, SDL_Renderer *, char *);
void renderplayer(player *, SDL_Renderer *);
void updateplayer(player *, int , int);
void pkeydown(player *, SDL_Keycode, unsigned long);
void pkeyup(player *, SDL_Keycode, unsigned long);
#endif
