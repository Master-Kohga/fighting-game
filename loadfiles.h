#ifndef _LOADFILES_
#define _LOADFILES_

#define MAXFILES 100
#define MAXSTRING 100

char ** loadfilenames(char *, int *);
void freefilenames(char **, int);

#endif
