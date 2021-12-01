#ifndef LIBME_UTILITY_HPP
  #define LIBME_UTILITY_HPP

#include "libme/TypeTraits.hpp"

#include <memory>

namespace me {

  template<typename T>
  constexpr T min(T a, T b);

  template<typename T>
  constexpr T max(T a, T b);

  template<typename C>
  constexpr bool is_digit(C chr);

  template<typename C>
  constexpr bool is_ascii(C chr);

  template<typename T>
  constexpr T* to_address(T* ptr);

  template<typename T>
  constexpr T* to_address(const T &val);

  template<typename T>
  constexpr T&& forward(typename remove_reference<T>::type &val);

  template<typename T>
  constexpr T&& forward(typename remove_reference<T>::type &&val);

  template<typename T>
  constexpr typename remove_reference<T>::type&& move(T &&val);

  template<typename T>
  constexpr void swap(T &a, T &b)
    noexcept
    requires is_move_constructible<T>::value && is_move_assignable<T>::value;

  template<typename T>
  constexpr void swap_ranges(T* begin, T* end, T* with);

  template<typename T>
  constexpr void fill(T* data, size_t num, const T &val);

  template<typename T>
  constexpr bool in_range(T* ptr, T* first, T* last);

} // namespace me

template<typename T>
constexpr T
  me::min(T a, T b)
{
  return a < b ? a : b;
}

template<typename T>
constexpr T
  me::max(T a, T b)
{
  return a > b ? a : b;
}

template<typename C>
constexpr bool
  me::is_digit(C chr)
{
  return chr >= C('0') && chr <= C('9');
}

template<typename C>
constexpr bool
  me::is_ascii(C chr)
{
  return (chr >= C('A') && chr <= C('Z')) || (chr >= C('a') && chr <= C('z'));
}

template<typename T>
constexpr T*
  me::to_address(T* ptr)
{
  static_assert(!std::is_function<T>::value);
  return ptr;
}

template<typename T>
constexpr T*
  me::to_address(const T &val)
{
  if constexpr (requires{std::pointer_traits<T>::to_address(val);})
    return std::pointer_traits<T>::pointer_to(val);
  else
    return val.operator->();
}

template<typename T>
constexpr T&&
  me::forward(typename remove_reference<T>::type &val)
{
  return static_cast<T&&>(val);
}

template<typename T>
constexpr T&&
  me::forward(typename remove_reference<T>::type &&val)
{
  return static_cast<T&&>(val);
}

template<typename T>
constexpr typename me::remove_reference<T>::type&&
  me::move(T &&val)
{
  return static_cast<typename remove_reference<T>::type&&>(val);
}

template<typename T>
constexpr void
  me::swap(T &a, T &b)
  noexcept
  requires is_move_constructible<T>::value && is_move_assignable<T>::value
{
  T tmp(move(a));
  a = move(b);
  b = move(tmp);
}

template<typename T>
constexpr void
  me::swap_ranges(T* begin, T* end, T* with)
{
  while (begin != end)
    swap(*begin++, *with++);
}

template<typename T>
constexpr void
  me::fill(T* data, size_t num, const T &val)
{
  for (size_t i = 0; i != num; i++)
    data[i] = val;
}

template<typename T>
constexpr bool
  me::in_range(T* ptr, T* first, T* last)
{
  return ptr >= first && ptr < last;
}

#endif
