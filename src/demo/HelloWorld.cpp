#include <iostream>
#include <concepts>

#include <sima/Vector4.hpp>
#include <sima/Matrix.hpp>

using namespace Sima;

template <std::size_t ROWS, std::size_t COLUMNS>
void print(const Matrix<ROWS, COLUMNS>& matrix) {
    for ( std::size_t row{}; row < 4; ++row ) {
        for ( std::size_t column{}; column < 4; ++column ) {
            std::cout << matrix(row, column) << '\t';
        }
        std::cout << '\n';
    }
}

template <std::floating_point T = float>
void print(const Vector4<T>& vec) {
    std::cout << '\n'
              << '<' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ">\n";
}

int main() {
    std::array<float, 16> data{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        1, 1, 1, 1
    };

    Matrix<4, 4> translationColumn{ data };
    auto translationRow{ ~translationColumn };

    print(translationColumn);
    std::cout << '\n';
    print(translationRow);

    Vector4 pos{ 1.0f, 1.0f, 1.0f, 1.0f };
    Vector4 res1{ pos * translationRow };
    Vector4 res2{ translationColumn * pos };

    print(pos);
    print(res1);
    print(res2);

    return 0;
}
