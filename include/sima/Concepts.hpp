#ifndef SIMA_CONCEPTS_H
#define SIMA_CONCEPTS_H

#include <algorithm>
#include <concepts>

namespace Sima {

    // TODO Document
    template <typename T>
    concept Number = (std::floating_point<T> || std::integral<T>) && !std::same_as<T, char> && !std::same_as<T, bool>;

    // TODO Document
    template <std::size_t ROWS, std::size_t COLUMNS, std::size_t DIMENSIONS = std::max(ROWS, COLUMNS)> 
    concept Vector = (ROWS == 1 && COLUMNS == DIMENSIONS) || (ROWS == DIMENSIONS && COLUMNS == 1);
}

#endif
