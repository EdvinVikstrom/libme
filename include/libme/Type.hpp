#ifndef MELIB_TYPE_HPP
  #define MELIB_TYPE_HPP

#include "libme/bits/Byte.hpp"

namespace me {

#ifndef ME_ALWAYS_INLINE
  #define ME_ALWAYS_INLINE [[gnu::always_inline]]
#endif

#define LIBME_ASSERT(c, m)
#define LIBME_STATIC_ASSERT(c, m) static_assert(c, m)

  typedef __INT8_TYPE__ int8_t;
  typedef __INT16_TYPE__ int16_t;
  typedef __INT32_TYPE__ int32_t;
  typedef __INT64_TYPE__ int64_t;
  typedef __INT_FAST8_TYPE__ int_fast8_t;
  typedef __INT_FAST16_TYPE__ int_fast16_t;
  typedef __INT_FAST32_TYPE__ int_fast32_t;
  typedef __INT_FAST64_TYPE__ int_fast64_t;
  typedef __INT_LEAST8_TYPE__ int_least8_t;
  typedef __INT_LEAST16_TYPE__ int_least16_t;
  typedef __INT_LEAST32_TYPE__ int_least32_t;
  typedef __INT_LEAST64_TYPE__ int_least64_t;
  typedef __INTMAX_TYPE__ intmax_t;

  typedef __UINT8_TYPE__ uint8_t;
  typedef __UINT16_TYPE__ uint16_t;
  typedef __UINT32_TYPE__ uint32_t;
  typedef __UINT64_TYPE__ uint64_t;
  typedef __UINT_FAST8_TYPE__ uint_fast8_t;
  typedef __UINT_FAST16_TYPE__ uint_fast16_t;
  typedef __UINT_FAST32_TYPE__ uint_fast32_t;
  typedef __UINT_FAST64_TYPE__ uint_fast64_t;
  typedef __UINT_LEAST8_TYPE__ uint_least8_t;
  typedef __UINT_LEAST16_TYPE__ uint_least16_t;
  typedef __UINT_LEAST32_TYPE__ uint_least32_t;
  typedef __UINT_LEAST64_TYPE__ uint_least64_t;
  typedef __UINTMAX_TYPE__ uintmax_t;
  typedef __UINTPTR_TYPE__ uintptr_t;

/* minimum */
#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483648)
#define INT64_MIN (-9223372036854775808)

#define INT_FAST8_MIN (0)
#define INT_FAST16_MIN (0)
#define INT_FAST32_MIN (0)
#define INT_FAST64_MIN (0)

#define INT_LEAST8_MIN (0)
#define INT_LEAST16_MIN (0)
#define INT_LEAST32_MIN (0)
#define INT_LEAST64_MIN (0)

#define INTPTR_MIN (0)
#define INTMAX_MIN (0)

/* maximum */
#define INT8_MAX __INT8_MAX__
#define INT16_MAX __INT16_MAX__
#define INT32_MAX __INT32_MAX__
#define INT64_MAX __INT64_MAX__

#define INT_FAST8_MAX __INT_FAST8_MAX__
#define INT_FAST16_MAX __INT_FAST16_MAX__
#define INT_FAST32_MAX __INT_FAST32_MAX__
#define INT_FAST64_MAX __INT_FAST64_MAX__

#define INT_LEAST8_MAX __INT_LEAST8_MAX__
#define INT_LEAST16_MAX __INT_LEAST16_MAX__
#define INT_LEAST32_MAX __INT_LEAST32_MAX__
#define INT_LEAST64_MAX __INT_LEAST64_MAX__

#define INTPTR_MAX __INTPTR_MAX__
#define INTMAX_MAX __INTMAX_MAX__

/* unsigned maximum */
#define UINT8_MAX __UINT8_MAX__
#define UINT16_MAX __UINT16_MAX__
#define UINT32_MAX __UINT32_MAX__
#define UINT64_MAX __UINT64_MAX__

#define UINT_FAST8_MAX __UINT_FAST8_MAX__
#define UINT_FAST16_MAX __UINT_FAST16_MAX__
#define UINT_FAST32_MAX __UINT_FAST32_MAX__
#define UINT_FAST64_MAX __UINT_FAST64_MAX__

#define UINT_LEAST8_MAX __UINT_LEAST8_MAX__
#define UINT_LEAST16_MAX __UINT_LEAST16_MAX__
#define UINT_LEAST32_MAX __UINT_LEAST32_MAX__
#define UINT_LEAST64_MAX __UINT_LEAST64_MAX__

#define UINTPTR_MAX __UINTPTR_MAX__
#define UINTMAX_MAX __UINTMAX_MAX__

  typedef __SIZE_TYPE__ size_t;
  typedef int64_t ssize_t;
  typedef __PTRDIFF_TYPE__ ptrdiff_t;
  typedef decltype(nullptr) nullptr_t;
  typedef long double max_align_t;

#define PTRDIFF_MIN (0)
#define PTRDIFF_MAX __PTRDIFF_MAX__
#define SIZE_MAX __SIZE_MAX__
#define SSIZE_MIN INT64_MIN
#define SSIZE_MAX INT64_MAX
#define WCHAR_MIN (0)
#define WCHAR_MAX __WCHAR_MAX__
#define WINT_MIN __WINT_MIN__
#define WINT_MAX __WINT_MAX__

  static constexpr size_t dynamic_extent = SIZE_MAX;

} // namespace me

#endif
