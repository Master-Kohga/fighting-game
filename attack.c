#include "attack.h"
#include <stdio.h>

int rectanglecollide(vec pos1, vec hitbox1, vec pos2, vec hitbox2) {
  int collision =
    pos1.x < pos2.x + hitbox2.x &&
    pos1.x + hitbox1.x > pos2.x &&
    pos1.y < pos2.y + hitbox2.y &&
    pos1.y + hitbox1.y > pos2.y;
  return collision;
}
