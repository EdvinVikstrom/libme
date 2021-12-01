#ifndef LIBME_UNIQUE_PTR_HPP
  #define LIBME_UNIQUE_PTR_HPP

#include "libme/Allocator.hpp"

namespace me {

  template<typename Type, typename Deleter = DefaultAllocator<Type>>
  class UniquePtr {

  public:

    typedef Type* Pointer;
    typedef Type& Reference;

  private:

    Pointer m_pointer;

  public:

    constexpr explicit UniquePtr(Pointer ptr) noexcept;
    template<typename Type2, typename Deleter2> constexpr UniquePtr(UniquePtr<Type2, Deleter2> &&unique_ptr) noexcept;
    constexpr UniquePtr(UniquePtr &&unique_ptr) noexcept;
    constexpr UniquePtr(nullptr_t) noexcept;
    constexpr UniquePtr() noexcept;
    constexpr ~UniquePtr() noexcept;
    constexpr UniquePtr& operator=(UniquePtr &&unique_ptr) noexcept;
    template<typename Type2, typename Deleter2> constexpr UniquePtr& operator=(UniquePtr<Type2, Deleter2> &&unique_ptr) noexcept;
    constexpr UniquePtr& operator=(nullptr_t) noexcept;

    [[nodiscard]] constexpr Pointer release() noexcept;
    constexpr void reset(Pointer ptr) noexcept;
    constexpr void swap(UniquePtr &&unique_ptr) noexcept;

    [[nodiscard]] constexpr Pointer get() const noexcept;
    [[nodiscard]] constexpr operator bool() const noexcept;

    [[nodiscard]] constexpr Reference operator*() const;
    [[nodiscard]] constexpr Pointer operator->() const noexcept;

  };

  template<typename Type, typename... Args>
  constexpr UniquePtr<Type> make_unique(Args&&... args);

} // namespace me

/* ------------------- */
/* class me::UniquePtr */
/* ------------------- */
template<typename Type, typename Deleter>
constexpr me::UniquePtr<Type, Deleter>::UniquePtr(Pointer ptr) noexcept
  : m_pointer(ptr)
{
}

template<typename Type, typename Deleter>
template<typename Type2, typename Deleter2>
constexpr me::UniquePtr<Type, Deleter>::UniquePtr(UniquePtr<Type2, Deleter2> &&unique_ptr) noexcept
  : m_pointer(unique_ptr.release())
{
}

template<typename Type, typename Deleter>
constexpr me::UniquePtr<Type, Deleter>::UniquePtr(UniquePtr &&unique_ptr) noexcept
  : m_pointer(unique_ptr.release())
{
}

template<typename Type, typename Deleter>
constexpr me::UniquePtr<Type, Deleter>::UniquePtr(nullptr_t) noexcept
  : m_pointer(nullptr)
{
}

template<typename Type, typename Deleter>
constexpr me::UniquePtr<Type, Deleter>::UniquePtr() noexcept
  : m_pointer(nullptr)
{
}

template<typename Type, typename Deleter>
constexpr me::UniquePtr<Type, Deleter>::~UniquePtr() noexcept
{
  if (m_pointer != nullptr)
    Deleter::deallocate(m_pointer);
}

template<typename Type, typename Deleter>
constexpr me::UniquePtr<Type, Deleter>&
me::UniquePtr<Type, Deleter>::operator=(UniquePtr &&unique_ptr) noexcept
{
  reset(unique_ptr.release());
  return *this;
}

template<typename Type, typename Deleter>
template<typename Type2, typename Deleter2>
constexpr me::UniquePtr<Type, Deleter>&
me::UniquePtr<Type, Deleter>::operator=(UniquePtr<Type2, Deleter2> &&unique_ptr) noexcept
{
  reset(unique_ptr.release());
  return *this;
}

template<typename Type, typename Deleter>
constexpr me::UniquePtr<Type, Deleter>&
me::UniquePtr<Type, Deleter>::operator=(nullptr_t) noexcept
{
  reset(nullptr);
  return *this;
}

template<typename Type, typename Deleter>
constexpr typename me::UniquePtr<Type, Deleter>::Pointer
me::UniquePtr<Type, Deleter>::release() noexcept
{
  Pointer ptr = m_pointer;
  m_pointer = nullptr;
  return ptr;
}

template<typename Type, typename Deleter>
constexpr void
me::UniquePtr<Type, Deleter>::reset(Pointer ptr) noexcept
{
  Pointer old = m_pointer;
  m_pointer = ptr;
  if (old)
    Deleter::deallocate(old);
  //if (m_pointer)
  //  Deleter::deallocate(m_pointer);
  //m_pointer = ptr;
}

template<typename Type, typename Deleter>
constexpr void
me::UniquePtr<Type, Deleter>::swap(UniquePtr &&unique_ptr) noexcept
{
  swap(m_pointer, unique_ptr.m_pointer);
}

template<typename Type, typename Deleter>
constexpr typename me::UniquePtr<Type, Deleter>::Pointer
me::UniquePtr<Type, Deleter>::get() const noexcept
{
  return m_pointer;
}

template<typename Type, typename Deleter>
constexpr
me::UniquePtr<Type, Deleter>::operator bool() const noexcept
{
  return m_pointer != nullptr;
}

template<typename Type, typename Deleter>
constexpr typename me::UniquePtr<Type, Deleter>::Reference
me::UniquePtr<Type, Deleter>::operator*() const
{
  return *m_pointer;
}

template<typename Type, typename Deleter>
constexpr typename me::UniquePtr<Type, Deleter>::Pointer
me::UniquePtr<Type, Deleter>::operator->() const noexcept
{
  return m_pointer;
}
/* end class me::UniquePtr */

template<typename Type, typename... Args>
constexpr me::UniquePtr<Type>
me::make_unique(Args&&... args)
{
  Type* ptr = DefaultAllocator<Type>::allocate(1);
  TypeTraits<Type>::construct(ptr, forward<Args>(args)...);
  return UniquePtr<Type>(ptr);
}

#endif
