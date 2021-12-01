#ifndef LIBME_SHARED_PTR_HPP
  #define LIBME_SHARED_PTR_HPP

#include "libme/Allocator.hpp"
#include "libme/Utility.hpp"

#include <stdio.h>

namespace me {

  template<typename Type, typename Deleter>
  class SharedCount {

  public:

    typedef ssize_t Size;

  private:

    Size m_count;
    Type* m_pointer;

  public:

    constexpr SharedCount(Type* ptr);
    template<typename PtrType> constexpr SharedCount(PtrType* ptr);
    constexpr SharedCount(nullptr_t);
    constexpr SharedCount();
    
    constexpr void add();
    constexpr void release();
    constexpr void reset(Type* ptr);

    [[nodiscard]] constexpr Size count() const;
    [[nodiscard]] constexpr operator bool() const;

  };

  template<typename Type, typename Deleter = DefaultAllocator<Type>>
  class SharedPtr {

  public:

    typedef size_t Size;

  private:

    SharedCount<Type, Deleter>* m_counter;
    Type* m_pointer;

  public:

    constexpr SharedPtr();
    constexpr SharedPtr(nullptr_t);
    constexpr SharedPtr(Type* ptr);
    template<typename PtrType> constexpr SharedPtr(PtrType* ptr) requires is_convertible<PtrType, Type>::value;
    template<typename PtrType> constexpr SharedPtr(const SharedPtr<PtrType> &shared_ptr, Type* ptr);
    template<typename PtrType> constexpr SharedPtr(SharedPtr<PtrType> &&shared_ptr, Type* ptr);
    constexpr SharedPtr(const SharedPtr &shared_ptr);
    template<typename PtrType> constexpr SharedPtr(const SharedPtr<PtrType> &shared_ptr);
    constexpr SharedPtr(SharedPtr &&shared_ptr);
    template<typename PtrType> constexpr SharedPtr(SharedPtr<PtrType> &&shared_ptr);
    constexpr ~SharedPtr();
    constexpr SharedPtr& operator=(const SharedPtr &shared_ptr) noexcept;
    template<typename PtrType> constexpr SharedPtr& operator=(const SharedPtr<PtrType> &shared_ptr) noexcept;
    constexpr SharedPtr& operator=(SharedPtr &&shared_ptr) noexcept;
    template<typename PtrType> constexpr SharedPtr& operator=(SharedPtr<PtrType> &&shared_ptr) noexcept;

    constexpr void reset() noexcept;
    template<typename PtrType> constexpr void reset(PtrType* ptr);
    constexpr void swap(SharedPtr &shared_ptr) noexcept;

    constexpr Type* get() const noexcept;
    constexpr Size use_count() const;
    constexpr bool is_unique() const;

    constexpr Type& operator*() const;
    constexpr Type* operator->() const;
    constexpr operator bool() const;

    SharedCount<Type, Deleter>*& __m_counter() { return m_counter; }
    SharedCount<Type, Deleter>* __m_counter() const { return m_counter; }
    Type*& __m_pointer() { return m_pointer; }
    Type* __m_pointer() const { return m_pointer; }

  };

  template<typename Type, typename... Args>
  constexpr SharedPtr<Type> make_shared(Args&&... args);

}

