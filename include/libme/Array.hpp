#ifndef LIBME_ARRAY_HPP
  #define LIBME_ARRAY_HPP

#include "libme/Utility.hpp"

namespace me {

  template<typename Type, size_t Count>
  struct Array {

    typedef Type ValueType;
    typedef size_t SizeType;
    typedef ptrdiff_t DifferenceType;
    typedef Type& Reference;
    typedef const Type& ConstReference;
    typedef Type* Pointer;
    typedef const Type* ConstPointer;
    typedef Type* Iterator;
    typedef const Type* ConstIterator;

    Type m_array[Count];

    [[nodiscard]] constexpr Reference at(SizeType pos) { return m_array[pos]; }
    [[nodiscard]] constexpr ConstReference at(SizeType pos) const { return m_array[pos]; }
    [[nodiscard]] constexpr Reference operator[](SizeType pos) { return m_array[pos]; }
    [[nodiscard]] constexpr ConstReference operator[](SizeType pos) const { return m_array[pos]; }
    [[nodiscard]] constexpr Reference front() { return m_array[0]; }
    [[nodiscard]] constexpr ConstReference front() const { return m_array[0]; }
    [[nodiscard]] constexpr Reference back() { return m_array[Count - 1]; }
    [[nodiscard]] constexpr ConstReference back() const { return m_array[Count - 1]; }
    [[nodiscard]] constexpr Pointer data() noexcept { return m_array; }
    [[nodiscard]] constexpr ConstPointer data() const noexcept { return m_array; }

    [[nodiscard]] constexpr Iterator begin() noexcept { return m_array; }
    [[nodiscard]] constexpr ConstIterator begin() const noexcept { return m_array; }
    [[nodiscard]] constexpr Iterator end() noexcept { return m_array + Count; }
    [[nodiscard]] constexpr ConstIterator end() const noexcept { return m_array + Count; }

    [[nodiscard]] constexpr bool is_empty() const noexcept { return Count == 0; }
    [[nodiscard]] constexpr SizeType length() const noexcept { return Count; }
    [[nodiscard]] constexpr SizeType max_length() const noexcept { return 1234567; /* TODO */ }

    constexpr void fill(ConstReference value) { ::me::fill(m_array, Count, value); }
    constexpr void swap(Array &array)
      noexcept(is_nothrow_swappable<Type>::value) { ::me::swap_ranges(m_array, m_array + Count, array.m_array); }

  };

  /* zero-sized array */
  template<typename Type>
  struct Array<Type, 0> {

    typedef Type ValueType;
    typedef size_t SizeType;
    typedef ptrdiff_t DifferenceType;
    typedef Type& Reference;
    typedef const Type& ConstReference;
    typedef Type* Pointer;
    typedef const Type* ConstPointer;
    typedef Type* Iterator;
    typedef const Type* ConstIterator;

    Type m_array[0];

    [[nodiscard]] constexpr Reference at(SizeType)
    { LIBME_ASSERT(false, "me::Array::at(): called on a zero-sized array"); }
    [[nodiscard]] constexpr ConstReference at(SizeType) const
    { LIBME_ASSERT(false, "me::Array::at(): called on a zero-sized array"); }
    [[nodiscard]] constexpr Reference operator[](SizeType)
    { LIBME_ASSERT(false, "me::Array::operator[](): called on a zero-sized array"); }
    [[nodiscard]] constexpr ConstReference operator[](SizeType) const
    { LIBME_ASSERT(false, "me::Array::operator[](): called on a zero-sized array"); }
    [[nodiscard]] constexpr Reference front()
    { LIBME_ASSERT(false, "me::Array::front(): called on a zero-sized array"); }
    [[nodiscard]] constexpr ConstReference front() const
    { LIBME_ASSERT(false, "me::Array::front(): called on a zero-sized array"); }
    [[nodiscard]] constexpr Reference back()
    { LIBME_ASSERT(false, "me::Array::back(): called on a zero-sized array"); }
    [[nodiscard]] constexpr ConstReference back() const
    { LIBME_ASSERT(false, "me::Array::back(): called on a zero-sized array"); }
    [[nodiscard]] constexpr Pointer data() noexcept { return m_array; }
    [[nodiscard]] constexpr ConstPointer data() const noexcept  { return m_array; }

