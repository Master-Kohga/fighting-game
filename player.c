#include <stdio.h>
#include <math.h>
#include "player.h"
#include "playertype.h"
#include "stage.h"

#define FRACTION(MAX, ACC) (((MAX / ACC) - 1) / (MAX / ACC))

void setdirection(player *, player *);
void attackplayer(player *, player *);
void beginattack(player *, int);
void endattack(player *);
int playerinput(player *, SDL_Keycode);

void updateplayer(player *players, int index, int length) {
  int i;
  player *p = &players[index];
  playertype pt = getplayertype(p->type);
  keynode *keyn = p->keys;

  p->frame++;
  p->acc.x = 0;
  p->acc.y = GRAVITY;

  //uncomment when the other animations and animation loading is added.
  //if (p->frame > playertypes[p->type].animations[p->state + NUMBEROFSTATES].length)
  //p->frame = 0;


  for (i = 0; i < length; i++) {
    if (index == i)
      continue;
    setdirection(p, &players[i]);
    attackplayer(p, &players[i]);
  }

  if (p->state < 0) {
    while (keyn != NULL) {
      playerinput(p, keyn->key);
      keyn = keyn->next;
    }
  }
  
  p->vel = vadd(p->vel, p->acc);
  p->pos = vadd(p->pos, p->vel);
  if (p->pos.y + pt.hitbox.y > FLOORHEIGHT) {
    p->pos.y = FLOORHEIGHT - pt.hitbox.y;
    p->vel.y = 0;
  }
  
  p->vel.x *= FRACTION(pt.maxvel, pt.accel);
}

void renderplayer(player *p, SDL_Renderer *renderer) {
  SDL_Rect rect;
  playertype pt = getplayertype(p->type);
  
  rect.x = p->pos.x;
  rect.y = p->pos.y;
  rect.w = pt.hitbox.x;
  rect.h = pt.hitbox.y;

  //SDL_RenderFillRect(renderer, &rect);
  //animation a = pt.animations[p->state];
  animation a = pt.animations[0];
  SDL_Texture *t = a.frames[p->frame % a.length];
  SDL_RenderCopyEx(renderer, t, NULL, &rect, 0, NULL, p->direction + 1 ? 0 : SDL_FLIP_HORIZONTAL);
}

// MAKE FUNCTION WHICH MAPS INPUT KEYS TO ATTACKS
int playerinput(player *p, SDL_Keycode key) {
  playertype pt = getplayertype(p->type);
  switch (key) {
  case SDLK_a:
    if (p->direction < 0 || p->vel.y != 0)
      p->acc.x = 0 - pt.accel;
    else
      p->acc.x = 0 - pt.accel / BACKWARDSSLOW;
    break;
  case SDLK_d:
    if (p->direction > 0 || p->vel.y != 0)
      p->acc.x = pt.accel;
    else
      p->acc.x = pt.accel / BACKWARDSSLOW;
    break;
  case SDLK_w:
    if (p->vel.y == 0)
      p->vel.y = 0 - sqrt(2 * GRAVITY * pt.jumpheight);
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
  if (p1->state < 0)
    return;
  
  int frame = p1->frame;
  attack a = getplayertype(p1->type).attacks[p1->state];
  if (frame < a.startframe || frame > a.endframe) {
    if (frame > a.waitframe)
      endattack(p1);
    return;
  }
  
  if (p1->direction < 0) {
    a.pvel = invertx(a.pvel);
    a.ovel = invertx(a.ovel);
    a.pos = invertx(a.pos);
    a.hitbox = invertx(a.hitbox);
  }

  p1->vel.x = 0;
  p1->vel = vadd(p1->vel, a.pvel);

  if (rectanglecollide(vadd(a.pos, p1->pos), a.hitbox,
		       p2->pos, getplayertype(p2->type).hitbox)) {
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

void setdirection(player *p1, player *p2) {
  if (p1->pos.x - p2->pos.x > 0)
    p1->direction = -1;
  else
    p1->direction = 1;
}
