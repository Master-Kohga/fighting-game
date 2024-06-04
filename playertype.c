#include "playertype.h"
#include <SDL2/SDL.h>

playertype playertypes[NUMBEROFPLAYERTYPES] =
  {
    {12, 2.5, 500, {}, {100, 200}, {
	{{0, 0}, {20, 100}, {10, 10}, {5, -40}, 3, 30, 35, 10, 1}
      }}
  };

playertype getplayertype(int i) {
  return playertypes[i];
}

void loadanimations(int type, SDL_Renderer *renderer, char *s) {
  playertypes[type].animations[0] = loadanimation(s, renderer);
}
