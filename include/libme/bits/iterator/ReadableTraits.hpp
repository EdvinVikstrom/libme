#ifndef LIBME_BITS_ITERATOR_READABLE_TRAITS_HPP
  #define LIBME_BITS_ITERATOR_READABLE_TRAITS_HPP

#include "libme/Concepts.hpp"

namespace me {

  template<typename>
  struct IteratorTraits;

  template<typename T>
  using __WithReference = T&;

  template<typename T>
  concept __CanReference = requires { typename __WithReference<T>; };

  template<typename T>
  concept __Dereferenceable = requires(T &t) {
    { *t } -> __CanReference;
  };

  template<typename> struct __CondValueType { };

  template<typename T>
    requires is_object_v<T>
  struct __CondValueType<T> {
    using ValueType = RemoveCV_T<T>;
  };

  template<typename T>
  concept __HasMemberValueType = requires { typename T::ValueType; };

  template<typename T>
  concept __HasMemberElementType = requires { typename T::ElementType; };

  template<typename> struct IndirectlyReadableTraits { };

  template<typename T>
  struct IndirectlyReadableTraits<T*> : __CondValueType<T> { };

  template<typename I>
    requires is_array_v<I>
  struct IndirectlyReadableTraits<I> {
    using ValueType = RemoveCV_T<RemoveExtent_T<I>>;
  };
  
  template<typename I>
  struct IndirectlyReadableTraits<const I> : IndirectlyReadableTraits<I> { };

  template<__HasMemberValueType T>
  struct IndirectlyReadableTraits<T> : __CondValueType<typename T::ValueType> { };

  template<__HasMemberElementType T>
  struct IndirectlyReadableTraits<T> : __CondValueType<typename T::ElementType> { };

  template<__HasMemberValueType T>
    requires __HasMemberElementType<T>
  struct IndirectlyReadableTraits<T> { };

  template<__HasMemberValueType T>
    requires __HasMemberElementType<T> &&
      SameAs<RemoveCV_T<typename T::ElementType>, RemoveCV_T<typename T::ValueType>>
  struct IndirectlyReadableTraits<T> : __CondValueType<typename T::ValueType> { };

  template<typename T>
  using IterValue_T = Conditional_T<__IsPrimaryTemplate<IteratorTraits<RemoveCVRef_T<T>>>::value,
	typename IndirectlyReadableTraits<RemoveCVRef_T<T>>::ValueType,
	typename IteratorTraits<RemoveCVRef_T<T>>::ValueType>;

} // namespace me

#endif // LIBME_BITS_ITERATOR_READABLE_TRAITS_HPP
