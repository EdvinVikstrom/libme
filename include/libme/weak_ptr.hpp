#ifndef LIBME_WEAK_PTR_HPP
  #define LIBME_WEAK_PTR_HPP

#include "type.hpp"

namespace me {

  class WeakPtr {

  protected:

    typedef size_t Size;
    typedef void* Pointer;


  public:

    constexpr WeakPtr();

  };

}

#endif
