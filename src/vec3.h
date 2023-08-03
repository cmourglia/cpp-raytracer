#pragma once

#include <cmath>

union vec3 {
  struct {
    double x, y, z;
  };

  double e[3];

  vec3() = default;
  vec3(double vx, double vy, double vz) : x{vx}, y{vy}, z{vz} {}
  ~vec3() = default;
  vec3(const vec3&) = default;
  vec3(vec3&&) = default;
  vec3& operator=(const vec3&) = default;
  vec3& operator=(vec3&&) = default;

  double operator[](int i) const { return e[i]; }
  double& operator[](int i) { return e[i]; }

  vec3 operator-() const { return {-x, -y, -z}; }

  vec3& operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  vec3& operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  vec3& operator*=(double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
  }

  vec3& operator/=(double t) {
    double i = 1.0f / t;
    x *= i;
    y *= i;
    z *= i;
    return *this;
  }

  double length() const { return std::sqrt(length_squared()); }

  double length_squared() const { return x * x + y * y + z * z; }
};

using point3 = vec3;
using color = vec3;

inline vec3 operator+(const vec3& a, const vec3& b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline vec3 operator-(const vec3& a, const vec3& b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline vec3 operator*(const vec3& a, const vec3& b) {
  return {a.x * b.x, a.y * b.y, a.z * b.z};
}

inline vec3 operator*(const vec3& a, double t) {
  return {a.x * t, a.y * t, a.z * t};
}

inline vec3 operator*(double t, const vec3& a) {
  return a * t;
}

inline vec3 operator/(const vec3& a, double t) {
  return a * (1.0f / t);
}

inline double dot(const vec3& a, const vec3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 cross(const vec3& a, const vec3& b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}