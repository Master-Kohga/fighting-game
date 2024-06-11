#ifndef _STAGE_
#define _STAGE_

#include <SDL2/SDL.h>

#define FLOORHEIGHT 480
#define GRAVITY 4.9

#define MAXLAYERSF 10
#define MAXLAYERSB 10
#define NUMBEROFSTAGES 1
#define MAXSTRING 100

#define BACKGROUNDDIR "/background"
#define FOREGROUNDDIR "/foreground"

void renderbackground(int, int, float, int, int, SDL_Renderer *);
void renderforeground(int, int, float, int, int, SDL_Renderer *);
void loadlayers(int, SDL_Renderer *, char *);
void freelayers(int);

#endif
