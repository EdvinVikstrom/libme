#ifndef MELIB_TYPE_HPP
  #define MELIB_TYPE_HPP

namespace me {

#ifndef SIZE_MAX
  #define SIZE_MAX __SIZE_MAX__
#endif

#ifndef ME_ALWAYS_INLINE
  #define ME_ALWAYS_INLINE [[gnu::always_inline]]
#endif

#define LIBME_ASSERT(c, m)
#define LIBME_STATIC_ASSERT(c, m) static_assert(c, m)

  typedef __UINT8_TYPE__ uint8_t;
  typedef __UINT16_TYPE__ uint16_t;
  typedef __UINT32_TYPE__ uint32_t;
  typedef __UINT64_TYPE__ uint64_t;

  typedef __INT8_TYPE__ int8_t;
  typedef __INT16_TYPE__ int16_t;
  typedef __INT32_TYPE__ int32_t;
  typedef __INT64_TYPE__ int64_t;
  typedef __INTMAX_TYPE__ intmax_t;
  typedef __UINTMAX_TYPE__ uintmax_t;

  typedef int32_t int_t;
  typedef uint32_t uint_t;

  typedef __SIZE_TYPE__ size_t;
  typedef int64_t ssize_t;

  typedef decltype(nullptr) nullptr_t;

  typedef __PTRDIFF_TYPE__ ptrdiff_t;

  static constexpr size_t dynamic_extent = SIZE_MAX;

}

#endif
