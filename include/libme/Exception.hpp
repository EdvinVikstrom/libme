#ifndef LIBME_EXCEPTION_HPP
  #define LIBME_EXCEPTION_HPP

#include <stdarg.h>
#include <stdio.h>

namespace me {

  class Exception {

  public:

    [[nodiscard]] virtual const char* get_message() const = 0;

  };

}

#endif
