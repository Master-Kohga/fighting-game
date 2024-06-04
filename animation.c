#include "animation.h"
#include <stdlib.h>
#include <dirent.h>
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
  int i = 0;
  animation a;
  char *c = malloc(100);
  strcpy(c, s);
  c = strcat(c, "/");

  DIR *d;
  struct dirent *dir;
  
  d = opendir(s);
  if (!d)
    printf("Error loading directory %s\n", s);

  while ((dir = readdir(d)) != NULL) {
    if (*dir->d_name == '.')
      continue;
    c = strcat(c, dir->d_name);
    printf("%s\n", c);
    a.frames[i++] = loadtexture(c, renderer);
    strcpy(c, s);
    c = strcat(c, "/");
  }
  
  free(c);
  closedir(d);

  a.length = i;
  return a;
}

//Add read directory function which returns a sorted list of filenames in a directory
