#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include "vector.h"

#define NUMBEROFPLAYERTYPES 1
#define NUMBEROFATTACKS 5
#define KEYBUFSIZE 5
#define IDLE -1

typedef struct keynode {
  SDL_Keycode key;
  unsigned long milliseconds;
  struct keynode *next;
} keynode;

typedef struct {
  int type, state, frame, health;
  vec pos, vel, acc;
  keynode *keys;
  keynode keybuf[KEYBUFSIZE];
} player;

#include "attack.h"

void renderplayer(player *, SDL_Renderer *);
void initialiseplayer(player *, int);
void updateplayer(player *, int , int);
void keydown(player *, SDL_Keycode, unsigned long);
void keyup(player *, SDL_Keycode, unsigned long);
#endif
