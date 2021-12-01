#ifndef LIBME_STRING_UTIL_HPP
  #define LIBME_STRING_UTIL_HPP

#include "../utility.hpp"

#include <type_traits>

namespace me {

  // ---------- INTEGER ---------- //

  /* converts a string to a integer */
  template<typename T, typename Char> [[nodiscard]] constexpr T strint(const Char* str, uint8_t base = 10) requires std::is_integral_v<T>;
  template<typename T, typename Char> [[nodiscard]] constexpr T strint(const Char* begin, const Char* end, uint8_t base = 10) requires std::is_integral_v<T>;

  /* creates a integer string from a integer */
  template<typename T, typename Char> constexpr void intstr(T i, Char* buffer, uint8_t base = 10) requires std::is_integral_v<T>;


  // ---------- FLOATING POINT ---------- //

  /* converts a string to a float */
  template<typename T, typename Char> [[nodiscard]] constexpr T strfloat(const Char* str, uint8_t base = 10) requires std::is_floating_point_v<T>;
  template<typename T, typename Char> [[nodiscard]] constexpr T strfloat(const Char* begin, const Char* end, uint8_t base = 10) requires std::is_floating_point_v<T>;

  /* creates a float string from a float */
  template<typename T, typename Char> constexpr void floatstr(T f, Char* buffer, uint8_t base = 10) requires std::is_floating_point_v<T>;


  /* creates a number string from a number */
  template<typename T, typename Char> constexpr void numstr(T n, Char* str, uint8_t base = 10);

  // --------- STUFF --------- //
  template<typename Char> [[nodiscard]] constexpr Char lowercase(Char chr);
  template<typename Char> [[nodiscard]] constexpr Char uppercase(Char chr);

}

template<typename T, typename Char>
constexpr T me::strint(const Char* str, uint8_t base) requires std::is_integral_v<T>
{
  T i = 0;

  while (is_digit(*str))
    i = base * i + *str++ - '0';
  return i;
}

template<typename T, typename Char>
constexpr T me::strint(const Char* begin, const Char* end, uint8_t base) requires std::is_integral_v<T>
{
  T i = 0;

  while (begin != end && is_digit(*begin))
    i = base * i + *begin++ - '0';
  return i;
}

template<typename T, typename Char>
constexpr void me::intstr(T i, Char* buffer, uint8_t base) requires std::is_integral_v<T>
{
  const Char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  Char temp[66];
  Char sign;
  int index = 0;

  if (i == 0)
  {
    *buffer++ = '0';
    return;
  }

  if constexpr (std::is_signed_v<T>)
  {
    if (i < 0)
    {
      sign = Char('-');
      i = -i;
    }else
      sign = 0;
  }else
    sign = 0;

  while (i)
  {
    T r = i % base;
    i = i / base;

    temp[index++] = chars[r];
  }

  if (sign)
    *buffer++ = sign;
  while (index)
    *buffer++ = temp[(index--) - 1];
}

template<typename T, typename Char>
constexpr void me::floatstr(T f, Char* str, uint8_t base) requires std::is_floating_point_v<T>
{
  (void) f;
  (void) str;
  (void) base;
}

template<typename T, typename Char>
constexpr void me::numstr(T n, Char* str, uint8_t base)
{
  if constexpr (std::is_integral<T>::value)
    intstr(n, str, base);
  else if constexpr (std::is_floating_point<T>::value)
    floatstr(n, str, base);
}

template<typename C>
constexpr C me::lowercase(C chr)
{
  if (chr >= 0x41 && chr <= 0x5A)
    return chr + 0x20;
  return chr;
}

template<typename C>
constexpr C me::uppercase(C chr)
{
  if (chr >= 0x61 && chr <= 0x7A)
    return chr - 0x20;
  return chr;
}

#endif
