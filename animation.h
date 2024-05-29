#ifndef _ANIMATION_
#define _ANIMATION_

#include <SDL2/SDL.h>
#define MAXFRAMES 500

typedef struct animation {
  SDL_Texture *frames[MAXFRAMES];
  int length;
} animation;

SDL_Texture *loadtexture(char *s, SDL_Renderer *);
animation loadanimation(char *s, SDL_Renderer *);

#endif
