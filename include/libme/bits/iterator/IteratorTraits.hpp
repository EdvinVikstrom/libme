#ifndef LIBME_BITS_ITERATOR_ITERATOR_TRAITS_HPP
  #define LIBME_BITS_ITERATOR_ITERATOR_TRAITS_HPP

#include "libme/TypeTraits.hpp"

namespace me {

  template<typename T>
  concept __HasMemberMOPOperator = requires { T::operator->(); };

  template<typename I> struct IteratorTraits;

  template<typename T>
    requires is_object_v<T>
  struct IteratorTraits<T*>;

} // namespace me

#endif // LIBME_BITS_ITERATOR_ITERATOR_TRAITS_HPP
