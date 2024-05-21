#include <stdio.h>
#include <math.h>
#include "player.h"
#include "stage.h"

#define FRACTION(MAX, ACC) (((MAX / ACC) - 1) / (MAX / ACC))

void attackplayer(player *, player *);

typedef struct {
  int (*update)(player *, SDL_Keycode);
  float maxvel, accel, jumpheight;
  //SDL_Textures textures[0];
  vec hitbox;
  attack attacks[NUMBEROFATTACKS];
} playertype;

int manupdate(player *, SDL_Keycode);

const playertype playertypes[NUMBEROFPLAYERTYPES] =
  {{manupdate, 12, 2.5, 500, {20, 100}, {{{0, 0}, {100, 100}, 3, 5, 5, 10}}}};

void initialiseplayer(player *p, int type) {
  p->type = type;
}

void updateplayer(player *players, int index, int length) {
  int i;
  player *p = &players[index];
  keynode *keyn = p->keys;

  printf("HEALTH: %d\n", p->health);
  //printf("COLLISION: %d\n", rectanglecollide(p->pos, playertypes[p->type].hitbox, players[(index + 1 % 2)].pos, playertypes[players[(index + 1 % 2)].type].hitbox));
  
  p->acc.x = 0;
  p->acc.y = GRAVITY;

  if (p->state >= 0) {
    for (i = 0; i < length; i++) {
      if (index == i)
	continue;
      attackplayer(p, &players[i]);
    }
  }

  if (p->state < 0) {
    while (keyn != NULL) {
      playertypes[p->type].update(p, keyn->key);
      keyn = keyn->next;
    }
  }
  
  p->vel = vadd(p->vel, p->acc);
  p->pos = vadd(p->pos, p->vel);
  if (p->pos.y + playertypes[p->type].hitbox.y > FLOORHEIGHT) {
    p->pos.y = FLOORHEIGHT - playertypes[p->type].hitbox.y;
    p->vel.y = 0;
  }
  
  p->vel.x *= FRACTION(playertypes[p->type].maxvel, playertypes[p->type].accel);
}

void renderplayer(player *p, SDL_Renderer *renderer) {
  SDL_Rect rect;
  
  rect.x = p->pos.x;
  rect.y = p->pos.y;
  rect.w = playertypes[p->type].hitbox.x;
  rect.h = playertypes[p->type].hitbox.y;

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(renderer, &rect);
}

int manupdate(player *p, SDL_Keycode key) {
  switch (key) {
  case SDLK_a:
    p->acc.x = 0 - playertypes[p->type].accel;
    p->direction = -1;
    break;
  case SDLK_d:
    p->acc.x = playertypes[p->type].accel;
    p->direction = 1;
    break;
  case SDLK_w:
    if (p->vel.y == 0)
      p->vel.y = 0 - sqrt(2 * GRAVITY * playertypes[p->type].jumpheight);
    //keyup(p, key, SDL_GetTicks64());
    break;
  case SDLK_e:
    p->state = 0;
    break;
  default:
    break;
  }
  return 0;
}

void attackplayer(player *p1, player *p2) {
  int frame = p1->frame++;
  vec direction = {-1, 1}, temp;
  attack a = playertypes[p1->type].attacks[p1->state];
  if (frame < a.startframe || frame > a.endframe) {
    if (frame > a.waitframe) {
      p1->state = -1;
      p1->frame = 0;
    }
    return;
  }
  
  if (p1->direction < 0) {
    a.pos = vmul(a.pos, direction);
    a.hitbox = vmul(a.hitbox, direction);
  }

  if (rectanglecollide(vadd(a.pos, p1->pos), a.hitbox,
		       p2->pos, playertypes[p2->type].hitbox)) {
    p2->health -= a.damage;
  }
}

void pkeydown(player *p, SDL_Keycode key, unsigned long milliseconds) {
  keydown(&p->keys, key, milliseconds);
}

void pkeyup(player *p, SDL_Keycode key, unsigned long milliseconds) {
  int i;
  keynode k = keyup(&p->keys, key, milliseconds);
  
  if (k.milliseconds == 0)
    return;
  
  for (i = 0; i < KEYBUFSIZE - 1; i++)
    p->keybuf[i + 1] = p->keybuf[i];
  p->keybuf[0] = k;
  p->keybuf[0].milliseconds = milliseconds - p->keybuf[0].milliseconds;
}
