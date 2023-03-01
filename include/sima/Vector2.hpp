#ifndef SIMA_VECTOR2_H
#define SIMA_VECTOR2_H

#include <concepts>
#include <cmath>

#include <sima/Concepts.hpp>

namespace Sima {
  template <std::floating_point T = float>
  struct Vector2 {
    T x{};
    T y{};

    Vector2() = default;
    Vector2(T x, T y) : x{x}, y{y} {}

    Vector2 operator+(const Vector2& other) const {
      return { x + other.x, y + other.y };
    }

    Vector2& operator+=(const Vector2& other) {
      x += other.x;
      y += other.y;
      return *this;
    }

    Vector2 operator-(const Vector2& other) const {
      return { x - other.x, y - other.y };
    }

    Vector2& operator-=(const Vector2& other) {
      x -= other.x;
      y -= other.y;
      return *this;
    }
    
    Vector2 operator*(const Vector2& other) const {
      return { x * other.x, y * other.y };
    }

    Vector2& operator*=(const Vector2& other) {
      x *= other.x;
      y *= other.y;
      return *this;
    }

    Vector2 operator*(const Number auto scalar) const {
      return { x * scalar, y * scalar };
    }

    Vector2& operator*=(const Number auto scalar) {
      x *= scalar;
      y *= scalar;
      return *this;
    }

    Vector2 operator/(const Number auto scalar) const {
      return { x / scalar, y / scalar };
    }

    Vector2& operator/=(const Number auto scalar) {
      x /= scalar;
      y /= scalar;
      return *this;
    }

    T dot(const Vector2& other) const {
      return x * other.x + y * other.y;
    }

    T squareMagnitude() const {
      return x * x + y * y;
    }

    T magnitude() const {
      return std::sqrt(x * x + y * y);
    }

    Vector2 normalized() const {
      return Vector2{*this} / magnitude();
    }

    Vector2& normalize() {
      return *this /= magnitude();
    }
    
  };
}
#endif
