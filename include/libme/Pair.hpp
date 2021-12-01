#ifndef LIBME_PAIR_HPP
  #define LIBME_PAIR_HPP

#include "libme/Utility.hpp"
#include "libme/Compare.hpp"

namespace me {

  template<class FirstType, class SecondType>
  class Pair {

  public:

    FirstType first;
    SecondType second;

    /* explicit(...) constexpr Pair() requires ...; */
    explicit(!is_default_constructible<FirstType>::value || !is_default_constructible<SecondType>::value)
      constexpr Pair()
      requires is_default_constructible<FirstType>::value && is_default_constructible<SecondType>::value;

    /* explicit(...) constexpr Pair(const FirstType &a, const SecondType &b) requires ...; */
    explicit(!is_convertible<const FirstType&, FirstType>::value || !is_convertible<const SecondType&, SecondType>::value)
      constexpr Pair(const FirstType &a, const SecondType &b)
      requires is_copy_constructible<FirstType>::value && is_copy_constructible<SecondType>::value;

    /* template<...> explicit(...) constexpr Pair(F2 &&a, S2 &&b) requires ...; */
    template<typename F2 = FirstType, typename S2 = SecondType>
    explicit(!is_convertible<F2&&, FirstType>::value || !is_convertible<S2&&, SecondType>::value)
      constexpr Pair(F2 &&a, S2 &&b)
      requires is_constructible<FirstType, F2&&>::value && is_constructible<SecondType, S2&&>::value;

    /* template<...> explicit(...) constexpr Pair(const Pair<F2, S2> &pair) requires ...; */
    template<typename F2, typename S2>
    explicit(!is_convertible<const F2&, FirstType>::value || !is_convertible<const S2&, SecondType>::value)
      constexpr Pair(const Pair<F2, S2> &pair)
      requires is_constructible<FirstType, const F2&>::value && is_constructible<SecondType, const S2&>::value;

    /* template<...> explicit(...) constexpr Pair(Pair<F2, S2> &&pair) requires ...; */
    template<typename F2, typename S2>
    explicit(!is_convertible<F2&&, FirstType>::value || !is_convertible<S2&&, SecondType>::value)
      constexpr Pair(Pair<F2, S2> &&pair)
      requires is_constructible<FirstType, F2&&>::value && is_constructible<SecondType, S2&&>::value;

    constexpr Pair(const Pair &pair) = default;
    constexpr Pair(Pair &&pair) = default;

    /* constexpr Pair& operator=(const Pair &pair) requires ...; */
    constexpr Pair& operator=(const Pair &pair) = delete;
    constexpr Pair& operator=(const Pair &pair)
      requires is_copy_assignable<FirstType>::value && is_copy_assignable<SecondType>::value;

    /* template<...> constexpr Pair& operator=(const Pair<F2, S2> &pair) requires ...; */
    template<typename F2, typename S2>
    constexpr Pair& operator=(const Pair<F2, S2> &pair)
      requires is_assignable<FirstType&, const F2&>::value && is_assignable<SecondType&, const S2&>::value;

    /* constexpr Pair& operator=(Pair &&pair) noexcept(...) requires ...; */
    constexpr Pair& operator=(Pair &&pair)
      noexcept(is_nothrow_move_assignable<FirstType>::value && is_nothrow_move_assignable<SecondType>::value)
      requires is_move_assignable<FirstType>::value && is_move_assignable<SecondType>::value;

    /* template<...> constexpr Pair& operator=(Pair<F2, S2> &&pair) requires ...; */
    template<typename F2, typename S2>
    constexpr Pair& operator=(Pair<F2, S2> &&pair)
      requires is_assignable<FirstType&, F2>::value && is_assignable<SecondType&, S2>::value;

    /* constexpr void swap(Pair &pair) noexcept(...) */
    constexpr void swap(Pair &pair)
      noexcept(is_nothrow_swappable<FirstType>::value && is_nothrow_swappable<SecondType>::value);

  };

  template<typename FirstType, typename SecondType>
  constexpr me::Pair<typename me::decay<FirstType>::type, typename me::decay<SecondType>::type> make_pair(FirstType &&a, SecondType &&b);

  template<typename FirstType, typename SecondType>
  constexpr bool operator==(const Pair<FirstType, SecondType> &lhs, const Pair<FirstType, SecondType> &rhs);

  template<typename FirstType, typename SecondType>
  constexpr typename me::common_comparsion_category<synth_three_way_t<FirstType>, synth_three_way_t<SecondType>>::type
    operator<=>(const Pair<FirstType, SecondType> &lhs, const Pair<FirstType, SecondType> &rhs);

