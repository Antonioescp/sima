#ifndef SIMA_VECTOR4_H
#define SIMA_VECTOR4_H

#include <cmath>
#include <concepts>

#include <sima/Concepts.hpp>
#include <sima/Vector3.hpp>

namespace Sima {
  
  // TODO Document
  template <std::floating_point T>
  struct Vector4 {
    T x{};
    T y{};
    T z{};
    T w{};

    Vector4() = default;
    Vector4(T x, T y, T z, T w) : x{x}, y{y}, z{z}, w{w} {}
    explicit Vector4(const Vector3<T>& other) : x{other.x}, y{other.y}, z{other.z}, w{} {}

    Vector4 operator+(const Vector4& other) const {
      return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    Vector4& operator+=(const Vector4& other) {
      x += other.x;
      y += other.y;
      z += other.z;
      return *this;
    }

    Vector4 operator-(const Vector4& other) const {
      return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    Vector4& operator-=(const Vector4& other) {
      x -= other.x;
      y -= other.y;
      z -= other.z;
      w -= other.w;
      return *this;
    }

    Vector4 operator*(Number auto scalar) const {
      return { x * scalar, y * scalar, z * scalar, w * scalar };
    }

    Vector4& operator*=(Number auto scalar) {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      w *= scalar;
      return *this;
    }

    Vector4 operator/(Number auto scalar) const {
      return { x / scalar, y / scalar, z / scalar, w / scalar };
    }

    Vector4& operator/=(Number auto scalar) {
      x /= scalar;
      y /= scalar;
      z /= scalar;
      w /= scalar;
      return *this;
    }

    Vector4 operator*(const Vector4& other) const {
      return { x * other.x, y * other.y, z * other.z, w * other.w };
    }

    Vector4& operator*=(const Vector4& other) {
      x *= other.x;
      y *= other.y;
      z *= other.z;
      w *= other.w;
      return *this;
    }

    T dot(const Vector4& other) const {
      return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    T squareMagnitude() const {
      return x * x + y * y + z * z + w * w;
    }

    T magnitude() const {
      return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Vector4 normalized() const {
      return Vector4{*this} / magnitude();
    }

    Vector4& normalize() {
      return *this /= magnitude();
    }

  };

}

#endif
