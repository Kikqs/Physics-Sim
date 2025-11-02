#pragma once
#ifndef SIM_VEC2_HPP
#define SIM_VEC2_HPP
// include/math/vec2.hpp
// Lightweight 2D vector for physics simulations
//
// Design notes:
//  - Header-only for maximum inlining and optimization
//  - constexpr/noexcept everywhere for performance
//  - No dependencies - can be used anywhere in the project
//  - Dimensionless: can represent position, velocity, force, etc.

#include "../core/concepts.hpp"  // Get Scalar concept from here
#include <cmath>      // std::sqrt
#include <compare>    // std::strong_ordering

namespace sim {

// -----------------------------
// 2D Vector
// -----------------------------
struct Vec2 {
  double x{0.0};
  double y{0.0};

  // ─────────────────────────────────────────────────────────────
  // Constructors
  // ─────────────────────────────────────────────────────────────
  constexpr Vec2() noexcept = default;
  constexpr Vec2(double x_, double y_) noexcept : x(x_), y(y_) {}

  // ─────────────────────────────────────────────────────────────
  // Arithmetic operators
  // ─────────────────────────────────────────────────────────────
  [[nodiscard]] constexpr Vec2 operator+(const Vec2& o) const noexcept { 
    return Vec2{x + o.x, y + o.y}; 
  }
  
  [[nodiscard]] constexpr Vec2 operator-(const Vec2& o) const noexcept { 
    return Vec2{x - o.x, y - o.y}; 
  }
  
  [[nodiscard]] constexpr Vec2 operator*(Scalar auto s) const noexcept { 
    return Vec2{x * s, y * s}; 
  }
  
  [[nodiscard]] constexpr Vec2 operator/(Scalar auto s) const noexcept { 
    return Vec2{x / s, y / s}; 
  }
  
  [[nodiscard]] constexpr Vec2 operator-() const noexcept { 
    return Vec2{-x, -y}; 
  }

  // ─────────────────────────────────────────────────────────────
  // Compound assignment operators
  // ─────────────────────────────────────────────────────────────
  constexpr Vec2& operator+=(const Vec2& o) noexcept { 
    x += o.x; 
    y += o.y; 
    return *this; 
  }
  
  constexpr Vec2& operator-=(const Vec2& o) noexcept { 
    x -= o.x; 
    y -= o.y; 
    return *this; 
  }
  
  constexpr Vec2& operator*=(Scalar auto s) noexcept { 
    x *= s; 
    y *= s; 
    return *this; 
  }
  
  constexpr Vec2& operator/=(Scalar auto s) noexcept { 
    x /= s; 
    y /= s; 
    return *this; 
  }

  // ─────────────────────────────────────────────────────────────
  // Comparison operators (C++20 spaceship)
  // ─────────────────────────────────────────────────────────────
  [[nodiscard]] constexpr auto operator<=>(const Vec2&) const noexcept = default;
  [[nodiscard]] constexpr bool operator==(const Vec2&) const noexcept = default;

  // ─────────────────────────────────────────────────────────────
  // Vector operations
  // ─────────────────────────────────────────────────────────────
  
  /// Dot product: measures alignment between vectors
  [[nodiscard]] constexpr double dot(const Vec2& o) const noexcept { 
    return x * o.x + y * o.y; 
  }
  
  /// 2D cross product: returns scalar (z-component of 3D cross product)
  /// Result > 0: o is counter-clockwise from this
  /// Result < 0: o is clockwise from this
  /// Result = 0: vectors are parallel
  [[nodiscard]] constexpr double cross(const Vec2& o) const noexcept { 
    return x * o.y - y * o.x;
  }

  /// Euclidean length (magnitude) of the vector
  [[nodiscard]] double length() const noexcept { 
    return std::sqrt(x * x + y * y); 
  }
  
  /// Squared length - faster than length() when you only need comparisons
  [[nodiscard]] constexpr double length_sq() const noexcept { 
    return x * x + y * y; 
  }

  /// Returns unit vector in same direction (length = 1)
  /// Returns zero vector if length is zero (avoids division by zero)
  [[nodiscard]] Vec2 normalized() const noexcept {
    const double len = length();
    return len > 0.0 ? *this / len : Vec2{};
  }

  /// Euclidean distance to another vector
  [[nodiscard]] double distance_to(const Vec2& o) const noexcept {
    return (*this - o).length();
  }

  /// Squared distance - faster for comparisons
  [[nodiscard]] constexpr double distance_sq_to(const Vec2& o) const noexcept {
    return (*this - o).length_sq();
  }

  /// Returns vector rotated 90° counter-clockwise
  [[nodiscard]] constexpr Vec2 perpendicular() const noexcept {
    return Vec2{-y, x};
  }
  
  /// Linear interpolation between this and another vector
  /// t=0 returns this, t=1 returns o
  [[nodiscard]] constexpr Vec2 lerp(const Vec2& o, double t) const noexcept {
    return *this + (o - *this) * t;
  }
};

// ─────────────────────────────────────────────────────────────
// Free functions
// ─────────────────────────────────────────────────────────────

/// Allow scalar * vector (in addition to vector * scalar)
[[nodiscard]] constexpr Vec2 operator*(Scalar auto s, const Vec2& v) noexcept { 
  return Vec2{v.x * s, v.y * s}; 
}

} // namespace sim

#endif // SIM_VEC2_HPP
