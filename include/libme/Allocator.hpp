#ifndef LIBME_ALLOCATOR_HPP
  #define LIBME_ALLOCATOR_HPP

#include "TypeTraits.hpp"

#include <stdlib.h>
#include <new>

namespace me {

  template<typename Type>
  class DefaultAllocator {

  public:

    typedef Type ValueType;
    typedef size_t SizeType;

  public:

    [[nodiscard]] static constexpr Type* allocate(SizeType num);

    static constexpr void deallocate(ValueType* ptr);

  };

  template<typename Allocator>
  class AllocatorTraits {

  public:

    typedef typename Allocator::ValueType ValueType;
    typedef ValueType* Pointer;
    typedef const ValueType* ConstPointer;
    typedef size_t SizeType;
    typedef ptrdiff_t DifferenceType;
    typedef void* VoidPointer;

  public:

    [[nodiscard]] static constexpr ValueType* allocate(SizeType num);

    static constexpr void deallocate(ValueType* ptr);

    template<typename... Args>
    static constexpr void construct(ValueType* ptr, Args&&... args);

    static constexpr void destroy(ValueType* ptr);

  };

  template<typename Type, typename Traits>
  class TempValue {

  private:

    AlignedStorage_T<sizeof(Type), alignof(Type)> m_value;

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
template<typename Allocator>
constexpr typename me::AllocatorTraits<Allocator>::ValueType*
  me::AllocatorTraits<Allocator>::allocate(SizeType num)
{
  return Allocator::allocate(num);
}

template<typename Allocator>
constexpr void
  me::AllocatorTraits<Allocator>::deallocate(ValueType* ptr)
{
  return Allocator::deallocate(ptr);
}

template<typename Allocator>
template<typename... Args>
constexpr void
  me::AllocatorTraits<Allocator>::construct(ValueType* ptr, Args&&... args)
{
  ::new ((void*) ptr) ValueType(static_cast<Args&&>(args)...);
}

template<typename Allocator>
constexpr void
  me::AllocatorTraits<Allocator>::destroy(ValueType* ptr)
{
  ptr->~ValueType();
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
