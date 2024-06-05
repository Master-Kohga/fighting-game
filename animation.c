#include "animation.h"
#include "loadfiles.h"
#include <stdlib.h>
#include <stdio.h>


SDL_Texture *loadtexture(char *s, SDL_Renderer *renderer) {
  SDL_Texture *texture;
  SDL_Surface *surface = SDL_LoadBMP(s);
  if (surface == NULL)
    printf("ERROR\n");

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == NULL)
    printf("ERROR\n");
  return texture;
}

animation loadanimation(char *s, SDL_Renderer *renderer) {
  int l, i;
  animation a;
  char **c = loadfilenames(s, &l);

  for (i = 0; i < l; i++) {
    a.frames[i] = loadtexture(c[i], renderer);
    printf("%s\n", c[i]);
  }

  freefilenames(c, l);
  a.length = l;
  return a;
}

//Add read directory function which returns a sorted list of filenames in a directory

