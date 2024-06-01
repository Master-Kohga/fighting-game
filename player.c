#include <stdio.h>
#include <math.h>
#include "player.h"
#include "stage.h"
#include "animation.h"

#define FRACTION(MAX, ACC) (((MAX / ACC) - 1) / (MAX / ACC))

void attackplayer(player *, player *);
void beginattack(player *, int);
void endattack(player *);
int playerinput(player *, SDL_Keycode);

typedef struct {
  float maxvel, accel, jumpheight;
  animation animations[NUMBEROFANIMATIONS];
  vec hitbox;
  attack attacks[NUMBEROFATTACKS];
} playertype;

playertype playertypes[NUMBEROFPLAYERTYPES] =
  {{12, 2.5, 500, {}, {20, 100}, {{{0, 0}, {20, 100}, {10, 10}, {5, -40}, 3, 30, 35, 10, 1}}}};

void loadanimations(int type, SDL_Renderer *renderer, char *s) {
  playertypes[type].animations[0] = loadanimation(s, renderer);
}

void updateplayer(player *players, int index, int length) {
  int i;
  player *p = &players[index];
  keynode *keyn = p->keys;

  p->frame++;
  p->acc.x = 0;
  p->acc.y = GRAVITY;

  //uncomment when the other animations and animation loading is added.
  //if (p->frame > playertypes[p->type].animations[p->state + NUMBEROFSTATES].length)
  //p->frame = 0;

  if (p->state >= 0) {
    for (i = 0; i < length; i++) {
      if (index == i)
	continue;
      attackplayer(p, &players[i]);
    }
  } else {
    while (keyn != NULL) {
      playerinput(p, keyn->key);
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

  //SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  //SDL_RenderFillRect(renderer, &rect);
  //animation a = playertypes[p->type].animations[p->state];
  animation a = playertypes[p->type].animations[0];
  SDL_Texture *t = a.frames[p->frame % a.length];
  SDL_RenderCopy(renderer, t, NULL, &rect);
}

// MAKE UNIVERSAL MOVEMENT FUNCTION
// MAKE FUNCTION WHICH MAPS INPUT KEYS TO ATTACKS
int playerinput(player *p, SDL_Keycode key) {
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
    break;
  case SDLK_e:
    beginattack(p, 0);
    break;
  default:
    break;
  }
  return 0;
}

void attackplayer(player *p1, player *p2) {
  int frame = p1->frame++;
  attack a = playertypes[p1->type].attacks[p1->state];
  if (frame < a.startframe || frame > a.endframe) {
    if (frame > a.waitframe)
      endattack(p1);
    return;
  }
  
  //a.pvel.y += vy;
  if (p1->direction < 0) {
    a.pvel = invertx(a.pvel);
    a.ovel = invertx(a.ovel);
    a.pos = invertx(a.pos);
    a.hitbox = invertx(a.hitbox);
  }

  p1->vel.x = 0;
  p1->vel = vadd(p1->vel, a.pvel);

  if (rectanglecollide(vadd(a.pos, p1->pos), a.hitbox,
		       p2->pos, playertypes[p2->type].hitbox)) {
    p2->vel = a.ovel;
    p2->health -= a.damage;
    if (a.endoncollision) {
      p1->frame = a.endframe;
      return;
    }
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

void endattack(player *p) {
  p->frame = 0;
  p->state = -1;
}

void beginattack(player *p, int attack) {
  p->frame = 0;
  p->state = attack;
}
