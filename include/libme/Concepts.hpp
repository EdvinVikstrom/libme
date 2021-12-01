#ifndef LIBME_CONCEPTS_HPP
  #define LIBME_CONCEPTS_HPP

#include "libme/TypeTraits.hpp"

namespace me {

  template<typename Type1, typename Type2>
  concept same_as = is_same<Type1, Type2>::value && is_same<Type2, Type1>::value;

  template<typename Derived, typename Base>
  concept derived_from = is_base_of<Base, Derived>::value && is_convertible<const volatile Derived*, const volatile Base*>::value;

  template<typename From, typename To>
  concept convertible_to = is_convertible<From, To>::value && requires { static_cast<To>(declval<From>()); };

  // concept common_reference_with = same_as



}

#endif
