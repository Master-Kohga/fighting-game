#include "key.h"

void keydown(keynode **p, SDL_Keycode key, unsigned long milliseconds) {
  keynode *currentnode, *previousnode, *newnode;
  newnode = malloc(sizeof(keynode));
  if (newnode == NULL) {
    printf("Not enough memory for key list.");
    return;
  }
  
  currentnode = *p;
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
    *p = newnode;
    return;
  }
  
  previousnode->next = newnode;
}

keynode keyup(keynode **p, SDL_Keycode key, unsigned long milliseconds) {
  keynode *currentnode, *previousnode, *tempnode, node;
  currentnode = *p;
  previousnode = NULL;

  while (currentnode != NULL && currentnode->key != key) {
    previousnode = currentnode;
    currentnode = currentnode->next;
  }

  tempnode = currentnode;

  if (currentnode == NULL) {
    printf("Cannot remove key\n");
    return NKEY;
  } if (previousnode == NULL) {
    *p = currentnode->next;
  } else {
    previousnode->next = currentnode->next;
  }

  /*for (i = 0; i < KEYBUFSIZE - 1; i++)
    p->keybuf[i + 1] = p->keybuf[i];
  p->keybuf[0] = *tempnode;
  p->keybuf[0].milliseconds = milliseconds - p->keybuf[0].milliseconds;*/

  node = *tempnode;
  free(tempnode);
  return node;
}
