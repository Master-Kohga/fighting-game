#include "stage.h"

typedef struct {
  int width, height, floorheight;
  //Add textures for foreground, and background.
  //Probably should have a struct containing texture and speed.
  //Array of those will form parallax scrolling
} stage;

stage stages[NUMBEROFSTAGES] =
  {1000, 480, 400};

void renderbackground(int i, int camerapos, int zoom, int width, int height, SDL_Renderer *renderer) {
  SDL_Texture *background;
  SDL_Rect screenrect;
  
  background = SDL_CreateTexture(renderer, SDL_PIXEL_FORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, stages[i].width, stages[i].height);

  //The following code will be replaced eventually
  //in order to render background textures
  SDL_SetRenderTarget(renderer, background);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderClear(renderer);

  screenrect.x = stages[i].width / 2 - (width / 2) / zoom + camerapos;
  screenrect.y = stages[i].height / 2 - (height / 2) / zoom + camerapos;
  screenrect.w = width / zoom;
  screenrect.h = height / zoom;
  
  SDL_RenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, background, &screenrect, NULL);
}

void renderforeground(int i, int camerapos, int zoom, int width, int height, SDL_Renderer *renderer) {
  SDL_Texture *foreground;
  SDL_Rect screenrect, floorrect;
  
  foreground = SDL_CreateTexture(renderer, SDL_PIXEL_FORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, stages[i].width, stages[i].height);

  //The following code will be replaced eventually
  //in order to render background textures
  SDL_SetRenderTarget(renderer, foreground);
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  floorrect = {0, stages[i].floorheight, stages[i].width, stages[i].height};
  SDL_RenderFillRect(renderer, floorrect);

  screenrect.x = stages[i].width / 2 - (width / 2) / zoom + camerapos;
  screenrect.y = stages[i].height / 2 - (height / 2) / zoom + camerapos;
  screenrect.w = width / zoom;
  screenrect.h = height / zoom;
  
  SDL_RenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, foreground, &screenrect, NULL);
}
