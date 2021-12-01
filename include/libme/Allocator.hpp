#ifndef LIBME_ALLOCATOR_HPP
  #define LIBME_ALLOCATOR_HPP

#include "TypeTraits.hpp"

#include <stdlib.h>
#include <new>

namespace me {

  template<typename Type>
  class DefaultAllocator {

  public:

    typedef size_t SizeType;

  public:

    [[nodiscard]] static constexpr Type* allocate(SizeType num);

    static constexpr void deallocate(Type* ptr);

  };

  template<typename Type, typename Alloc = DefaultAllocator<Type>>
  class AllocatorTraits {

  public:

    typedef Type* Pointer;
    typedef const Type* ConstPointer;
    typedef size_t SizeType;
    typedef void* VoidPointer;

  public:

    [[nodiscard]] static constexpr Type* allocate(SizeType num);

    static constexpr void deallocate(Type* ptr);

    template<typename... Args>
    static constexpr void construct(Type* ptr, Args&&... args);

    static constexpr void destroy(Type* ptr);

  };

  template<typename Type, typename Traits>
  class TempValue {

  private:

    typename aligned_storage<sizeof(Type), alignof(Type)>::type m_value;

  public:

    template<typename... Args> constexpr TempValue(Args&&... args);
    constexpr ~TempValue();

    constexpr Type& get();
    constexpr Type* address();

  };

} // namespace me

/* -------------------------- */
/* class me::DefaultAllocator */
/* -------------------------- */
template<typename Type>
constexpr Type*
  me::DefaultAllocator<Type>::allocate(SizeType num)
{
  if (is_constant_evaluated())
    return static_cast<Type*>(::operator new(num * sizeof(Type)));
  else
    return static_cast<Type*>(::malloc(num * sizeof(Type)));
}

template<typename Type>
constexpr void
  me::DefaultAllocator<Type>::deallocate(Type* ptr)
{
  if (is_constant_evaluated())
    ::operator delete(ptr);
  else
    ::free(ptr);
}
/* end class me::DefaultAllocator */

/* ------------------------- */
/* class me::AllocatorTraits */
/* ------------------------- */
template<typename Type, typename Alloc>
constexpr Type*
  me::AllocatorTraits<Type, Alloc>::allocate(SizeType num)
{
  return Alloc::allocate(num);
}

template<typename Type, typename Alloc>
constexpr void
  me::AllocatorTraits<Type, Alloc>::deallocate(Type* ptr)
{
  return Alloc::deallocate(ptr);
}

template<typename Type, typename Alloc>
template<typename... Args>
constexpr void
  me::AllocatorTraits<Type, Alloc>::construct(Type* ptr, Args&&... args)
{
  ::new ((void*) ptr) Type(static_cast<Args&&>(args)...);
}

template<typename Type, typename Alloc>
constexpr void
  me::AllocatorTraits<Type, Alloc>::destroy(Type* ptr)
{
  ptr->~Type();
}
/* end class me::AllocatorTraits */

/* ------------------- */
/* class me::TempValue */
/* ------------------- */
template<typename Type, typename Traits>
template<typename... Args>
constexpr me::TempValue<Type, Traits>::TempValue(Args&&... args)
{
  Traits::construct(reinterpret_cast<Type*>(m_value), forward<Args>(args)...);
}

template<typename Type, typename Traits>
constexpr me::TempValue<Type, Traits>::~TempValue()
{
  Traits::destroy(*reinterpret_cast<Type*>(m_value));
}

template<typename Type, typename Traits>
constexpr Type& me::TempValue<Type, Traits>::get()
{
  return *reinterpret_cast<Type*>(m_value);
}

template<typename Type, typename Traits>
constexpr Type* me::TempValue<Type, Traits>::address()
{
  return reinterpret_cast<Type*>(m_value);
}
/* end class me::TempValue */

#endif
