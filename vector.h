#ifndef VECTOR
#define VECTOR

typedef struct vector {
  int x, y;
} vec;

vec vadd(vec, vec);
vec vsub(vec, vec);
vec vmul(vec, vec);
vec vdiv(vec, vec);

#endif
