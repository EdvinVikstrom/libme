#ifndef LIBME_POINTER_TRAITS_HPP
  #define LIBME_POINTER_TRAITS_HPP

#include "libme/Type.hpp"

namespace me {

  template<typename Type>
  struct pointer_traits {

    typedef Type* Pointer;
    typedef Type ElementType;
    typedef ptrdiff_t DifferenceType;

    template<typename Other>
    struct rebind { typedef Other* other; };

  };

  template<typename From, typename To>
  struct rebind_pointer {

    typedef typename pointer_traits<From>::template rebind<To>::other type;

  };


} // namespace me

#endif
