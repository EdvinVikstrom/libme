#ifndef LIBME_POINTER_TRAITS_HPP
  #define LIBME_POINTER_TRAITS_HPP

#include "libme/Type.hpp"

namespace me {

  template<typename Type>
  struct PointerTraits {

    typedef Type* Pointer;
    typedef Type ElementType;
    typedef ptrdiff_t DifferenceType;

    template<typename O>
    struct Rebind { typedef O* Other; };

  };

  template<typename From, typename To>
  struct RebindPointer {

    typedef typename PointerTraits<From>::template Rebind<To>::Other Type;

  };


} // namespace me

#endif // LIBME_POINTER_TRAITS_HPP
