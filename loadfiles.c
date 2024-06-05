#include "loadfiles.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void *, const void *);

char **loadfilenames(char *s, int *l) {
  DIR *d;
  struct dirent *dir;
  char *c = malloc(100);
  strcpy(c, s);
  c = strcat(c, "/");
  *l = 0;

  char **directory = malloc(MAXFILES);

  d = opendir(s);
  if (!d)
    printf("Error loading directory %s\n", s);

  while ((dir = readdir(d)) != NULL) {
    if (*dir->d_name == '.')
      continue;
    c = strcat(c, dir->d_name);
    directory[*l] = malloc(MAXSTRING);
    strcpy(directory[(*l)++], c);
    strcpy(c, s);
    c = strcat(c, "/");
  }

  free(c);
  closedir(d);

  directory[*l] = NULL;
  qsort(directory, *l, sizeof(char *), compare);
  return directory;
}

void freefilenames(char **s, int l) {
  int i;
  for (i = 0; i < l; i++) {
    free(s[i]);
  }
  
  free(s);
}

int compare(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}
