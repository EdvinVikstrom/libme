#ifndef LIBME_BITS_ITERATOR_RANGES_HPP
  #define LIBME_BITS_ITERATOR_RANGES_HPP

/* iterator */
#include "libme/bits/iterator/Concepts.hpp"

/* ranges */
#include "libme/bits/ranges/Access.hpp"

namespace me::ranges {

  inline namespace __cust {

    struct __IterMove { };

    struct __IterSwap { };

    inline namespace __func {
      inline constexpr __IterMove iter_move = { }; // TODO
      inline constexpr __IterSwap iter_swap = { }; // TODO
    } // namespace __func

  } // namespace __cust

  /* advance */
  template<InputOrOutputIterator I>
  constexpr void advance(I &i, IterDifference_T<I> n);

  template<InputOrOutputIterator I, SentinelFor<I> S>
  constexpr void advance(I &i, S bound);

  template<InputOrOutputIterator I, SentinelFor<I> S>
  constexpr IterDifference_T<I> advance(I &i, IterDifference_T<I> n, S bound);

  /* distance */
  template<InputOrOutputIterator I, SentinelFor<I> S>
    requires (!SizedSentinelFor<S, I>)
  constexpr IterDifference_T<I> distance(I first, S last);

  template<InputOrOutputIterator I, SizedSentinelFor<I> S>
  constexpr IterDifference_T<I> distance(const I &first, const S &last);

  template<Range R>
  constexpr RangeDifference_T<R> distance(R &&r);

  /* next */
  template<InputOrOutputIterator I>
  constexpr I next(I x);

  template<InputOrOutputIterator I>
  constexpr I next(I x, IterDifference_T<I> n);

  template<InputOrOutputIterator I, SentinelFor<I> S>
  constexpr I next(I x, S bound);

  template<InputOrOutputIterator I, SentinelFor<I> S>
  constexpr I next(I x, IterDifference_T<I> n, S bound);

  /* prev */
  template<BidirectionalIterator I>
  constexpr I prev(I x);

  template<BidirectionalIterator I>
  constexpr I prev(I x, IterDifference_T<I> n);

  template<BidirectionalIterator I>
  constexpr I prev(I x, IterDifference_T<I> n, I bound);


} // namespace me::ranges
// Implementations:

#endif // LIBME_BITS_ITERATOR_RANGES_HPP
