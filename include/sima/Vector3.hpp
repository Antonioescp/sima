#ifndef VECTOR3_H
#define VECTOR3_H

#include <concepts>
#include <cmath>

#include "sima/Concepts.hpp"
#include "sima/Vector2.hpp"

namespace Sima {

    // TODO Document
    template <std::floating_point T = float>
    struct Vector3 {
        T x{};
        T y{};
        T z{};

        Vector3() = default;
        Vector3(T x, T y, T z) : x{x}, y{y}, z{z} {}
        Vector3(const Vector2<T>& other) : x{other.x}, y{other.y}, z{} {}

        Vector3 operator+(const Vector3& other) const {
            return { x + other.x, y + other.y, z + other.z };
        }

        Vector3& operator+=(const Vector3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3 operator-(const Vector3& other) const {
            return { x - other.x, y - other.y, z - other.z };
        }

        Vector3& operator-=(const Vector3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }
        
        Vector3 operator*(Number auto scalar) const {
            return { x * scalar, y * scalar, z * scalar };
        }

        Vector3& operator*=(Number auto scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vector3 operator/(Number auto scalar) const {
            return { x / scalar, y / scalar, z / scalar };
        }

        Vector3& operator/=(Number auto scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        T dot(const Vector3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3 cross(const Vector3& other) const {
            return {
                .x = y * other.z - z * other.y,
                .y = z * other.x - x * other.z,
                .z = x * other.y - y * other.x
            };
        }

        Vector3& crossAssign(const Vector3& other) {
            x = y * other.z - z * other.y;
            y = z * other.x - x * other.z;
            z = x * other.y - y * other.x;
            return *this;
        }

        T squaredMagnitude() const {
            return x*x + y*y + z*z;
        }

        T magnitude() const {
            return std::sqrt(x*x + y*y + z*z);
        }

        Vector3 normalized() const {
            auto mag(magnitude());
            return Vector3{*this} / mag;
        }

        Vector3& normalize() {
            return (*this) /= magnitude();
        }

        T angleBetween(const Vector3& other) const {
            return std::acos(dot(other) / (magnitude() * other.magnitude()));
        }
    };
} // Sima

#endif
