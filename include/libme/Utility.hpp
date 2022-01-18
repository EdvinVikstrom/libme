#ifndef LIBME_UTILITY_HPP
  #define LIBME_UTILITY_HPP

#include "libme/Compare.hpp"
#include "libme/InitializerList.hpp"
#include "libme/Limits.hpp"

namespace me {

  template<typename T>
  constexpr void swap(T &a, T &b)
    noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>)
    requires is_move_constructible_v<T> && is_move_assignable_v<T>;

  template<typename T, size_t N>
  constexpr void swap(T (&a)[N], T (&b)[N])
    noexcept(is_nothrow_swappable_v<T>)
    requires is_swappable_v<T>;

  template<typename T, typename U = T>
  constexpr T exchange(T &obj, U &&new_val)
    noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_assignable_v<T&, U>);

  template<typename T>
  constexpr T&& forward(RemoveReference_T<T> &t) noexcept;

  template<typename T>
  constexpr T&& forward(RemoveReference_T<T> &&t) noexcept;

  template<typename T>
  constexpr RemoveReference_T<T>&& move(T &&t) noexcept;

  template<typename T>
  constexpr Conditional_T<!is_nothrow_move_constructible_v<T> && is_copy_constructible_v<T>, const T&, T&&>
    move_if_noexcept(T &x) noexcept;

  template<typename T>
  constexpr AddConst_T<T>& as_const(T &t) noexcept;

  template<typename T>
  constexpr void as_const(const T&&) = delete;

  template<typename T>
  AddRValueReference_T<T> declval() noexcept;

  template<typename T, typename U>
  constexpr bool cmp_equal(T t, U u) noexcept;

  template<typename T, typename U>
  constexpr bool cmp_not_equal(T t, U u) noexcept;

  template<typename T, typename U>
  constexpr bool cmp_less(T t, U u) noexcept;

  template<typename T, typename U>
  constexpr bool cmp_greater(T t, U u) noexcept;

  template<typename T, typename U>
  constexpr bool cmp_less_equal(T t, U u) noexcept;

  template<typename T, typename U>
  constexpr bool cmp_greater_equal(T t, U u) noexcept;

  template<typename R, typename T>
  constexpr bool in_range(T t) noexcept;

  template<typename T>
  constexpr UnderlyingType_T<T> to_underlying(T value) noexcept;

  template<typename T, T...>
  class IntegerSequence;

  template<size_t... I>
  using IndexSequence = IntegerSequence<size_t, I...>;

  template<typename T, T N>
  using MakeIntegerSequence = IntegerSequence<T, 0>;

  template<size_t N>
  using MakeIndexSequence = MakeIntegerSequence<size_t, N>;

  template<typename... T>
  using IndexSequenceFor = MakeIndexSequence<sizeof...(T)>;

  /* +------------------------------+ */
  /* |            Tuple             | */
  /* +------------------------------+ */

  // TODO: tuple stuff under here:

  struct PiecewiseConstruct_T {
    explicit PiecewiseConstruct_T() = default;
  };
  inline constexpr PiecewiseConstruct_T piecewise_construct { };

  template<typename... Types>
  class Tuple; // defined in "libme/Tuple.hpp"

  struct InPlace_T {
    explicit InPlace_T() = default;
  };
  inline constexpr InPlace_T in_place { };

  template<typename T>
  struct InPlaceType_T {
    explicit InPlaceType_T() = default;
  };
  template<typename T> inline constexpr InPlaceType_T<T> in_place_type { };

  template<size_t I>
  struct InPlaceIndex_T {
    explicit InPlaceIndex_T() = default;
  };
  template<size_t I> inline constexpr InPlaceIndex_T<I> in_place_index { };

} // namespace me
// Implementations:

/* class me::IntegerSequence */

template<typename T, T... Vals>
class me::IntegerSequence {

  /* Types */
public:

  typedef T ValueType;

  /* Functions */
public:

  static constexpr size_t length() noexcept
  {
    return sizeof...(Vals);
  }

};

/* end class me::IntegerSequence */

template<typename T>
constexpr void
  me::swap(T &a, T &b)
  noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>)
  requires is_move_constructible_v<T> && is_move_assignable_v<T>
{
  T tmp(move(a));
  a = move(b);
  b = move(tmp);
}

template<typename T, me::size_t N>
constexpr void
  me::swap(T (&a)[N], T (&b)[N])
  noexcept(is_nothrow_swappable_v<T>)
  requires is_swappable_v<T>
{
  for (size_t i = 0; i != N; i++) // TODO
    swap(a[i], b[i]);
}

template<typename T, typename U>
constexpr T
  me::exchange(T &obj, U &&new_val)
  noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_assignable_v<T&, U>)
{
  T old = move(obj);
  obj = forward<U>(new_val);
  return old;
}

template<typename T>
constexpr T&&
  me::forward(RemoveReference_T<T> &t)
  noexcept
{
  return static_cast<T&&>(t);
}

template<typename T>
constexpr T&&
  me::forward(RemoveReference_T<T> &&t)
  noexcept
{
  return static_cast<T&&>(t);
}

template<typename T>
constexpr me::RemoveReference_T<T>&&
  me::move(T &&t)
  noexcept
{
  return static_cast<RemoveReference_T<T>&&>(t);
}

namespace me { // Why do we need to have namespace here? Stupid C++...
  template<typename T>
  constexpr Conditional_T<!is_nothrow_move_constructible_v<T> && is_copy_constructible_v<T>, const T&, T&&>
    move_if_noexcept(T &x)
    noexcept
  {
    if constexpr (noexcept(move(x)))
      return move(x);
    return x;
  }
}

template<typename T>
constexpr me::AddConst_T<T>&
  me::as_const(T &t)
  noexcept
{
  return t;
}

template<typename T, typename U>
constexpr bool
  me::cmp_equal(T t, U u)
  noexcept
{
  using UnsignedT = MakeUnsigned_T<T>;
  using UnsignedU = MakeUnsigned_T<U>;

  if constexpr (is_signed_v<T> == is_signed_v<U>)
    return t == u;
  else if constexpr (is_signed_v<T>)
    return t < 0 ? false : UnsignedT(t) == u;
  else
    return u < 0 ? false : t == UnsignedU(u);
}

template<typename T, typename U>
constexpr bool
  me::cmp_not_equal(T t, U u)
  noexcept
{
  return !cmp_equal(t, u);
}

template<typename T, typename U>
constexpr bool
  me::cmp_less(T t, U u)
  noexcept
{
  using UnsignedT = MakeUnsigned_T<T>;
  using UnsignedU = MakeUnsigned_T<U>;

  if constexpr (is_signed_v<T> == is_signed_v<U>)
    return t < u;
  else if constexpr (is_signed_v<T>)
    return t < 0 ? false : UnsignedT(t) < u;
  else
    return u < 0 ? false : t < UnsignedU(u);
}

template<typename T, typename U>
constexpr bool
  me::cmp_greater(T t, U u)
  noexcept
{
  return cmp_less(u, t);;
}

template<typename T, typename U>
constexpr bool
  me::cmp_less_equal(T t, U u)
  noexcept
{
  return !cmp_greater(t, u);
}

template<typename T, typename U>
constexpr bool
  me::cmp_greater_equal(T t, U u)
  noexcept
{
  return !cmp_less(t, u);
}

template<typename R, typename T>
constexpr bool
  me::in_range(T t)
  noexcept
{
  return cmp_greater_equal(t, NumericLimits<R>::min()) && cmp_less_equal(t, NumericLimits<R>::max());
}

#endif // LIBME_UTILITY_HPP
