#include "stage.h"
#include <stdio.h>

typedef struct {
  float speed;
  SDL_Texture *texture;
} layer;

typedef struct {
  int width, height, floorheight;
  //Add textures for foreground, and background.
  //Probably should have a struct containing texture and speed.
  //Array of those will form parallax scrolling
  layer backgroundlayer;
  layer foregroundlayer;
} stage;

stage stages[NUMBEROFSTAGES] =
  {{1000, 480, 250}};

layer loadlayer(char *, float, SDL_Renderer *);
SDL_Texture *loadtexture(char *, SDL_Renderer *);

void renderbackground(int i, int camerapos, float zoom, int width, int height, SDL_Renderer *renderer) {
  SDL_Texture *background;
  SDL_Rect screenrect;
  
  background = stages[i].backgroundlayer.texture;//SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, stages[i].width, stages[i].height);
  
  //The following code will be replaced eventually
  //in order to render background textures
  /*SDL_SetRenderTarget(renderer, background);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);*/
  
  screenrect.x = stages[i].width / 2 - (width / 2) / zoom + camerapos * stages[i].backgroundlayer.speed;
  screenrect.y = stages[i].height / 2 - (height / 2) / zoom;
  screenrect.w = width / zoom;
  screenrect.h = height / zoom;
  
  //SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, background, &screenrect, NULL);
}

void renderforeground(int i, int camerapos, float zoom, int width, int height, SDL_Renderer *renderer) {
  SDL_Texture *foreground;
  SDL_Rect screenrect, floorrect;
  
  foreground = stages[i].foregroundlayer.texture;//SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, stages[i].width, stages[i].height);
  SDL_SetTextureBlendMode(foreground, SDL_BLENDMODE_BLEND);
  
  //The following code will be replaced eventually
  //in order to render foreground textures
  /*SDL_SetRenderTarget(renderer, foreground);

  floorrect = (SDL_Rect) {0, stages[i].floorheight, stages[i].width, stages[i].height};

  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderFillRect(renderer, &floorrect);*/
  
  screenrect.x = stages[i].width / 2 - (width / 2) / zoom + camerapos * stages[i].foregroundlayer.speed;
  screenrect.y = stages[i].height / 2 - (height / 2) / zoom;
  screenrect.w = width / zoom;
  screenrect.h = height / zoom;
  
  //SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, foreground, &screenrect, NULL);
}

void setbackgroundlayer(int i, char *s, float speed, SDL_Renderer *renderer) {
  stages[i].backgroundlayer = loadlayer(s, speed, renderer);
}

void setforegroundlayer(int i, char *s, float speed, SDL_Renderer *renderer) {
  stages[i].foregroundlayer = loadlayer(s, speed, renderer);
}

layer loadlayer(char *s, float speed, SDL_Renderer *renderer) {
  layer l;
  l.texture = loadtexture(s, renderer);
  l.speed = speed;
  return l;
}

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