  template<typename T1, typename T2> class Pair;
  template<typename T1, typename T2>
  constexpr void swap(Pair<T1, T2> &a, Pair<T1, T2> &b)
    noexcept(noexcept(a.swap(b)))
    requires is_swappable<T1>::value && is_swappable<T2>::value;

} // namespace me

/* -------------- */
/* class me::Pair */
/* -------------- */
template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>::Pair()
  requires is_default_constructible<FirstType>::value && is_default_constructible<SecondType>::value
  : first(), second()
{
}

template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>::Pair(const FirstType &a, const SecondType &b)
  requires is_copy_constructible<FirstType>::value && is_copy_constructible<SecondType>::value
  : first(a), second(b)
{
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>::Pair(F2 &&a, S2 &&b)
  requires is_constructible<FirstType, F2&&>::value && is_constructible<SecondType, S2&&>::value
  : first(forward<F2>(a)), second(forward<S2>(b))
{
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>::Pair(const Pair<F2, S2> &pair)
  requires is_constructible<FirstType, const F2&>::value && is_constructible<SecondType, const S2&>::value
  : first(pair.first), second(pair.second)
{
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>::Pair(Pair<F2, S2> &&pair)
  requires is_constructible<FirstType, F2&&>::value && is_constructible<SecondType, S2&&>::value
  : first(forward<F2>(pair.first)), second(forward<S2>(pair.second))
{
}

template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>&
me::Pair<FirstType, SecondType>::operator=(const Pair &pair)
  requires is_copy_assignable<FirstType>::value && is_copy_assignable<SecondType>::value
{
  first = pair.first;
  second = pair.second;
  return *this;
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>&
me::Pair<FirstType, SecondType>::operator=(const Pair<F2, S2> &pair)
  requires is_assignable<FirstType&, const F2&>::value && is_assignable<SecondType&, const S2&>::value
{
  first = pair.first;
  second = pair.second;
  return *this;
}

template<typename FirstType, typename SecondType>
constexpr me::Pair<FirstType, SecondType>&
  me::Pair<FirstType, SecondType>::operator=(Pair &&pair)
  noexcept(is_nothrow_move_assignable<FirstType>::value && is_nothrow_move_assignable<SecondType>::value)
  requires is_move_assignable<FirstType>::value && is_move_assignable<SecondType>::value
{
  first = move(pair.first);
  second = move(pair.second);
  return *this;
}

template<typename FirstType, typename SecondType>
template<typename F2, typename S2>
constexpr me::Pair<FirstType, SecondType>&
me::Pair<FirstType, SecondType>::operator=(Pair<F2, S2> &&pair)
  requires is_assignable<FirstType&, F2>::value && is_assignable<SecondType&, S2>::value
{
  first = forward<F2>(pair.first);
  second = forward<S2>(pair.second);
  return *this;
}

template<typename FirstType, typename SecondType>
constexpr void
  me::Pair<FirstType, SecondType>::swap(Pair &pair)
  noexcept(is_nothrow_swappable<FirstType>::value && is_nothrow_swappable<SecondType>::value)
{
  ::me::swap(first, pair.first);
  ::me::swap(second, pair.second);
}
/* end class me::Pair */

template<typename FirstType, typename SecondType>
constexpr me::Pair<typename me::decay<FirstType>::type, typename me::decay<SecondType>::type>
  me::make_pair(FirstType &&a, SecondType &&b)
{
  return Pair<typename decay<FirstType>::type, typename decay<SecondType>::type>(forward<FirstType>(a), forward<SecondType>(b));
}

template<typename FirstType, typename SecondType>
constexpr bool
me::operator==(const Pair<FirstType, SecondType> &lhs, const Pair<FirstType, SecondType> &rhs)
{
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<typename FirstType, typename SecondType>
constexpr typename me::common_comparsion_category<me::synth_three_way_t<FirstType>, me::synth_three_way_t<SecondType>>::type
  me::operator<=>(const Pair<FirstType, SecondType> &lhs, const Pair<FirstType, SecondType> &rhs)
{
  if (auto res = synth_three_way(lhs.first, rhs.first) != 0)
    return res;
  synth_three_way(lhs.second, rhs.second);
}

template<typename T1, typename T2>
constexpr void
  me::swap(me::Pair<T1, T2> &a, me::Pair<T1, T2> &b)
  noexcept(noexcept(a.swap(b)))
  requires is_swappable<T1>::value && is_swappable<T2>::value
{
  a.swap(b);
}

#endif
