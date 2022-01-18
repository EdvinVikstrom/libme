#ifndef LIBME_BITS_TYPE_UTILITY_HPP
  #define LIBME_BITS_TYPE_UTILITY_HPP

#include "libme/TypeTraits.hpp"

namespace me {

  template<typename T>
  constexpr T __decay_copy(const T &t)
  {
    return Decay_T<T>(t);
  }

}

#endif // LIBME_BITS_TYPE_UTILITY_HPP
