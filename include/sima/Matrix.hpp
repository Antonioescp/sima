#ifndef SIMA_MATRIX_H
#define SIMA_MATRIX_H

#include <concepts>
#include <span>

#include <sima/Concepts.hpp>

namespace Sima {

  // TODO Document
  template <std::size_t ROWS, std::size_t COLUMNS, std::floating_point T>
  class Matrix {
    public:

      static Matrix Identity() {
        Matrix result;
        for (std::size_t row{}; row < ROWS; ++row) {
          for (std::size_t column{}; column < COLUMNS; ++column) {
            if (row == column) {
              result(row, column) = 1;
            } 
          }
        }
      }

      Matrix() = default;

      Matrix(std::span<T, ROWS * COLUMNS> values) {
        constexpr std::size_t size{ROWS * COLUMNS};
        for (std::size_t i{}; i < size; ++i) {
          items[i] = values[i];
        }
      }

      Matrix operator+(const Matrix& other) const {
        Matrix result{*this};
        for (std::size_t i{}; i < ROWS * COLUMNS; ++i) {
          result.items[i] += other.items[i];
        }
        return result;
      }

      Matrix& operator+=(const Matrix& other) {
        for (std::size_t i{}; i < ROWS * COLUMNS; ++i) {
          items[i] += other.items[i];
        }
        return *this;
      }
    
      Matrix operator-() const {
        Matrix result{*this};
        for (std::size_t i{}; i < ROWS * COLUMNS; ++i) {
          result.items[i] = -result.items[i];
        }
        return result;
      }

      Matrix operator-(const Matrix& other) const {
        Matrix result{*this};
        for (std::size_t i{}; i < ROWS * COLUMNS; ++i) {
          result.items[i] -= other.items[i];
        }
        return result;
      }

      Matrix& operator-=(const Matrix& other) {
        for (std::size_t i{}; i < ROWS * COLUMNS; ++i) {
          items[i] -= other.items[i];
        }
        return *this;
      }

      Matrix operator*(const Number auto scalar) const {
        Matrix result{*this};
        for (std::size_t i{}; i < ROWS * COLUMNS; ++i) {
          result.items[i] *= scalar;
        }
        return result;
      }

      Matrix& operator*=(const Number auto scalar) {
        for (std::size_t i{}; i < ROWS * COLUMNS; ++i) {
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

        for (std::size_t row{}; row < ROWS; ++row) {
          for (std::size_t column{}; column < OCOLUMNS; ++column) {
            PromotedType sum{};
            for (std::size_t operation{}; operation < ROWS; ++operation) {
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
        for (std::size_t row{}; row < ROWS; ++row) {
          for (std::size_t column{}; column < COLUMNS; ++column) {
            result(column, row) = items[getIndex(row, column)];
          }
        }
        return result;
      }

    private:
      T* items[ROWS * COLUMNS]{};
      
      static inline std::size_t getIndex(const std::size_t row, const std::size_t column) {
        return row * COLUMNS + column;
      }
  };
}

#endif
