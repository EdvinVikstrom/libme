#ifndef LIBME_EXCEPTIONS_HPP
  #define LIBME_EXCEPTIONS_HPP

#include "libme/Exception.hpp"

namespace me {
  
  class RuntimeError : public Exception {

  private:

    char message[1024];

  public:

    template<typename... Args>
    constexpr RuntimeError(const char* format, ...)
    {
      va_list args;
      va_start(args, format);
      vsprintf(message, format, args);
      va_end(args);
    }

    const char* get_message() const override
    {
      return message;
    }
    
  };

} // namespace me

#define LIBME_EXCEPTION_DEFINE(n, m) \
namespace me { \
  class n : public Exception { \
  public: \
    constexpr n() { } \
    const char* get_message() const override \
    { \
      return m; \
    } \
  }; \
}

LIBME_EXCEPTION_DEFINE(OutOfRangeError, "index out of range")
LIBME_EXCEPTION_DEFINE(NullptrError, "value is nullptr")

#endif
