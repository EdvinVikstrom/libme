#ifndef LIBME_ALGORITHM_HPP
  #define LIBME_ALGORITHM_HPP

#include "libme/Type.hpp"

namespace me {

  template<typename T>
  constexpr T min(T lhs, T rhs);

  template<typename T>
  constexpr T max(T lhs, T rhs);


} // namespace me

template<typename T>
constexpr T
  me::min(T lhs, T rhs)
{
  if (lhs < rhs)
    return lhs;
  return rhs;
}

template<typename T>
constexpr T
  me::max(T lhs, T rhs)
{
  if (rhs < lhs)
    return lhs;
  return rhs;
}

#endif // LIBME_ALGORITHM_HPP
