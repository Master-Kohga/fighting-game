#include <stdio.h>
#include "vector.h"

vec vadd(vec v, vec u) {
  v.x += u.x;
  v.y += u.y;
  return v;
}

vec vsub(vec v, vec u) {
  v.x -= u.x;
  v.y -= u.y;
  return v;
}

vec vmul(vec v, vec u) {
  v.x *= u.x;
  v.y *= u.y;
  return v;
}

vec vdiv(vec v, vec u) {
  v.x /= u.x;
  v.y /= u.y;
  return v;
}

