#ifndef LIBME_ALLOCATOR_HPP
  #define LIBME_ALLOCATOR_HPP

#include "TypeTraits.hpp"
#include "PointerTraits.hpp"

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

  private:

    struct __Helper {

#define __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(name, member) \
  template<typename T, typename = void> struct name : FalseType { }; \
  template<typename T> struct name<T, typename __Void<typename T:: member >::Type> : TrueType { };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__has_pointer, Pointer)
      template<typename Alloc, typename T, bool = __has_pointer<Alloc>::value>
      struct Pointer { typedef typename Alloc::Pointer Type; };
      template<typename Alloc, typename T>
      struct Pointer<Alloc, T, false> { typedef T* Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__has_const_pointer, ConstPointer)
      template<typename Alloc, typename P, typename T, bool = __has_const_pointer<Alloc>::value>
      struct ConstPointer { typedef typename Alloc::ConstPointer Type; };
      template<typename Alloc, typename P, typename T>
      struct ConstPointer<Alloc, P, T, false> { typedef typename PointerTraits<P>::template Rebind<const T> Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__has_void_pointer, VoidPointer)
      template<typename Alloc, typename P, bool = __has_void_pointer<Alloc>::value>
      struct VoidPointer { typedef typename Alloc::VoidPointer Type; };
      template<typename Alloc, typename P>
      struct VoidPointer<Alloc, P, false> { typedef typename PointerTraits<P>::template Rebind<void> Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__has_const_void_pointer, ConstVoidPointer)
      template<typename Alloc, typename P, bool = __has_const_void_pointer<Alloc>::value>
      struct ConstVoidPointer { typedef typename Alloc::ConstVoidPointer Type; };
      template<typename Alloc, typename P>
      struct ConstVoidPointer<Alloc, P, false> { typedef typename PointerTraits<P>::template Rebind<const void> Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__has_difference_type, DifferenceType)
      template<typename Alloc, typename P, bool = __has_difference_type<Alloc>::value>
      struct DifferenceType { typedef typename Alloc::DifferenceType Type; };
      template<typename Alloc, typename P>
      struct DifferenceType<Alloc, P, false> { typedef typename PointerTraits<P>::DifferenceType Type; }; // TODO

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__has_size_type, SizeType)
      template<typename Alloc, typename T, bool = __has_size_type<Alloc>::value>
      struct SizeType { typedef typename Alloc::SizeType Type; };
      template<typename Alloc, typename T>
      struct SizeType<Alloc, T, false> { typedef MakeUnsigned_T<T> Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__HasPropagateOnContainerCopyAssignment, PropagateOnContainerCopyAssignment)
      template<typename Alloc, bool = __HasPropagateOnContainerCopyAssignment<Alloc>::value>
      struct PropagateOnContainerCopyAssignment { typedef typename Alloc::PropagateOnContainerCopyAssignment Type; };
      template<typename Alloc>
      struct PropagateOnContainerCopyAssignment<Alloc, false> { typedef FalseType Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__HasPropagateOnContainerMoveAssignment, PropagateOnContainerMoveAssignment)
      template<typename Alloc, bool = __HasPropagateOnContainerMoveAssignment<Alloc>::value>
      struct PropagateOnContainerMoveAssignment { typedef typename Alloc::PropagateOnContainerMoveAssignment Type; };
      template<typename Alloc>
      struct PropagateOnContainerMoveAssignment<Alloc, false> { typedef FalseType Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__HasPropagateOnContainerSwap, PropagateOnContainerSwap)
      template<typename Alloc, bool = __HasPropagateOnContainerSwap<Alloc>::value>
      struct PropagateOnContainerSwap { typedef typename Alloc::PropagateOnContainerSwap Type; };
      template<typename Alloc>
      struct PropagateOnContainerSwap<Alloc, false> { typedef FalseType Type; };

      __LIBME_ALLOCATOR_TRAITS_HAS_MEMBER(__HasIsAlwaysEqual, IsAlwaysEqual)
      template<typename Alloc, bool = __HasIsAlwaysEqual<Alloc>::value>
      struct IsAlwaysEqual { typedef typename Alloc::IsAlwaysEqual Type; };
      template<typename Alloc>
      struct IsAlwaysEqual<Alloc, false> { typedef typename IsEmpty<Alloc>::Type Type; };

    };

  public:

    typedef Allocator AllocatorType;
    typedef typename Allocator::ValueType ValueType;
    typedef typename __Helper::template Pointer<Allocator, ValueType>::Type Pointer;
    typedef typename __Helper::template ConstPointer<Allocator, Pointer, ValueType>::Type ConstPointer;
    typedef typename __Helper::template VoidPointer<Allocator, Pointer>::Type VoidPointer;
    typedef typename __Helper::template ConstVoidPointer<Allocator, Pointer>::Type ConstVoidPointer;
    typedef typename __Helper::template DifferenceType<Allocator, Pointer>::Type DifferenceType;
    typedef typename __Helper::template SizeType<Allocator, DifferenceType>::Type SizeType;
    typedef typename __Helper::template PropagateOnContainerCopyAssignment<Allocator>::Type PropagateOnContainerCopyAssignment;
    typedef typename __Helper::template PropagateOnContainerMoveAssignment<Allocator>::Type PropagateOnContainerMoveAssignment;
    typedef typename __Helper::template PropagateOnContainerSwap<Allocator>::Type PropagateOnContainerSwap;
    typedef typename __Helper::template IsAlwaysEqual<Allocator>::Type IsAlwaysEqual;

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

#endif // LIBME_ALLOCATOR_HPP
