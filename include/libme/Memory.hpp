#ifndef LIBME_MEMORY_HPP
  #define LIBME_MEMORY_HPP

#include "libme/TypeTraits.hpp"
#include "libme/Utility.hpp"

namespace me::memory {

  template<typename T>
  struct default_delete {
    void operator()(T* ptr)
    {
      delete ptr;
    }
  };

  template<typename TA>
  struct default_delete<TA[]> {
    void operator()(TA arr[])
    {
      delete[] arr;
    }
  };

  template<typename Type> constexpr void copy(Type* dest, Type* begin, Type* end);
  template<typename Type> constexpr void move(Type* dest, Type* src, me::size_t num);

  template<typename Type> constexpr bool in_range(const Type* ptr, const Type* begin, const Type* end);

} // namespace me::memory

template<typename Type>
constexpr void me::memory::copy(Type* dest, Type* begin, Type* end)
{
  /* TODO: use memcpy if not a constant expression */
  while (begin != end)
    *dest++ = *begin++;
}

template<typename Type>
constexpr void me::memory::move(Type* dest, Type* src, me::size_t num)
{
  if (dest < src)
  {
    for (size_t i = 0; num--; i++)
      dest[i] = move(src[i]);
  }else if (dest > src)
  {
    for (size_t i = num - 1; num--; i--)
      dest[i] = move(src[i]);
  }
}

template<typename Type>
constexpr bool in_range(const Type* ptr, const Type* begin, const Type* end)
{
  return ptr >= begin && ptr <= end;
}

#endif