    [[nodiscard]] constexpr Iterator begin() noexcept { return m_array; }
    [[nodiscard]] constexpr ConstIterator begin() const noexcept { return m_array; }
    [[nodiscard]] constexpr Iterator end() noexcept { return m_array + 0; }
    [[nodiscard]] constexpr ConstIterator end() const noexcept { return m_array + 0; }

    [[nodiscard]] constexpr bool is_empty() const noexcept { return true; }
    [[nodiscard]] constexpr SizeType length() const noexcept { return 0; }
    [[nodiscard]] constexpr SizeType max_length() const noexcept { return 1234567; /* TODO */ }

    constexpr void fill(ConstReference) { }
    constexpr void swap(Array&)
      noexcept(is_nothrow_swappable<Type>::value) { }

  };

  template<typename Type, size_t Count>
  constexpr bool operator==(const Array<Type, Count> &lhs, const Array<Type, Count> &rhs);

  template<size_t Index, typename Type, size_t Count>
  constexpr Type& get(Array<Type, Count> &array) noexcept;

  template<size_t Index, typename Type, size_t Count>
  constexpr Type&& get(Array<Type, Count> &&array) noexcept;

  template<size_t Index, typename Type, size_t Count>
  constexpr const Type& get(const Array<Type, Count> &array) noexcept;

  template<size_t Index, typename Type, size_t Count>
  constexpr const Type&& get(const Array<Type, Count> &&array) noexcept;

  template<typename Type, size_t Count>
  constexpr void swap(Array<Type, Count> &lhs, Array<Type, Count> &rhs)
    noexcept(noexcept(lhs.swap(rhs)))
    requires (Count == 0) || is_swappable<Type>::value;

  template<typename Type, size_t Count>
  constexpr Array<Type, Count> to_array(Type (&arr)[Count]);

  template<typename Type, size_t Count>
  constexpr Array<Type, Count> to_array(Type (&&arr)[Count]);

} // namespace me

template<typename Type, size_t Count>
constexpr bool
  me::operator==(const Array<Type, Count> &a, const Array<Type, Count> &b)
{
  for (size_t i = 0; i != Count; i++)
  {
    if (a.at(i) != b.at(i))
      return false;
  }
  return true;
}

template<size_t Index, typename Type, size_t Count>
constexpr Type&
  me::get(Array<Type, Count> &array)
  noexcept
{
  return array.at(Index);
}

template<size_t Index, typename Type, size_t Count>
constexpr Type&&
  me::get(Array<Type, Count> &&array)
  noexcept
{
  return array.at(Index);
}

template<size_t Index, typename Type, size_t Count>
constexpr const Type&
  me::get(const Array<Type, Count> &array)
  noexcept
{
  return array.at(Index);
}

template<size_t Index, typename Type, size_t Count>
constexpr const Type&&
  me::get(const Array<Type, Count> &&array)
  noexcept
{
  return array.at(Index);
}

template<typename Type, size_t Count>
constexpr void
  me::swap(Array<Type, Count> &lhs, Array<Type, Count> &rhs)
  noexcept(noexcept(lhs.swap(rhs)))
  requires (Count == 0) || is_swappable<Type>::value
{
  lhs.swap(rhs);
}

template<typename Type, size_t Count>
constexpr me::Array<Type, Count>
  me::to_array(Type (&arr)[Count])
{
  (void) arr; // TODO
}

template<typename Type, size_t Count>
constexpr me::Array<Type, Count>
  me::to_array(Type (&&arr)[Count])
{
  (void) arr; // TODO
}

#endif
