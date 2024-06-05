#include <SDL2/SDL.h>
#include "stage.h"
#include <stdio.h>

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480

int main() {
  int game = 1, zoom = 5;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event e;

  SDL_Init(SDL_INIT_VIDEO);
  if ((window = SDL_CreateWindow("FIGHTING TEST", 0, 0, WINDOWWIDTH, WINDOWHEIGHT, 0)) == NULL)
    printf("WINDOW INITIALISATION ERROR\n");
  if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL)
    printf("RENDERER INITIALISATION ERROR\n");

  setbackgroundlayer(0, "background.bmp", 0.5, renderer);
  setforegroundlayer(0, "foreground.bmp", 1, renderer);

  while (game) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
	game = 0;
	break;
      }
    }

    renderbackground(0, zoom, 1, WINDOWWIDTH, WINDOWHEIGHT, renderer);
    renderforeground(0, zoom, 1, WINDOWWIDTH, WINDOWHEIGHT, renderer);
    SDL_RenderPresent(renderer);

    zoom = (zoom + 5) % 200;
    SDL_Delay(100);
  }
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
