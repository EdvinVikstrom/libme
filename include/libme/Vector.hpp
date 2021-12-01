#ifndef LIBME_VECTOR_HPP
  #define LIBME_VECTOR_HPP

#include "libme/Type.hpp"
#include "libme/Allocator.hpp"
#include "libme/TypeTraits.hpp"
#include "libme/Memory.hpp"

#include <initializer_list>

namespace me {

  template<typename Type, typename Alloc = DefaultAllocator<Type>>
  class Vector {

  public:

    typedef AllocatorTraits<Type> Traits;
    typedef TempValue<Type, Traits> Temp;
    typedef size_t Size;
    typedef ssize_t SSize;
    typedef Type* Pointer;
    typedef const Type* ConstPointer;
    typedef Type* Iterator;
    typedef const Type* ConstIterator;

  private:

    Pointer m_begin;
    Pointer m_end;
    Pointer m_capacity;

  public:

    constexpr Vector(); // [1]
    constexpr Vector(Size count, const Type &value); // [3]
    constexpr explicit Vector(Size count); // [4]
    template<typename Iter> constexpr Vector(Iter first, Iter last); // [5]
    constexpr Vector(const Vector &vector); // [6]
    constexpr Vector(Vector &&vector) noexcept; // [8]
    constexpr Vector(std::initializer_list<Type> list); // [10]
    constexpr ~Vector();
    constexpr Vector& operator=(const Vector &vector);
    constexpr Vector& operator=(Vector &&vector) noexcept;
    constexpr Vector& operator=(std::initializer_list<Type> list);
    constexpr void assign(Size count, const Type &value);
    template<typename Iter> constexpr void assign(Iter first, Iter last);
    constexpr void assign(std::initializer_list<Type> list);

    [[nodiscard]] constexpr Type& at(Size pos);
    [[nodiscard]] constexpr const Type& at(Size pos) const;
    [[nodiscard]] constexpr Type& operator[](Size pos);
    [[nodiscard]] constexpr const Type& operator[](Size pos) const;
    [[nodiscard]] constexpr Type& front();
    [[nodiscard]] constexpr const Type& front() const;
    [[nodiscard]] constexpr Type& back();
    [[nodiscard]] constexpr const Type& back() const;
    [[nodiscard]] constexpr Pointer data() noexcept;
    [[nodiscard]] constexpr ConstPointer data() const noexcept;

    [[nodiscard]] constexpr Iterator begin();
    [[nodiscard]] constexpr ConstIterator begin() const;
    [[nodiscard]] constexpr Iterator end();
    [[nodiscard]] constexpr ConstIterator end() const;

    [[nodiscard]] constexpr bool is_empty() const;
    [[nodiscard]] constexpr Size length() const;
    [[nodiscard]] constexpr Size max_length() const;
    constexpr void reserve(Size new_cap);
    [[nodiscard]] constexpr Size capacity() const;
    constexpr void shrink_to_fit();

    constexpr void clear() noexcept;
    constexpr Vector& insert(ConstIterator pos, const Type &val);
    constexpr Vector& insert(ConstIterator pos, const Type &val, Size num);
    template<typename Iter> constexpr Vector& insert(ConstIterator pos, Iter first, Iter last);
    constexpr Vector& insert(ConstIterator pos, std::initializer_list<Type> list);
    template<typename... Args> constexpr Iterator emplace(ConstIterator pos, Args&&... args);
    constexpr Iterator erase(ConstIterator pos);
    constexpr Iterator erase(ConstIterator first, ConstIterator last);
    constexpr void push_back(const Type& val);
    constexpr void push_back(Type&& val);
    template<typename... Args> constexpr void emplace_back(Args&&... args);
    constexpr void pop_back();
    constexpr void resize(Size num);
    constexpr void resize(Size num, const Type &val);
    constexpr void swap(Vector &vector);

    constexpr void __vconstructl(Size len);
    constexpr void __vconstructlv(Size len, const Type &value);
    template<typename Iter> constexpr void __vconstructld(Size len, Iter data);
    constexpr void __vallocate(Size len);
    constexpr void __vdeallocate();
    constexpr void __vreserve(Size new_cap);
    constexpr void __vset_length(Size len);

  };

} // namespace me