/* ----------------------- */
/* class me::SharedCounter */
/* ----------------------- */
template<typename Type, typename Deleter>
constexpr me::SharedCount<Type, Deleter>::SharedCount(Type* ptr)
{
  reset(ptr);
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedCount<Type, Deleter>::SharedCount(PtrType* ptr)
{
  reset(ptr);
}

template<typename Type, typename Deleter>
constexpr me::SharedCount<Type, Deleter>::SharedCount(nullptr_t)
{
  reset(nullptr);
}

template<typename Type, typename Deleter>
constexpr me::SharedCount<Type, Deleter>::SharedCount()
{
  reset(nullptr);
}

template<typename Type, typename Deleter>
constexpr void
me::SharedCount<Type, Deleter>::add()
{
  m_count++;
}

template<typename Type, typename Deleter>
constexpr void
me::SharedCount<Type, Deleter>::release()
{
  m_count--;
  if (m_count <= 0)
    Deleter::deallocate(m_pointer);
}

template<typename Type, typename Deleter>
constexpr void
me::SharedCount<Type, Deleter>::reset(Type* ptr)
{
  m_count = 1;
  if (m_pointer)
    Deleter::deallocate(m_pointer);
  m_pointer = ptr;
}

template<typename Type, typename Deleter>
constexpr typename me::SharedCount<Type, Deleter>::Size
me::SharedCount<Type, Deleter>::count() const
{
  return m_count;
}

template<typename Type, typename Deleter>
constexpr
me::SharedCount<Type, Deleter>::operator bool() const
{
  return m_count > 0;
}
/* end class me::SharedCounter */

/* ------------------- */
/* class me::SharedPtr */
/* ------------------- */
template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr()
  : m_counter(nullptr), m_pointer(nullptr)
{
}

template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(nullptr_t)
  : m_counter(nullptr), m_pointer(nullptr)
{
}

template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(Type* ptr)
  : m_counter(new SharedCount<Type, Deleter>(ptr)), m_pointer(ptr)
{
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(PtrType* ptr) requires is_convertible<PtrType, Type>::value
  : m_counter(new SharedCount<Type, Deleter>(ptr)), m_pointer(ptr)
{
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(const SharedPtr<PtrType> &shared_ptr, Type* ptr)
  : m_counter(reinterpret_cast<SharedCount<Type, Deleter>*>(shared_ptr.__m_counter())), m_pointer(ptr)
{
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(SharedPtr<PtrType> &&shared_ptr, Type* ptr)
  : m_counter(reinterpret_cast<SharedCount<Type, Deleter>*>(shared_ptr.__m_counter())), m_pointer(ptr)
{
}

template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(const SharedPtr &shared_ptr)
  : m_counter(shared_ptr.m_counter), m_pointer(shared_ptr.m_pointer)
{
  if (m_counter)
    m_counter->add();
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(const SharedPtr<PtrType> &shared_ptr)
  : m_counter(reinterpret_cast<SharedCount<Type, Deleter>*>(shared_ptr.__m_counter())), m_pointer(shared_ptr.__m_pointer())
{
  if (m_counter)
    m_counter->add();
}

template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(SharedPtr &&shared_ptr)
  : m_counter(shared_ptr.m_counter), m_pointer(shared_ptr.m_pointer)
{
  shared_ptr.m_counter = nullptr;
  shared_ptr.m_pointer = nullptr;
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedPtr<Type, Deleter>::SharedPtr(SharedPtr<PtrType> &&shared_ptr)
  : m_counter(reinterpret_cast<SharedCount<Type, Deleter>*>(shared_ptr.__m_counter())), m_pointer(shared_ptr.__m_pointer())
{
  shared_ptr.__m_counter() = nullptr;
  shared_ptr.__m_pointer() = nullptr;
}

template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>::~SharedPtr()
{
  if (m_counter)
  {
    m_counter->release();
    if (!*m_counter)
      delete m_counter;
  }
}

template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>&
me::SharedPtr<Type, Deleter>::operator=(const SharedPtr &shared_ptr) noexcept
{
  SharedPtr<Type>(shared_ptr).swap(*this);
  return *this;
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedPtr<Type, Deleter>&
me::SharedPtr<Type, Deleter>::operator=(const SharedPtr<PtrType> &shared_ptr) noexcept
{
  SharedPtr<Type>(shared_ptr).swap(*this);
  return *this;
}

template<typename Type, typename Deleter>
constexpr me::SharedPtr<Type, Deleter>&
me::SharedPtr<Type, Deleter>::operator=(SharedPtr &&shared_ptr) noexcept
{
  SharedPtr<Type>(move(shared_ptr)).swap(*this);
  return *this;
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr me::SharedPtr<Type, Deleter>&
me::SharedPtr<Type, Deleter>::operator=(SharedPtr<PtrType> &&shared_ptr) noexcept
{
  SharedPtr<Type>(move(shared_ptr)).swap(*this);
  return *this;
}

template<typename Type, typename Deleter>
constexpr void
me::SharedPtr<Type, Deleter>::reset() noexcept
{
  SharedPtr().swap(*this);
}

template<typename Type, typename Deleter>
template<typename PtrType>
constexpr void
me::SharedPtr<Type, Deleter>::reset(PtrType* ptr)
{
  SharedPtr<Type, Deleter>(ptr).swap(*this);
}

template<typename Type, typename Deleter>
constexpr void
me::SharedPtr<Type, Deleter>::swap(SharedPtr &shared_ptr) noexcept
{
  ::me::swap(m_counter, shared_ptr.m_counter);
  ::me::swap(m_pointer, shared_ptr.m_pointer);
}

template<typename Type, typename Deleter>
constexpr Type*
me::SharedPtr<Type, Deleter>::get() const noexcept
{
  return m_pointer;
}

template<typename Type, typename Deleter>
constexpr typename me::SharedPtr<Type, Deleter>::Size
me::SharedPtr<Type, Deleter>::use_count() const
{
  return m_counter->count();
}

template<typename Type, typename Deleter>
constexpr bool
me::SharedPtr<Type, Deleter>::is_unique() const
{
  return m_counter->count() == 1;
}

template<typename Type, typename Deleter>
constexpr Type&
me::SharedPtr<Type, Deleter>::operator*() const
{
  return *m_pointer;
}

template<typename Type, typename Deleter>
constexpr Type*
me::SharedPtr<Type, Deleter>::operator->() const
{
  return m_pointer;
}

template<typename Type, typename Deleter>
constexpr
me::SharedPtr<Type, Deleter>::operator bool() const
{
  return m_pointer != nullptr;
}
/* end class me::SharedPtr */

template<typename Type, typename... Args>
constexpr me::SharedPtr<Type>
me::make_shared(Args&&... args)
{
  Type* ptr = DefaultAllocator<Type>::allocate(1);
  TypeTraits<Type>::construct(ptr, forward<Args>(args)...);
  return SharedPtr<Type>(ptr);
}

#endif
