#pragma once

#include "vec3.h"

struct ray {
  point3 origin;
  vec3 direction;

  ray() = default;
  ray(const point3& o, const vec3& d) : origin{o}, direction{d} {};

  point3 at(float t) const { return origin + t * direction; }
};