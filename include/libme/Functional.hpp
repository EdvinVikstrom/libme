#ifndef LIBME_FUNCTIONAL_HPP
  #define LIBME_FUNCTIONAL_HPP

#include "libme/Utility.hpp"

namespace me {

  template<typename Type>
  struct less {
    constexpr bool operator()(const Type &lhs, const Type &rhs) const;
  };

  template<>
  struct less<void> {
    template<typename Type1, typename Type2>
    constexpr auto operator()(Type1 &&lhs, Type2 &&rhs) const
      -> decltype(forward<Type1>(lhs) < forward<Type2>(rhs));
  };

}

template<typename Type>
constexpr bool me::less<Type>::operator()(const Type &lhs, const Type &rhs) const
{
  return lhs < rhs;
}

template<typename Type1, typename Type2>
constexpr auto me::less<void>::operator()(Type1 &&lhs, Type2 &&rhs) const
  -> decltype(forward<Type1>(lhs) < forward<Type2>(rhs))
{
  return forward<Type1>(lhs) < forward<Type2>(rhs);
}

#endif
