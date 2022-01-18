#ifndef LIBME_FUNCTIONAL_HPP
  #define LIBME_FUNCTIONAL_HPP

#define Unspecified int

#include "libme/TypeTraits.hpp"
#include "libme/Compare.hpp"

namespace me {

  template<typename F, typename... Args>
  constexpr InvokeResult_T<F, Args...> invoke(F &&f, Args&& ...args)
    noexcept(is_nothrow_invocable_v<F, Args...>);

  template<typename R, typename F, typename... Args>
  constexpr R invoke_r(F &&f, Args&& ...args)
    noexcept(is_nothrow_invocable_r_v<R, F, Args...>);

  //template<typename T> class ReferenceWrapper;

  //template<typename T> constexpr ReferenceWrapper<T> ref(T&) noexcept;
  //template<typename T> constexpr ReferenceWrapper<const T> cref(const T&) noexcept;
  //template<typename T> constexpr void ref(const T&&) = delete;
  //template<typename T> constexpr void cref(const T&&) = delete;

  //template<typename T> constexpr ReferenceWrapper<T> ref(ReferenceWrapper<T>) noexcept;
  //template<typename T> constexpr ReferenceWrapper<const T> cref(ReferenceWrapper<T>) noexcept;

  // arithmeitc operations

  template<typename T = void> struct Plus;
  template<typename T = void> struct Minus;
  template<typename T = void> struct Multiplies;
  template<typename T = void> struct Divides;
  template<typename T = void> struct Modulus;
  template<typename T = void> struct Negate;
  template<> struct Plus<void>;
  template<> struct Minus<void>;
  template<> struct Multiplies<void>;
  template<> struct Divides<void>;
  template<> struct Modulus<void>;
  template<> struct Negate<void>;

  // comparisons

  template<typename T = void> struct EqualTo;
  template<typename T = void> struct NotEqualTo;
  template<typename T = void> struct Greater;
  template<typename T = void> struct Less;
  template<typename T = void> struct GreaterEqual;
  template<typename T = void> struct LessEqual;
  template<> struct EqualTo<void>;
  template<> struct NotEqualTo<void>;
  template<> struct Greater<void>;
  template<> struct Less<void>;
  template<> struct GreaterEqual<void>;
  template<> struct LessEqual<void>;

  // logical operations

  template<typename T = void> struct LogicalAnd;
  template<typename T = void> struct LogicalOr;
  template<typename T = void> struct LogicalNot;
  template<> struct LogicalAnd<void>;
  template<> struct LogicalOr<void>;
  template<> struct LogicalNot<void>;

  // bitwise operations

  template<typename T = void> struct BitAnd;
  template<typename T = void> struct BitOr;
  template<typename T = void> struct BitXor;
  template<typename T = void> struct BitNot;
  template<> struct BitAnd<void>;
  template<> struct BitOr<void>;
  template<> struct BitXor<void>;
  template<> struct BitNot<void>;

  struct Identity;

  //template<typename F> constexpr Unspecified not_fn(F &&f);

  //template<typename F, typename... Args> constexpr Unspecified bind_front(F&&, Args&&...);

  //template<typename T> struct IsBindExpression;
  //template<typename T> inline constexpr bool is_bind_expression_v = IsBindExpression<T>::value;

  //template<typename T> struct IsPlaceholder;
  //template<typename T> inline constexpr bool is_placeholder_v = IsPlaceholder<T>::value;

  //template<typename F, typename... BoundArgs> constexpr Unspecified bind(F&&, BoundArgs&&...);
  //template<typename R, typename F, typename... BoundArgs> constexpr Unspecified bind(F&&, BoundArgs&&...);

  //namespace placeholders {
  //} // namespace placeholders

  //template<typename R, typename T> constexpr Unspecified mem_fn(R T::*) noexcept;

  //class BadFunctionCall;

  //template<typename> class Function;
  //template<typename R, typename... ArgTypes> class Function<R(ArgTypes...)>;

  namespace ranges {

