#ifndef LIBME_PAIR_HPP
  #define LIBME_PAIR_HPP

#include "libme/TypeTraits.hpp"
#include "libme/Utility.hpp"
#include "libme/Compare.hpp"

namespace me {

  template<class FirstType, class SecondType>
  class Pair {

  public:

    FirstType first;
    SecondType second;

    /* explicit(...) constexpr Pair() requires ...; */
    explicit(!is_default_constructible_v<FirstType> || !is_default_constructible_v<SecondType>)
      constexpr Pair()
      requires is_default_constructible_v<FirstType> && is_default_constructible_v<SecondType>;

    /* explicit(...) constexpr Pair(const FirstType &a, const SecondType &b) requires ...; */
    explicit(!is_convertible_v<const FirstType&, FirstType> || !is_convertible_v<const SecondType&, SecondType>)
      constexpr Pair(const FirstType &a, const SecondType &b)
      requires is_copy_constructible_v<FirstType> && is_copy_constructible_v<SecondType>;

    /* template<...> explicit(...) constexpr Pair(F2 &&a, S2 &&b) requires ...; */
    template<typename F2 = FirstType, typename S2 = SecondType>
    explicit(!is_convertible_v<F2&&, FirstType> || !is_convertible_v<S2&&, SecondType>)
      constexpr Pair(F2 &&a, S2 &&b)
      requires is_constructible_v<FirstType, F2&&> && is_constructible_v<SecondType, S2&&>;

    /* template<...> explicit(...) constexpr Pair(const Pair<F2, S2> &pair) requires ...; */
    template<typename F2, typename S2>
    explicit(!is_convertible_v<const F2&, FirstType> || !is_convertible_v<const S2&, SecondType>)
      constexpr Pair(const Pair<F2, S2> &pair)
      requires is_constructible_v<FirstType, const F2&> && is_constructible_v<SecondType, const S2&>;

    /* template<...> explicit(...) constexpr Pair(Pair<F2, S2> &&pair) requires ...; */
    template<typename F2, typename S2>
    explicit(!is_convertible_v<F2&&, FirstType> || !is_convertible_v<S2&&, SecondType>)
      constexpr Pair(Pair<F2, S2> &&pair)
      requires is_constructible_v<FirstType, F2&&> && is_constructible_v<SecondType, S2&&>;

    constexpr Pair(const Pair &pair) = default;
    constexpr Pair(Pair &&pair) = default;

    /* constexpr Pair& operator=(const Pair &pair) requires ...; */
    constexpr Pair& operator=(const Pair &pair) = delete;
    constexpr Pair& operator=(const Pair &pair)
      requires is_copy_assignable_v<FirstType> && is_copy_assignable_v<SecondType>;

    /* template<...> constexpr Pair& operator=(const Pair<F2, S2> &pair) requires ...; */
    template<typename F2, typename S2>
    constexpr Pair& operator=(const Pair<F2, S2> &pair)
      requires is_assignable_v<FirstType&, const F2&> && is_assignable_v<SecondType&, const S2&>;

    /* constexpr Pair& operator=(Pair &&pair) noexcept(...) requires ...; */
    constexpr Pair& operator=(Pair &&pair)
      noexcept(is_nothrow_move_assignable_v<FirstType> && is_nothrow_move_assignable_v<SecondType>)
      requires is_move_assignable_v<FirstType> && is_move_assignable_v<SecondType>;

    /* template<...> constexpr Pair& operator=(Pair<F2, S2> &&pair) requires ...; */
    template<typename F2, typename S2>
    constexpr Pair& operator=(Pair<F2, S2> &&pair)
      requires is_assignable_v<FirstType&, F2> && is_assignable_v<SecondType&, S2>;

    /* constexpr void swap(Pair &pair) noexcept(...) */
    constexpr void swap(Pair &pair)
      noexcept(is_nothrow_swappable_v<FirstType> && is_nothrow_swappable_v<SecondType>);

  };

  template<typename T1, typename T2, typename U1, typename U2,
    template<typename> typename TQual, template<typename> typename UQual>
      requires requires {
	  typename Pair<CommonReference_T<TQual<T1>, UQual<U1>>, CommonReference_T<TQual<T2>, UQual<U2>>>;
	}
  struct BasicCommonReference<Pair<T1, T2>, Pair<U1, U2>, TQual, UQual> {
    using Type = Pair<CommonReference_T<TQual<T1>, UQual<U1>>, CommonReference_T<TQual<T2>, UQual<U2>>>;
  };

  template<typename T1, typename T2, typename U1, typename U2>
    requires requires {
	typename Pair<CommonType_T<T1, U1>, CommonType_T<T2, U2>>;
      }
  struct CommonType<Pair<T1, T2>, Pair<U1, U2>> {
    using Type = Pair<CommonType_T<T1, U1>, CommonType_T<T2, U2>>;
  };

  template<typename T1, typename T2>
  constexpr bool operator==(const Pair<T1, T2>&, const Pair<T1, T2>&);

