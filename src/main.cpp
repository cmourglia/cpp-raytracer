#include <stdio.h>
#include <string.h>

#include "boilerplate.h"

#include "ray.h"
#include "vec3.h"

bool hit_sphere(const point3& center, double radius, const ray& r) {
  vec3 oc = r.origin - center;
  double a = dot(r.direction, r.direction);
  double b = 2 * dot(oc, r.direction);
  double c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;
  return discriminant > 0;
}

color ray_color(const ray& r) {
  if (hit_sphere(point3(0, 0, -1), 0.5, r)) {
    return color(1, 0, 0);
  }

  vec3 unit_dir = unit_vector(r.direction);
  double t = 0.5 * (unit_dir.y + 1);
  return (1 - t) * color(1, 1, 1) + t * color(0.5, 0.7, 1);
}

int main() {
  double aspect_ratio = 16.0f / 9.0f;

  int image_height = 800;
  int image_width = aspect_ratio * image_height;

  if (!setup(image_width, image_height)) {
    return 1;
  }

  // ----------------------------------------------------
  // DO RAYTRACING HERE

  // Camera
  double viewport_height = 2;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1;

  point3 origin = point3(0, 0, 0);
  vec3 horizontal = vec3(viewport_width, 0, 0);
  vec3 vertical = vec3(0, viewport_height, 0);
  vec3 lower_left_corner =
      origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

  // Render
  for (int j = 0; j < image_height; ++j) {
    for (int i = 0; i < image_width; ++i) {
      double u = double(i) / (image_width - 1);
      double v = double(j) / (image_height - 1);

      ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      color pixel_color = ray_color(r);
      set_pixel(pixel_color, i, j);
    }
  }

  // IGNORE AFTER THIS
  // ----------------------------------------------------

  return display_result();
}
