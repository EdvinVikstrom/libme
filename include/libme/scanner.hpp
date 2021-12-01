#ifndef LIBME_SCANNER_HPP
  #define LIBME_SCANNER_HPP

#include "template/string_view.hpp"

namespace me {

  template<typename T>
  class Scanner {

  public:

    typedef size_t Size;
    typedef T Type;
    typedef T* Iterator;
    typedef const T* ConstIterator;

  private:

  public:

    constexpr virtual bool has_remaining() const = 0;
    constexpr virtual Type peek() = 0;
    constexpr virtual Type read() = 0;
    constexpr virtual bool read(Type condition) = 0;
    constexpr virtual void read(Type dest[]) = 0;

  };

}

#endif