/* ---------------- */
/* class me::Vector */
/* ---------------- */
template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>::Vector() // [1]
  : m_begin(nullptr), m_end(nullptr), m_capacity(nullptr)
{
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>::Vector(Size count, const Type &value) // [3]
{
  __vallocate(count);
  __vconstructlv(count, value);
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>::Vector(Size count) // [4]
{
  __vallocate(count);
  __vconstructl(count);
}

template<typename Type, typename Alloc>
template<typename Iter>
constexpr me::Vector<Type, Alloc>::Vector(Iter first, Iter last) // [5]
{
  Size count = last - first;
  __vallocate(count);
  __vconstructld(count, first);
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>::Vector(const Vector &vector) // [6]
{
  Size count = vector.length();
  __vallocate(count);
  __vconstructld(count, vector.data());
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>::Vector(Vector &&vector) noexcept // [8]
  : m_begin(vector.m_begin), m_end(vector.m_end), m_capacity(vector.m_capacity)
{
  vector.m_begin = vector.m_end = vector.m_capacity = nullptr;
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>::Vector(std::initializer_list<Type> list) // [10]
{
  __vallocate(list.size());
  __vconstructld(list.size(), list.begin());
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>::~Vector()
{
  if (m_begin)
    __vdeallocate();
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>&
me::Vector<Type, Alloc>::operator=(const Vector &vector)
{
  assign(vector.begin(), vector.end());
  return *this;
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>&
me::Vector<Type, Alloc>::operator=(Vector &&vector) noexcept
{
  m_begin = vector.m_begin;
  m_end = vector.m_end;
  m_capacity = vector.m_capacity;
  vector.m_begin = vector.m_end = vector.m_capacity = nullptr;
  return *this;
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>&
me::Vector<Type, Alloc>::operator=(std::initializer_list<Type> list)
{
  assign(list);
  return *this;
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::assign(Size count, const Type &value)
{
  if (count <= capacity()) 
  {
    __vset_length(count);
  }else
  {
    __vdeallocate();
    __vallocate();
  }
  __vconstructlv(count, value);
}

template<typename Type, typename Alloc>
template<typename Iter>
constexpr void
me::Vector<Type, Alloc>::assign(Iter first, Iter last)
{
  Size count = last - first;
  if (count <= capacity()) 
  {
    __vset_length(count);
  }else
  {
    __vdeallocate();
    __vallocate();
  }
  __vconstructld(count, first);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::assign(std::initializer_list<Type> list)
{
  if (list.size() <= capacity()) 
  {
    __vset_length(list.size());
  }else
  {
    __vdeallocate();
    __vallocate();
  }
  __vconstructld(list.size(), list.begin());
}

template<typename Type, typename Alloc>
constexpr Type&
me::Vector<Type, Alloc>::at(Size pos)
{
  LIBME_ASSERT(pos < length(), "me::Vector::at(): pos out of range");
  return m_begin[pos];
}

template<typename Type, typename Alloc>
constexpr const Type&
me::Vector<Type, Alloc>::at(Size pos) const
{
  LIBME_ASSERT(pos < length(), "me::Vector::at(): pos out of range");
  return m_begin[pos];
}

template<typename Type, typename Alloc>
constexpr Type&
me::Vector<Type, Alloc>::operator[](Size pos)
{
  return m_begin[pos];
}

template<typename Type, typename Alloc>
constexpr const Type&
me::Vector<Type, Alloc>::operator[](Size pos) const
{
  return m_begin[pos];
}

template<typename Type, typename Alloc>
constexpr Type&
me::Vector<Type, Alloc>::front()
{
  LIBME_ASSERT(length() != 0, "me::Vector::front(): called on a empty vector");
  return m_begin[0];
}

template<typename Type, typename Alloc>
constexpr const Type&
me::Vector<Type, Alloc>::front() const
{
  LIBME_ASSERT(length() != 0, "me::Vector::front(): called on a empty vector");
  return m_begin[0];
}

template<typename Type, typename Alloc>
constexpr Type&
me::Vector<Type, Alloc>::back()
{
  LIBME_ASSERT(length() != 0, "me::Vector::back(): called on a empty vector");
  return *(m_end - 1);
}

template<typename Type, typename Alloc>
constexpr const Type&
me::Vector<Type, Alloc>::back() const
{
  LIBME_ASSERT(length() != 0, "me::Vector::back(): called on a empty vector");
  return *(m_end - 1);
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Pointer
me::Vector<Type, Alloc>::data() noexcept
{
  return m_begin;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::ConstPointer
me::Vector<Type, Alloc>::data() const noexcept
{
  return m_begin;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Iterator
me::Vector<Type, Alloc>::begin()
{
  return m_begin;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::ConstIterator
me::Vector<Type, Alloc>::begin() const
{
  return m_begin;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Iterator
me::Vector<Type, Alloc>::end()
{
  return m_end;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::ConstIterator
me::Vector<Type, Alloc>::end() const
{
  return m_end;
}

template<typename Type, typename Alloc>
constexpr bool
me::Vector<Type, Alloc>::is_empty() const
{
  return m_begin == m_end;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Size
me::Vector<Type, Alloc>::length() const
{
  return m_end - m_begin;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Size
me::Vector<Type, Alloc>::max_length() const
{
  return 1234567; // TODO
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::reserve(Size new_cap)
{
  if (new_cap < capacity())
    return;

  __vreserve(new_cap);
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Size
me::Vector<Type, Alloc>::capacity() const
{
  return m_capacity - m_begin;
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::shrink_to_fit()
{
  if (m_capacity == m_end)
    return;

  Size len = length();
  Pointer new_data = Alloc::allocate(len);
  for (Size i = 0; i != len; i++)
    Traits::construct(&new_data[i], move(m_begin[i]));
  __vdeallocate();

  m_begin = new_data;
  m_end = m_begin + len;
  m_capacity = m_begin + len;
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::clear() noexcept
{
  for (Iterator i = m_begin; i != m_end; i++)
    Traits::destroy(*i);
  m_end = m_begin;
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>&
me::Vector<Type, Alloc>::insert(ConstIterator pos, const Type &val)
{
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>&
me::Vector<Type, Alloc>::insert(ConstIterator pos, const Type &val, Size num)
{
}

template<typename Type, typename Alloc>
template<typename Iter>
constexpr me::Vector<Type, Alloc>&
me::Vector<Type, Alloc>::insert(ConstIterator pos, Iter first, Iter last)
{
}

template<typename Type, typename Alloc>
constexpr me::Vector<Type, Alloc>&
me::Vector<Type, Alloc>::insert(ConstIterator pos, std::initializer_list<Type> list)
{
}

template<typename Type, typename Alloc>
template<typename... Args>
constexpr typename me::Vector<Type, Alloc>::Iterator
me::Vector<Type, Alloc>::emplace(ConstIterator pos, Args&&... args)
{
  ///* At least 1 free space */
  //if (m_end < m_capacity)
  //{
  //  Pointer ptr = m_begin + (pos - m_begin);

  //  if (ptr == m_end)
  //  {
  //    Traits::construct(m_end++, forward<Args>(args)...);
  //  }else
  //  {
  //    Temp tmp(forward<Args>(args)...);
  //    memory::move(ptr + 1, ptr, m_end - ptr);
  //    *ptr = move(tmp.get());
  //    m_end++;
  //  }
  //}else
  //{
  //  Size i = pos - m_begin;
  //  reserve(length() + 1);
  //  Pointer ptr = m_begin + i;
  //  memory::move(ptr + 1, ptr, m_end - ptr);
  //  Traits::construct(ptr, forward<Args>(args)...);
  //  m_end++;
  //}

  LIBME_ASSERT(memory::in_range(pos, m_begin, m_end), "me::Vector::emplace(): pos does not belong to this vector");

  Size i = pos - m_begin;
  reserve(length() + 1);
  Pointer ptr = m_begin + i;
  memory::move(ptr + 1, ptr, m_end - ptr);
  Traits::construct(ptr, forward<Args>(args)...);
  m_end++;
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Iterator
me::Vector<Type, Alloc>::erase(ConstIterator pos)
{
}

template<typename Type, typename Alloc>
constexpr typename me::Vector<Type, Alloc>::Iterator
me::Vector<Type, Alloc>::erase(ConstIterator first, ConstIterator last)
{
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::push_back(const Type& val)
{
  reserve(length() + 1);
  Traits::construct(m_end++, val);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::push_back(Type&& val)
{
  reserve(length() + 1);
  Traits::construct(m_end++, move(val));
}

template<typename Type, typename Alloc>
template<typename... Args>
constexpr void
me::Vector<Type, Alloc>::emplace_back(Args&&... args)
{
  reserve(length() + 1);
  Traits::construct(m_end++, forward<Args>(args)...);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::pop_back()
{
  Traits::destroy(back());
  m_end--;
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::resize(Size num)
{
  if (num > length())
  {
    __vreserve(num);
    for (Size i = 0; i != num; i++)
      Traits::construct(m_end + i);
  }
  __vset_length(num);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::resize(Size num, const Type &val)
{
  if (num > length())
  {
    __vreserve(num);
    for (Size i = 0; i != num; i++)
      Traits::construct(m_end + i, val);
  }
  __vset_length(num);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::swap(Vector &vector)
{
  ::me::swap(m_begin, vector.m_begin);
  ::me::swap(m_end, vector.m_end);
  ::me::swap(m_capacity, vector.m_capacity);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::__vconstructl(Size len)
{
  for (Size i = 0; i != len; i++)
    Traits::construct(&m_begin[i]);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::__vconstructlv(Size len, const Type &value)
{
  for (Size i = 0; i != len; i++)
    Traits::construct(&m_begin[i], value);
}

template<typename Type, typename Alloc>
template<typename Iter>
constexpr void
me::Vector<Type, Alloc>::__vconstructld(Size len, Iter data)
{
  for (Size i = 0; i != len; i++)
    Traits::construct(&m_begin[i], data[i]);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::__vallocate(Size len)
{
  m_begin = Alloc::allocate(len);
  m_capacity = m_end = m_begin + len;
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::__vdeallocate()
{
  for (Iterator i = m_begin; i != m_end; i++)
    Traits::destroy(*i);
  Alloc::deallocate(m_begin);
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::__vreserve(Size new_cap)
{
  Size len = length();
  Pointer new_data = Alloc::allocate(new_cap);
  for (Size i = 0; i != len; i++)
    Traits::construct(&new_data[i], move(m_begin[i]));
  __vdeallocate();

  m_begin = new_data;
  m_end = m_begin + len;
  m_capacity = m_begin + new_cap;
}

template<typename Type, typename Alloc>
constexpr void
me::Vector<Type, Alloc>::__vset_length(Size len)
{
  m_end = m_begin + len;
}
/* end class me::Vector */

#endif
