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

void keydown(player *p, SDL_Keycode key, unsigned long milliseconds) {
  keynode *currentnode, *previousnode, *newnode;
  newnode = malloc(sizeof(keynode));
  if (newnode == NULL) {
    printf("Not enough memory for key list.");
    return;
  }
  
  currentnode = p->keys;
  previousnode = NULL;

  newnode->key = key;
  newnode->milliseconds = milliseconds;
  newnode->next = NULL;
  
  while (currentnode != NULL) {
    if (currentnode->key == key)
      return;
    previousnode = currentnode;
    currentnode = currentnode->next;
  }
  
  if (previousnode == NULL) {
    p->keys = newnode;
    return;
  }
  
  previousnode->next = newnode;
}

void keyup(player *p, SDL_Keycode key, unsigned long milliseconds) {
  int i;
  keynode *currentnode, *previousnode, *tempnode;
  currentnode = p->keys;
  previousnode = NULL;

  while (currentnode != NULL && currentnode->key != key) {
    previousnode = currentnode;
    currentnode = currentnode->next;
  }

  tempnode = currentnode;

  if (currentnode == NULL) {
    printf("Cannot remove key\n");
    return;
  } if (previousnode == NULL) {
    p->keys = currentnode->next;
  } else {
    previousnode->next = currentnode->next;
  }

  for (i = 0; i < KEYBUFSIZE - 1; i++)
    p->keybuf[i + 1] = p->keybuf[i];
  p->keybuf[0] = *tempnode;
  p->keybuf[0].milliseconds = milliseconds - p->keybuf[0].milliseconds;

  free(tempnode);
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
    break;
  case SDLK_d:
    p->acc.x = playertypes[p->type].accel;
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
  attack a = playertypes[p1->type].attacks[p1->state];
  if (frame < a.startframe || frame > a.endframe) {
    if (frame > a.waitframe) {
      p1->state = -1;
      p1->frame = 0;
    }
    return;
  }

  if (rectanglecollide(vadd(a.pos, p1->pos), a.hitbox,
		       p2->pos, playertypes[p2->type].hitbox)) {
    p2->health -= a.damage;
  }
}
