#ifndef LIBME_CSTRING_HPP
  #define LIBME_CSTRING_HPP

#include "TypeTraits.hpp"

namespace me {

  template<typename Char>
  constexpr size_t strlen(const Char* str);

  template<typename Char>
  constexpr int strcmp(const Char* lhs, const Char* rhs);

} // namespace me

template<typename Char>
constexpr me::size_t me::strlen(const Char* str)
{
  size_t len = 0;
  while (str[len] != Char('\0'))
    len++;
  return len;
}

template<typename Char>
constexpr int me::strcmp(const Char* lhs, const Char* rhs)
{
  typedef typename make_unsigned<Char>::type UChar;

  UChar c1, c2;

  do {
    c1 = static_cast<UChar>(*lhs++);
    c2 = static_cast<UChar>(*rhs++);
    if (c1 == Char('\0'))
      return c1 - c2;
  }while (c1 == c2);
  return c1 - c2;
}

#endif
