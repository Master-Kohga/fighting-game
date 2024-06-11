#include <SDL2/SDL.h>
#include "stage.h"
#include "player.h"
#include "playertype.h"
#include <stdio.h>

#define WINDOWWIDTH 640
#define WINDOWHEIGHT 480
#define NUMBEROFPLAYERS 2

/*Add:
  Quick start screen
  Character select screen
  Healthbar
  Enemy AI
 */

int main() {
  int game = 1, zoom = 5, xoffset;
  player players[NUMBEROFPLAYERS] = {
    {0, -1, 0, 100, -1, {0, 0}, {0, 0}, {0, 0}, NULL},
    {0, -1, 0, 100, 1, {100, 100}, {0, 0}, {0, 0}, NULL}};
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event e;

  SDL_Init(SDL_INIT_VIDEO);
  if ((window = SDL_CreateWindow("FIGHTING TEST", 0, 0, WINDOWWIDTH, WINDOWHEIGHT, 0)) == NULL)
    printf("WINDOW INITIALISATION ERROR\n");
  if ((renderer = SDL_CreateRenderer(window, -1, 0)) == NULL)
    printf("RENDERER INITIALISATION ERROR\n");

  loadlayers(0, renderer, "night");
  loadanimations(0, renderer, "loop");

  while (game) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
	game = 0;
	break;
      case SDL_KEYDOWN:
	if (e.key.repeat == 0)
	  pkeydown(players,  e.key.keysym.sym, e.key.timestamp);
	break;
      case SDL_KEYUP:
	pkeyup(players, e.key.keysym.sym, e.key.timestamp);
	break;
      }
    }
    
    updateplayer(players, 0, NUMBEROFPLAYERS);
    updateplayer(players, 1, NUMBEROFPLAYERS);

    xoffset = getscreencentre(players, players + 1);

    renderbackground(0, xoffset, 1, WINDOWWIDTH, WINDOWHEIGHT, renderer);
    renderplayer(xoffset - WINDOWWIDTH / 2, players, renderer);
    renderplayer(xoffset - WINDOWWIDTH / 2, players + 1, renderer);
    renderforeground(0, xoffset, 1, WINDOWWIDTH, WINDOWHEIGHT, renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000 / 30);
  }
  
  freelayers(0);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
