#ifndef LIBME_BITS_ITERATOR_CONCEPTS_HPP
  #define LIBME_BITS_ITERATOR_CONCEPTS_HPP

#include "libme/Concepts.hpp"
#include "libme/Functional.hpp"

#include "libme/bits/iterator/IncrementableTraits.hpp"
#include "libme/bits/iterator/ReadableTraits.hpp"
#include "libme/bits/iterator/IteratorTraits.hpp"

namespace me {

  template<__Dereferenceable T>
    using IterReference_T = decltype(*declval<T&>());

  // iterator concepts

  template<typename In>
    concept IndirectlyReadable = true; // TODO

  template<IndirectlyReadable T>
    using IterCommonReference_T =
      CommonReference_T<IterReference_T<T>, IterValue_T<T>&>;

  template<typename Out, typename T>
    concept IndirectlyWritable = true; // TODO

  template<typename I>
    concept WeaklyIncrementable = true; // TODO

  template<typename I>
    concept Incrementable = true; // TODO

  template<typename I>
    concept InputOrOutputIterator = true; // TODO

  template<typename S, typename I>
    concept SentinelFor = true; // TODO

  template<typename S, typename I>
    inline constexpr bool disable_sized_sentinel_for = false;

  template<typename S, typename I>
    concept SizedSentinelFor = true; // TODO

  template<typename I>
    concept InputIterator = true; // TODO

  template<typename I, typename T>
    concept OutputIterator = true; // TODO

  template<typename I>
    concept ForwardIterator = true; // TODO

  template<typename I>
    concept BidirectionalIterator = true; // TODO

  template<typename I>
    concept RandomAccessIterator = true; // TODO

  template<typename I>
    concept ContiguousIterator = true; // TODO

  // indirect callable requirements

  template<typename F, typename I>
    concept IndirectlyUnaryInvocable = true; // TODO

  template<typename F, typename I>
    concept IndirectlyRegularUnaryInvocable = true; // TODO

  template<typename F, typename I>
    concept IndirectUnaryPredicate = true; // TODO

  template<typename F, typename I1, typename I2>
    concept IndirectBinaryPredicate = true; // TODO

  template<typename F, typename I1, typename I2 = I1>
    concept IndirectEquivalenceRelation = true; // TODO

  template<typename F, typename I1, typename I2 = I1>
    concept IndirectStrictWeakOrder = true; // TODO

  template<typename F, typename... Is>
    requires (IndirectlyReadable<Is> && ...) && Invocable<F, IterReference_T<Is>...>
      using indirect_result_t = InvokeResult_T<F, IterReference_T<Is>...>;

  template<IndirectlyReadable I, IndirectlyRegularUnaryInvocable<I> Proj>
    struct Projected;

  template<WeaklyIncrementable I, typename Proj>
  struct IncrementableTraits<Projected<I, Proj>>;

  // common algorithm requirements

  template<typename In, typename Out>
    concept IndirectlyMovable = true; // TODO

  template<typename In, typename Out>
    concept IndirectlyMovableStorable = true; // TODO

  template<typename In, typename Out>
    concept IndirectlyCopyable = true; // TODO

  template<typename In, typename Out>
    concept IndirectlyCopyableStorable = true; // TODO

  template<typename I1, typename I2 = I1>
    concept IndirectlySwappable = true; // TODO

  template<typename I1, typename I2, typename R, typename P1 = Identity, typename P2 = Identity>
    concept IndirectlyComparable = true; // TODO

  template<typename I>
    concept Permutable = true; // TODO

  template<typename I1, typename I2, typename Out, typename R = ranges::Less, typename P1 = Identity, typename P2 = Identity>
    concept Mergeable = true; // TODO

  template<typename I, typename R = ranges::Less, typename P = Identity>
    concept Sortable = true; // TODO

} // namespace me
// Implementations:

#endif // LIBME_BITS_ITERATOR_CONCEPTS_HPP
