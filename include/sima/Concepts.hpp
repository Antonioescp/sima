#ifndef SIMA_CONCEPTS_H
#define SIMA_CONCEPTS_H

#include <concepts>

namespace Sima {

    // TODO Document
    template <typename T>
    concept Number = (std::floating_point<T> || std::integral<T>) && !std::same_as<T, char> && !std::same_as<T, bool>;
}

#endif
