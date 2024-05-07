#ifndef _STAGE_
#define _STAGE_

#include <SDL2/SDL.h>

#define FLOORHEIGHT 500
#define GRAVITY 9.8
#define NUMBEROFSTAGES 1

void renderbackground(int, int, int, int, int, SDL_Renderer *);
void renderforeground(int, int, int, int, int, SDL_Renderer *);

#endif
