#include <stdio.h>
#include <math.h>
#include "player.h"

#define NUMBEROFPLAYERTYPES 1
#define FLOORHEIGHT 500
#define FRACTION(MAX, ACC) (((MAX / ACC) - 1) / (MAX / ACC))
#define GRAVITY 9.8

typedef struct {
  int (*update)(player *, SDL_Keycode);
  float maxvel, accel, jumpheight;
  //SDL_Textures textures[0];
  vec hitbox;
} playertype;

int manupdate(player *, SDL_Keycode);

const playertype playertypes[NUMBEROFPLAYERTYPES] =
  {{manupdate, 12, 2.5, 100, {20, 20}}};

void initialiseplayer(player *p, int type) {
  p->type = type;
}

void updateplayer(player *p) {
  p->acc.x = 0;
  p->acc.y = 9.8;

  keynode *keyn = p->keys;
  while (keyn != NULL) {
    playertypes[p->type].update(p, keyn->key);
    keyn = keyn->next;
  }

  p->vel = vadd(p->vel, p->acc);
  p->pos = vadd(p->pos, p->vel);
  if (p->pos.y > FLOORHEIGHT) {
    p->pos.y = FLOORHEIGHT;
    p->vel.y = 0;
  }
  
  p->vel.x *= FRACTION(playertypes[p->type].maxvel, playertypes[p->type].accel);
  printf("%f, %f\n", p->pos.x, p->pos.y);
}

void keydown(player *p, SDL_Keycode key) {
  keynode *currentnode, *previousnode, *newnode;
  newnode = malloc(sizeof(keynode));
  if (newnode == NULL) {
    printf("Not enough memory for key list.");
    return;
  }
  
  currentnode = p->keys;
  previousnode = NULL;

  newnode->key = key;
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

void keyup(player *p, SDL_Keycode key) {
  keynode *currentnode, *previousnode, *tempnode;
  currentnode = p->keys;
  previousnode = NULL;

  while (currentnode != NULL && currentnode->key != key) {
    previousnode = currentnode;
    currentnode = currentnode->next;
  }

  tempnode = currentnode;
  
  if (previousnode == NULL) {
    p->keys = currentnode->next;
  } else if (currentnode != NULL) {
    previousnode->next = currentnode->next;
  } else {
    printf("Cannot remove key");
    return;
  }

  free(tempnode);
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
      p->vel.y = 0 - sqrt(0 - -2 * GRAVITY * playertypes[p->type].jumpheight);
    break;
  default:
    break;
  }
  return 0;
}
