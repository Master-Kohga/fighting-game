#ifndef _KEYS_
#define _KEYS_

#include "SDL2/SDL.h"

#define NKEY ((keynode) {SDLK_l, 0, NULL})

typedef struct keynode {
  SDL_Keycode key;
  unsigned long milliseconds;
  struct keynode *next;
} keynode;

void keydown(keynode **, SDL_Keycode, unsigned long);
keynode keyup(keynode **, SDL_Keycode, unsigned long);

#endif