    struct EqualTo;
    struct NotEqualTo;
    struct Greater;
    struct Less;
    struct GreaterEqual;
    struct LessEqual;

  }

} // namespace me
// Implementations:

/* Plus-Impl */
template<typename T>
struct me::Plus {
  constexpr T operator()(const T &x, const T &y) { return x + y; }
};

template<>
struct me::Plus<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) + forward<U>(u))
  { return forward<T>(t) + forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* Minus-Impl */
template<typename T>
struct me::Minus {
  constexpr T operator()(const T &x, const T &y) { return x - y; }
};

template<>
struct me::Minus<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) - forward<U>(u))
  { return forward<T>(t) - forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* Multiplies-Impl */
template<typename T>
struct me::Multiplies {
  constexpr T operator()(const T &x, const T &y) { return x * y; }
};

template<>
struct me::Multiplies<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) * forward<U>(u))
  { return forward<T>(t) * forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* Divides-Impl */
template<typename T>
struct me::Divides {
  constexpr T operator()(const T &x, const T &y) { return x / y; }
};

template<>
struct me::Divides<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) / forward<U>(u))
  { return forward<T>(t) / forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* Modulus-Impl */
template<typename T>
struct me::Modulus {
  constexpr T operator()(const T &x, const T &y) { return x % y; }
};

template<>
struct me::Modulus<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) % forward<U>(u))
  { return forward<T>(t) % forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* Negate-Impl */
template<typename T>
struct me::Negate {
  constexpr T operator()(const T &x) { return -x; }
};

template<>
struct me::Negate<void> {
  template<typename T>
  constexpr auto operator()(T &&t) const
    -> decltype(-forward<T>(t))
  { return -forward<T>(t); }

  using IsTransparent = Unspecified;
};

/* EqualTo-Impl */
template<typename T>
struct me::EqualTo {
  constexpr T operator()(const T &x, const T &y) { return x == y; }
};

template<>
struct me::EqualTo<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) == forward<U>(u))
  { return forward<T>(t) == forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* NotEqualTo-Impl */
template<typename T>
struct me::NotEqualTo {
  constexpr T operator()(const T &x, const T &y) { return x != y; }
};

template<>
struct me::NotEqualTo<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) != forward<U>(u))
  { return forward<T>(t) != forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* Greater-Impl */
template<typename T>
struct me::Greater {
  constexpr T operator()(const T &x, const T &y) { return x > y; }
};

template<>
struct me::Greater<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) > forward<U>(u))
  { return forward<T>(t) > forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* Less-Impl */
template<typename T>
struct me::Less {
  constexpr T operator()(const T &x, const T &y) { return x < y; }
};

template<>
struct me::Less<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) < forward<U>(u))
  { return forward<T>(t) < forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* GreaterEqual-Impl */
template<typename T>
struct me::GreaterEqual {
  constexpr T operator()(const T &x, const T &y) { return x >= y; }
};

template<>
struct me::GreaterEqual<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) >= forward<U>(u))
  { return forward<T>(t) >= forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* LessEqual-Impl */
template<typename T>
struct me::LessEqual {
  constexpr T operator()(const T &x, const T &y) { return x <= y; }
};

template<>
struct me::LessEqual<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) <= forward<U>(u))
  { return forward<T>(t) <= forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* LogicalAnd-Impl */
template<typename T>
struct me::LogicalAnd {
  constexpr bool operator()(const T &x, const T &y) { return x && y; }
};

template<>
struct me::LogicalAnd<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) && forward<U>(u))
  { return forward<T>(t) && forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* LogicalOr-Impl */
template<typename T>
struct me::LogicalOr {
  constexpr bool operator()(const T &x, const T &y) { return x || y; }
};

template<>
struct me::LogicalOr<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, U &&u) const
    -> decltype(forward<T>(t) || forward<U>(u))
  { return forward<T>(t) || forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* LogicalNot-Impl */
template<typename T>
struct me::LogicalNot {
  constexpr bool operator()(const T &x) { return !x; }
};

template<>
struct me::LogicalNot<void> {
  template<typename T>
  constexpr auto operator()(T &&t) const
    -> decltype(!forward<T>(t))
  { return !forward<T>(t); }

  using IsTransparent = Unspecified;
};

/* BitAnd-Impl */
template<typename T>
struct me::BitAnd {
  constexpr T operator()(const T &x, const T &y) { return x & y; }
};

template<>
struct me::BitAnd<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) & forward<U>(u))
  { return forward<T>(t) & forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* BitOr-Impl */
template<typename T>
struct me::BitOr {
  constexpr T operator()(const T &x, const T &y) { return x | y; }
};

template<>
struct me::BitOr<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) | forward<U>(u))
  { return forward<T>(t) | forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* BitXor-Impl */
template<typename T>
struct me::BitXor {
  constexpr T operator()(const T &x, const T &y) { return x ^ y; }
};

template<>
struct me::BitXor<void> {
  template<typename T, typename U>
  constexpr auto operator()(T &&t, T &&u) const
    -> decltype(forward<T>(t) ^ forward<U>(u))
  { return forward<T>(t) ^ forward<U>(u); }

  using IsTransparent = Unspecified;
};

/* BitNot-Impl */
template<typename T>
struct me::BitNot {
  constexpr T operator()(const T &x) { return ~x; }
};

template<>
struct me::BitNot<void> {
  template<typename T>
  constexpr auto operator()(T &&t) const
    -> decltype(~forward<T>(t))
  { return ~forward<T>(t); }

  using IsTransparent = Unspecified;
};

/* Identity-Impl */
struct me::Identity {
  template<typename T>
  constexpr T&& operator()(T &&t) const noexcept
  {
    return forward<T>(t);
  }

  using IsTransparent = Unspecified;
};

/* ranges::EqualTo-Impl */
struct me::ranges::EqualTo {
  template<typename T, typename U>
  constexpr bool operator()(T &&t, U &&u) const
    noexcept(noexcept(bool(forward<T>(t) == forward<U>(u))))
  {
    return forward<T>(t) == forward<U>(u);
  }

  using IsTransparent = Unspecified;
};

/* ranges::NotEqualTo-Impl */
struct me::ranges::NotEqualTo {
  template<typename T, typename U>
  constexpr bool operator()(T &&t, U &&u) const
    noexcept(noexcept(bool(!(forward<T>(t) == forward<U>(u)))))
  {
    return !(forward<T>(t) == forward<U>(u));
  }

  using IsTransparent = Unspecified;
};

/* ranges::Greater-Impl */
struct me::ranges::Greater {
  template<typename T, typename U>
  constexpr bool operator()(T &&t, U &&u) const
    noexcept(noexcept(bool(forward<T>(u) < forward<U>(t))))
  {
    return forward<T>(u) < forward<U>(t);
  }

  using IsTransparent = Unspecified;
};

/* ranges::Less-Impl */
struct me::ranges::Less {
  template<typename T, typename U>
  constexpr bool operator()(T &&t, U &&u) const
    noexcept(noexcept(bool(forward<T>(t) < forward<U>(u))))
  {
    return forward<T>(t) < forward<U>(u);
  }

  using IsTransparent = Unspecified;
};

/* ranges::GreaterEqual-Impl */
struct me::ranges::GreaterEqual {
  template<typename T, typename U>
  constexpr bool operator()(T &&t, U &&u) const
    noexcept(noexcept(bool(!(forward<T>(u) < forward<U>(t)))))
  {
    return !(forward<T>(u) < forward<U>(t));
  }

  using IsTransparent = Unspecified;
};

/* ranges::LessEqual-Impl */
struct me::ranges::LessEqual {
  template<typename T, typename U>
  constexpr bool operator()(T &&t, U &&u) const
    noexcept(noexcept(bool(!(forward<T>(t) < forward<U>(u)))))
  {
    return !(forward<T>(t) < forward<U>(u));
  }

  using IsTransparent = Unspecified;
};

#endif // LIBME_FUNCTIONAL_HPP
