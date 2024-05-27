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

vec invertx(vec v) {
  vec u = {-1, 1};
  return vmul(v, u);
}
