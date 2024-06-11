#include "stage.h"
#include "animation.h"
#include "loadfiles.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  float speed;
  SDL_Texture *texture;
} layer;

typedef struct {
  int width, height, floorheight;
  int bounds;
  layer backgroundlayers[MAXLAYERSB];
  layer foregroundlayers[MAXLAYERSF];
  int numberofbackgroundlayers, numberofforegroundlayers;
} stage;

stage stages[NUMBEROFSTAGES] =
  {{2560, 480, 250, 1000, {{2, NULL}, {2.5, NULL}, {3, NULL}, {1.5, NULL}}, {{1, NULL}, {2, NULL}}, 0, 0}};

int getlowerbound(int level) {
  return stages[level].bounds - stages[level].width / 2;
}

int getupperbound(int level) {
  return stages[level].width / 2 - stages[level].bounds;
}

void loadlayers(int level, SDL_Renderer *renderer, char *s) {
  int l, i;
  char *sb = malloc(MAXSTRING);
  char *sf = malloc(MAXSTRING);
  char **c;

  *sb = *sf = '\0';

  strcat(sb, s);
  strcat(sb, BACKGROUNDDIR);
  c = loadfilenames(sb, &l);

  for (i = 0; i < l; i++) {
    stages[level].backgroundlayers[i].texture = loadtexture(c[i], renderer);
    SDL_SetTextureBlendMode(stages[level].backgroundlayers[i].texture, SDL_BLENDMODE_BLEND);
  }

  stages[level].numberofbackgroundlayers = l;
  freefilenames(c, l);

  strcat(sf, s);
  strcat(sf, FOREGROUNDDIR);
  c = loadfilenames(sf, &l);

  for (i = 0; i < l; i++) {
    stages[level].foregroundlayers[i].texture = loadtexture(c[i], renderer);
    SDL_SetTextureBlendMode(stages[level].foregroundlayers[i].texture, SDL_BLENDMODE_BLEND);
  }

  stages[level].numberofforegroundlayers = l;
  freefilenames(c, l);

  free(sb);
  free(sf);
}

void freelayers(int level) {
  int i;
  for (i = 0; i < stages[level].numberofbackgroundlayers; i++) {
    SDL_DestroyTexture(stages[level].backgroundlayers[i].texture);
  }

  for (i = 0; i < stages[level].numberofforegroundlayers; i++) {
    SDL_DestroyTexture(stages[level].foregroundlayers[i].texture);
  }
}

void renderbackground(int level, int camerapos, float zoom, int width, int height, SDL_Renderer *renderer) {
  int i, basescreenx;
  const layer *layers = stages[level].backgroundlayers;
  SDL_Rect screenrect;

  basescreenx = stages[level].width / 2 - (width / 2) / zoom;
  screenrect.y = stages[level].height / 2 - (height / 2) / zoom;
  screenrect.w = width / zoom;
  screenrect.h = height / zoom;
  
  for (i = 0; i < stages[level].numberofbackgroundlayers; i++) {
    screenrect.x = basescreenx + camerapos * layers[i].speed;
    SDL_RenderCopy(renderer, layers[i].texture, &screenrect, NULL);
  }
}

void renderforeground(int level, int camerapos, float zoom, int width, int height, SDL_Renderer *renderer) {
  int i, basescreenx;
  const layer *layers = stages[level].foregroundlayers;
  SDL_Rect screenrect;

  basescreenx = stages[level].width / 2 - (width / 2) / zoom;
  screenrect.y = stages[level].height / 2 - (height / 2) / zoom;
  screenrect.w = width / zoom;
  screenrect.h = height / zoom;
  
  for (i = 0; i < stages[level].numberofforegroundlayers; i++) {
    screenrect.x = basescreenx + camerapos * layers[i].speed;
    SDL_RenderCopy(renderer, layers[i].texture, &screenrect, NULL);
  }
}
