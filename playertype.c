#include "playertype.h"
#include "loadfiles.h"
#include <SDL2/SDL.h>

playertype playertypes[NUMBEROFPLAYERTYPES] =
  {
    {12, 2.5, 500, {}, {100, 200}, {
	{{0, 0}, {20, 100}, {10, 10}, {5, -40}, 5, 7, 8, 10, 0}
      }}
  };

playertype getplayertype(int i) {
  return playertypes[i];
}

void loadanimations(int type, SDL_Renderer *renderer, char *s) {
  int l, i;
  char **c = loadfilenames(s, &l);

  for (i = 0; i < l; i++) {
    playertypes[type].animations[i] = loadanimation(c[i], renderer);
  }

  freefilenames(c, l);
}
