#include <stdio.h>
#include "player.h"

#define NUMBEROFPLAYERTYPES 1
#define FLOORHEIGHT 500

typedef struct {
  int (*update)(player *, SDL_Keycode);
  //SDL_Textures textures[0];
  vec hitbox;
} playertype;

int manupdate(player *, SDL_Keycode);

const playertype playertypes[NUMBEROFPLAYERTYPES] =
  {{manupdate, {20, 20}}};

void initialiseplayer(player *p, int type) {
  p->type = type;
}

void updateplayer(player *p, SDL_Keycode key) {
  playertypes[p->type].update(p, key);
  p->pos = vadd(p->pos, p->vel);
  if (p->pos.y > FLOORHEIGHT)
    p->pos.y = FLOORHEIGHT;
  p->vel = vadd(p->vel, p->acc);
  printf("%d, %d\n", p->pos.x, p->pos.y);
}

int manupdate(player *p, SDL_Keycode key) {
  switch (key) {
  case SDLK_a:
    p->acc.x -= 5;
    break;
  case SDLK_d:
    p->acc.x += 5;
    break;
  case SDLK_w:
    p->acc.y -= 5;
    break;
  }

  return 0;
}
