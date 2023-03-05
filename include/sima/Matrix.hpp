#ifndef SIMA_MATRIX_H
#define SIMA_MATRIX_H

#include <concepts>
#include <span>

#include <sima/Concepts.hpp>
#include <sima/Vector4.hpp>

namespace Sima {
    // TODO(Document)
    template <std::size_t ROWS, std::size_t COLUMNS, std::floating_point T = float>
        requires (ROWS >= 1 && COLUMNS >= 1)
    class Matrix {
      public:
        static Matrix Identity()
            requires (ROWS == COLUMNS)
        {
            Matrix result;
            for ( std::size_t row{}; row < ROWS; ++row ) {
                for ( std::size_t column{}; column < COLUMNS; ++column ) {
                    if ( row == column ) {
                        result(row, column) = 1;
                    }
                }
            }
        }

        Matrix() = default;

        Matrix(std::span<T, ROWS * COLUMNS> values) {
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                items[i] = values[i];
            }
        }

        explicit Matrix(const Vector4<T>& vector)
            requires Vector<ROWS, COLUMNS, 4>
        {
            const T* values{ &vector.x };
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i, ++values ) {
                items[i] = *values;
            }
        }

        Matrix operator+(const Matrix& other) const {
            Matrix result{ *this };
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                result.items[i] += other.items[i];
            }
            return result;
        }

        Matrix& operator+=(const Matrix& other) {
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                items[i] += other.items[i];
            }
            return *this;
        }

        Matrix operator-() const {
            Matrix result{ *this };
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                result.items[i] = -result.items[i];
            }
            return result;
        }

        Matrix operator-(const Matrix& other) const {
            Matrix result{ *this };
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                result.items[i] -= other.items[i];
            }
            return result;
        }

        Matrix& operator-=(const Matrix& other) {
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                items[i] -= other.items[i];
            }
            return *this;
        }

        Matrix operator*(const Number auto scalar) const {
            Matrix result{ *this };
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                result.items[i] *= scalar;
            }
            return result;
        }

        Matrix& operator*=(const Number auto scalar) {
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i ) {
                items[i] *= scalar;
            }
            return *this;
        }

        template <std::size_t OROWS, std::size_t OCOLUMNS, std::floating_point OT>
            requires (COLUMNS == OROWS)
        auto operator*(const Matrix<OROWS, OCOLUMNS, OT>& other) const {

            using PromotedType = decltype(T{} + OT{});
            using ResultType = Matrix<ROWS, OCOLUMNS, PromotedType>;
            ResultType result;

            for ( std::size_t row{}; row < ROWS; ++row ) {
                for ( std::size_t column{}; column < OCOLUMNS; ++column ) {
                    PromotedType sum{};
                    for ( std::size_t operation{}; operation < COLUMNS; ++operation ) {
                        sum += items[getIndex(row, operation)] * other(operation, column);
                    }
                    result(row, column) = sum;
                }
            }
            return result;
        }

        T operator()(const std::size_t row, const std::size_t column) const {
            return items[getIndex(row, column)];
        }

        T& operator()(const std::size_t row, const std::size_t column) {
            return items[getIndex(row, column)];
        }

        Matrix<COLUMNS, ROWS, T> operator~() const {
            Matrix<COLUMNS, ROWS, T> result;
            for ( std::size_t row{}; row < ROWS; ++row ) {
                for ( std::size_t column{}; column < COLUMNS; ++column ) {
                    result(column, row) = items[getIndex(row, column)];
                }
            }
            return result;
        }

        Vector4<T> operator*(const Vector4<T>& other) const {
            Matrix<4, 1, T> rowVector{ other };
            return Vector4<T>(*this * rowVector);
        }

        explicit operator Vector4<T>() const
            requires Vector<ROWS, COLUMNS, 4>
        {
            Vector4<T> result;
            T* current{ &result.x };
            for ( std::size_t i{}; i < ROWS * COLUMNS; ++i, ++current ) {
                *current = items[i];
            }
            return result;
        }

      private:
        T items[ROWS * COLUMNS]{};

        static inline std::size_t getIndex(const std::size_t row, const std::size_t column) {
            return column * ROWS + row;
        }
    };

    template <std::size_t ROWS, std::size_t COLUMNS, std::floating_point T>
    Matrix<ROWS, COLUMNS, T> operator*(const Number auto scalar, const Matrix<ROWS, COLUMNS, T>& matrix) {
        return matrix * scalar;
    }

    template <std::floating_point T>
    Vector4<T> operator*(const Vector4<T>& vector, const Matrix<4, 4>& matrix) {
        Matrix<1, 4> rowVector{ vector };
        return static_cast<Vector4<T>>(rowVector * matrix);
    }
}  // namespace Sima

#endif
