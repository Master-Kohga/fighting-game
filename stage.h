#ifndef _STAGE_
#define _STAGE_

#include <SDL2/SDL.h>

#define FLOORHEIGHT 350
#define GRAVITY 4.9
#define NUMBEROFSTAGES 1


void setbackgroundlayer(int , char *, float, SDL_Renderer *);
void setforegroundlayer(int, char *, float, SDL_Renderer *);
void renderbackground(int, int, float, int, int, SDL_Renderer *);
void renderforeground(int, int, float, int, int, SDL_Renderer *);

#endif
