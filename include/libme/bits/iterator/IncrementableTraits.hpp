#ifndef LIBME_BITS_ITERATOR_INCREMENTABLE_TRAITS_HPP
  #define LIBME_BITS_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include "libme/Concepts.hpp"

namespace me {

  template<typename>
  struct IteratorTraits;

  template<typename> struct IncrementableTraits { };
  template<typename T>
    requires me::is_object_v<T>
  struct IncrementableTraits<T*> {
    using DifferenceType = ptrdiff_t;
  };
  
  template<typename I>
  struct IncrementableTraits<const I> : IncrementableTraits<I> { };
  
  template<typename T>
    requires requires { typename T::DifferenceType; }
  struct IncrementableTraits<T> {
    using DifferenceType = typename T::DifferenceType;
  };
  
  template<typename T>
    requires (!requires { typename T::DifferenceType; } &&
        requires(const T &a, const T &b) { {a - b } -> me::Integral; })
  struct IncrementableTraits<T> {
    using DifferenceType = MakeSigned_T<decltype(declval<T>() - declval<T>())>;
  };

  template<typename T>
  using IterDifference_T = Conditional_T<__IsPrimaryTemplate<IteratorTraits<RemoveCVRef_T<T>>>::value,
	typename IncrementableTraits<RemoveCVRef_T<T>>::DifferenceType,
	typename IteratorTraits<RemoveCVRef_T<T>>::DifferenceType>;

} // namespace me

#endif // LIBME_BITS_ITERATOR_INCREMENTABLE_TRAITS_HPP