  template<typename T1, typename T2>
  constexpr CommonComparsionCategory_T<SynthThreeWayResult<T1>, SynthThreeWayResult<T2>>
    operator<=>(const Pair<T1, T2>&, const Pair<T1, T2>&);

  template<typename T1, typename T2>
  constexpr void swap(Pair<T1, T2> &a, Pair<T1, T2> &b)
    noexcept(noexcept(a.swap(b)))
    requires is_swappable_v<T1> && is_swappable_v<T2>;

  template<typename T1, typename T2>
  constexpr void swap(const Pair<T1, T2> &a, const Pair<T1, T2> &b)
    noexcept(noexcept(a.swap(b)))
    requires is_swappable_v<T1> && is_swappable_v<T2>;

  template<typename T1, typename T2>
  constexpr Pair<T1, T2> make_pair(T1&&, T2&&);

} // namespace me
// Implementations:

/* class me::Pair */

template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>::Pair()
  requires is_default_constructible_v<FirstType> && is_default_constructible_v<SecondType>
  : first(), second()
{
}

template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>::Pair(const FirstType &a, const SecondType &b)
  requires is_copy_constructible_v<FirstType> && is_copy_constructible_v<SecondType>
  : first(a), second(b)
{
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>::Pair(F2 &&a, S2 &&b)
  requires is_constructible_v<FirstType, F2&&> && is_constructible_v<SecondType, S2&&>
  : first(forward<F2>(a)), second(forward<S2>(b))
{
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>::Pair(const Pair<F2, S2> &pair)
  requires is_constructible_v<FirstType, const F2&> && is_constructible_v<SecondType, const S2&>
  : first(pair.first), second(pair.second)
{
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>::Pair(Pair<F2, S2> &&pair)
  requires is_constructible_v<FirstType, F2&&> && is_constructible_v<SecondType, S2&&>
  : first(forward<F2>(pair.first)), second(forward<S2>(pair.second))
{
}

template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>&
me::Pair<FirstType, SecondType>::operator=(const Pair &pair)
  requires is_copy_assignable_v<FirstType> && is_copy_assignable_v<SecondType>
{
  first = pair.first;
  second = pair.second;
  return *this;
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>&
me::Pair<FirstType, SecondType>::operator=(const Pair<F2, S2> &pair)
  requires is_assignable_v<FirstType&, const F2&> && is_assignable_v<SecondType&, const S2&>
{
  first = pair.first;
  second = pair.second;
  return *this;
}

template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>&
  me::Pair<FirstType, SecondType>::operator=(Pair &&pair)
  noexcept(is_nothrow_move_assignable_v<FirstType> && is_nothrow_move_assignable_v<SecondType>)
  requires is_move_assignable_v<FirstType> && is_move_assignable_v<SecondType>
{
  first = move(pair.first);
  second = move(pair.second);
  return *this;
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>&
me::Pair<FirstType, SecondType>::operator=(Pair<F2, S2> &&pair)
  requires is_assignable_v<FirstType&, F2> && is_assignable_v<SecondType&, S2>
{
  first = forward<F2>(pair.first);
  second = forward<S2>(pair.second);
  return *this;
}

template<typename FirstType, typename SecondType>
constexpr void
  me::Pair<FirstType, SecondType>::swap(Pair &pair)
  noexcept(is_nothrow_swappable_v<FirstType> && is_nothrow_swappable_v<SecondType>)
{
  ::me::swap(first, pair.first);
  ::me::swap(second, pair.second);
}

/* end class me::Pair */

template<typename T1, typename T2>
constexpr bool
  me::operator==(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
{
  return lhs.first = rhs.first && lhs.second == rhs.second;
}

template<typename T1, typename T2>
constexpr me::CommonComparsionCategory_T<me::SynthThreeWayResult<T1>, me::SynthThreeWayResult<T2>>
  me::operator<=>(const Pair<T1, T2> &lhs, const Pair<T1, T2> &rhs)
{
  if (auto res = synth_three_way(lhs.first, rhs.first) != 0)
    return res;
  return synth_three_way(lhs.second, rhs.second);
}

template<typename T1, typename T2>
constexpr void
  me::swap(Pair<T1, T2> &a, Pair<T1, T2> &b)
  noexcept(noexcept(a.swap(b)))
  requires is_swappable_v<T1> && is_swappable_v<T2>
{
  a.swap(b);
}

template<typename T1, typename T2>
constexpr void
  me::swap(const Pair<T1, T2> &a, const Pair<T1, T2> &b)
  noexcept(noexcept(a.swap(b)))
  requires is_swappable_v<T1> && is_swappable_v<T2>
{
  a.swap(b);
}

template<typename T1, typename T2>
constexpr me::Pair<T1, T2>
  me::make_pair(T1 &&first, T2 &&second)
{
  return Pair<T1, T2>(forward<T1>(first), forward<T2>(second));
}

#endif // LIBME_PAIR_HPP
